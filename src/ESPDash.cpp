#include "ESPDash.h"

dash::Component::Component(ESPDash& dashboard, const char* name) : _id(nextId()), _name(name) {
  dashboard.add(*this);
}

ESPDash::ESPDash(AsyncWebServer& server, const char* uri, bool enable_default_stats) {
  _server = &server;

  if (enable_default_stats) {
    // Hardware
    dash::StatisticValue<const char*>* hardware = new dash::StatisticValue<const char*>("Hardware");
    hardware->setValue(DASH_HARDWARE);
    _components.push_back(hardware);
    _componentsOwned.push_back(hardware);

    // SDK Version
    dash::StatisticValue<dash::string>* sdk = new dash::StatisticValue<dash::string>("SDK Version");
#if defined(ESP8266)
    sdk->setValue(ESP.getCoreVersion().c_str());
#elif defined(ESP32)
    sdk->setValue(esp_get_idf_version());
#elif defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
    String sdk_version;
    sdk_version.reserve(16);
    sdk_version.concat(ARDUINO_PICO_MAJOR);
    sdk_version.concat(".");
    sdk_version.concat(ARDUINO_PICO_MINOR);
    sdk_version.concat(".");
    sdk_version.concat(ARDUINO_PICO_REVISION);
    sdk->setValue(sdk_version.c_str());
#else
    sdk->setValue("Unknown Platform");
#endif
    _components.push_back(sdk);
    _componentsOwned.push_back(sdk);

    // MAC Address
    dash::StatisticValue<dash::string>* mac = new dash::StatisticValue<dash::string>("MAC Address");
    mac->setValue(WiFi.macAddress().c_str());
    _components.push_back(mac);
    _componentsOwned.push_back(mac);

    // Free Heap
    dash::StatisticProvider<uint32_t>* heap = new dash::StatisticProvider<uint32_t>("Free Heap (SRAM)");
#if defined(ESP8266) || defined(ESP32)
    heap->setProvider([]() { return ESP.getFreeHeap(); });
#elif defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
    heap->setProvider([]() { return rp2040.getFreeHeap(); });
#else
    heap->setProvider([]() { return 0; });
#endif
    _components.push_back(heap);
    _componentsOwned.push_back(heap);

    // WiFi Mode
    dash::StatisticProvider<uint8_t>* wifi = new dash::StatisticProvider<uint8_t>("WiFi Mode");
    wifi->setProvider([]() { return WiFi.getMode(); });
    _components.push_back(wifi);
    _componentsOwned.push_back(wifi);

    // WiFi Signal
    dash::StatisticProvider<int8_t>* signal = new dash::StatisticProvider<int8_t>("WiFi Signal");
    signal->setProvider([]() { return WiFi.RSSI(); });
    _components.push_back(signal);
    _componentsOwned.push_back(signal);
  }

  // Initialize AsyncWebSocket
  _ws = new AsyncWebSocket("/dashws");

  // Attach AsyncWebServer Routes
  _server->on(uri, HTTP_GET, [this](AsyncWebServerRequest* request) {
    if (basic_auth) {
      if (!request->authenticate(username.c_str(), password.c_str()))
        return request->requestAuthentication();
    }
    // respond with the compressed frontend
    AsyncWebServerResponse* response = request->beginResponse(200, "text/html", DASH_HTML, sizeof(DASH_HTML));
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Cache-Control", "public, max-age=900");
    request->send(response);
  });

  // Websocket Callback Handler
  _ws->onEvent([&](__unused AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, __unused void* arg, uint8_t* data, size_t len) {
  // Request Buffer
#if ARDUINOJSON_VERSION_MAJOR == 6
    StaticJsonDocument<200> json;
#else
    JsonDocument json;
#endif

    if (type == WS_EVT_DATA) {
      AwsFrameInfo* info = (AwsFrameInfo*)arg;
      if (info->final && info->index == 0 && info->len == len) {
        if (info->opcode == WS_TEXT) {
          data[len] = 0;
          deserializeJson(json, reinterpret_cast<const char*>(data));
          // client side commands parsing
          if (json["command"] == "get:layout") {
            _asyncAccessInProgress = true;
            if (_beforeUpdateCallback)
              _beforeUpdateCallback(false);
            generateLayoutJSON(client, false, nullptr);
            _asyncAccessInProgress = false;
          } else if (json["command"] == "ping") {
            _ws->text(client->id(), "{\"command\":\"pong\"}");
          } else if (json["id"].is<uint16_t>()) {
            uint16_t id = json["id"].as<uint16_t>();
            // find component with same id
            for (auto c : _components) {
              if (c->id() == id) {
                _asyncAccessInProgress = true;
#ifdef DASH_DEBUG
                dash::string jsonEvent;
                serializeJson(json, jsonEvent);
                DASH_LOGD("ESPDash", "[%d] %s: onEvent(%s): %s", c->id(), c->name(), json["command"].as<const char*>(), jsonEvent.c_str());
#endif
                c->onEvent(json.as<JsonObject>());
                _asyncAccessInProgress = false;
                break;
              }
            }
          }
        }
      }
    }
  });

  // Attach Websocket Instance to AsyncWebServer
  _server->addHandler(_ws);
}

void ESPDash::setAuthentication(const char* user, const char* pass) {
  username = user;
  password = pass;
  basic_auth = username.length() && password.length();
  if (basic_auth) {
    _ws->setAuthentication(username.c_str(), password.c_str());
  }
}

// Add a component to the dashboard and return true if the component was added, false if the component ID was already present
bool ESPDash::add(dash::Component& component) {
  for (auto c : _components)
    if (c->id() == component.id()) {
#ifdef DASH_DEBUG
      DASH_LOGW("ESPDash", "Component with ID %" PRIu16 " already exists", component.id());
#endif
      return false;
    }
  _components.push_back(&component);
  return true;
}

void ESPDash::remove(dash::Component& component) {
  _components.remove(&component);
}

// generates the layout JSON string to the frontend
void ESPDash::generateLayoutJSON(AsyncWebSocketClient* client, bool changes_only, const dash::Component* onlyComponent) {
#ifdef DASH_DEBUG
  DASH_LOGD("ESPDash", "generateLayoutJSON(%p, %d, %p)", client, changes_only, onlyComponent);
#endif

#if ARDUINOJSON_VERSION_MAJOR == 6
  DynamicJsonDocument doc(DASH_JSON_DOCUMENT_ALLOCATION);
#else
  JsonDocument doc;
#endif

  if (changes_only || onlyComponent) {
    // send only the components that have changed or a specific component
    doc["command"] = "update:components";

    if (onlyComponent) {
      if (generateLayoutJSON(client, true, onlyComponent, doc, onlyComponent->family()))
        send(client, doc);

    } else {
      // when sending updates, go through all components in order of family
      // and try to pack as many updates as possible in the same payload
      size_t docSize = 0;
      docSize += generateLayoutJSON(client, true, onlyComponent, doc, dash::Component::Family::STATISTIC);
      docSize += generateLayoutJSON(client, true, onlyComponent, doc, dash::Component::Family::CARD);
      docSize += generateLayoutJSON(client, true, onlyComponent, doc, dash::Component::Family::CHART);
      if (docSize > 0)
        send(client, doc);
    }

  } else {
    doc["command"] = "update:layout:begin";
    send(client, doc);

    if (generateLayoutJSON(client, false, nullptr, doc, dash::Component::Family::STATISTIC))
      send(client, doc);

    if (generateLayoutJSON(client, false, nullptr, doc, dash::Component::Family::CARD))
      send(client, doc);

    if (generateLayoutJSON(client, false, nullptr, doc, dash::Component::Family::CHART))
      send(client, doc);
  }
}

size_t ESPDash::generateLayoutJSON(AsyncWebSocketClient* client, bool changes_only, const dash::Component* onlyComponent, JsonDocument& doc, dash::Component::Family family) {
  size_t docSize = 0;
  doc["command"] = changes_only ? "update:components" : "update:layout:next";

  for (auto c : _components) {
    // skip if onlyComponent is set and it is not the current component
    if (onlyComponent && onlyComponent != c)
      continue;

    const dash::Component::Family f = c->family();
    if (f != family)
      continue;

    // for auto-updatable components like statistics provider
    c->selfUpdate();

    // skip if we only want to send changes and the component has not changed
    if (changes_only && !c->hasChanged())
      continue;

    const char* key = jsonKey(f);

#ifdef DASH_DEBUG
    DASH_LOGD("ESPDash", "Generate %s/%d: %s", key, c->id(), c->name());
#endif

    JsonObject obj = doc[key].add<JsonObject>();
    c->toJson(obj, changes_only);

    // check if json doc is full
    if (doc.overflowed()) {
      DASH_LOGW("ESPDash", "Doc overflow!");

      // send current data if json doc is full
      send(client, doc);
      docSize = 0;
      doc["command"] = changes_only ? "update:components" : "update:layout:next";

      // add the component back again since it was not added
      obj = doc[key].add<JsonObject>();
      c->toJson(obj, changes_only);
    }

    docSize += measureJson(obj);

    // check if we are above the payload size
    if (docSize > DASH_JSON_SIZE) {
#ifdef DASH_DEBUG
      DASH_LOGD("ESPDash", "Reached payload size: %u", docSize);
#endif
      // send current data if we are above the payload size
      send(client, doc);
      docSize = 0;
      doc["command"] = changes_only ? "update:components" : "update:layout:next";
    }

    // component processed
    if (changes_only)
      c->clearChanges();
  }

  return docSize;
}

void ESPDash::send(AsyncWebSocketClient* client, JsonDocument& doc) {
  const size_t len = measureJson(doc);

#ifdef DASH_DEBUG
  #if defined(ESP8266) || defined(ESP32)
  DASH_LOGD("ESPDash", "send(%u) - Free heap: %" PRIu32, len, ESP.getFreeHeap());
  #elif defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
  DASH_LOGD("ESPDash", "send(%u) - Free heap: %d", len, rp2040.getFreeHeap());
  #endif

  // uncommenting this will print the JSON to the serial console but can be very verbose when having many components
  // and can cause the websocket client in browser to timeout
  // serializeJson(doc, Serial);
  // Serial.println();
#endif

  AsyncWebSocketMessageBuffer* buffer = _ws->makeBuffer(len);
  assert(buffer);
  serializeJson(doc, buffer->get(), len);
  if (client != nullptr) {
    client->text(buffer);
  } else {
    _ws->textAll(buffer);
  }
  doc.clear();
}

const char* ESPDash::jsonKey(dash::Component::Family family) {
  switch (family) {
    case dash::Component::Family::CARD:
      return "cards";
    case dash::Component::Family::CHART:
      return "charts";
    case dash::Component::Family::STATISTIC:
      return "stats";
    default:
      assert(false);
      return "";
  }
}

/* Send Card Updates to all clients */
void ESPDash::sendUpdates(bool force) {
  _ws->cleanupClients(DASH_MAX_WS_CLIENTS);
  if (!hasClient()) {
    return;
  }
  if (_beforeUpdateCallback)
    _beforeUpdateCallback(!force);
  generateLayoutJSON(nullptr, !force, nullptr);
}

void ESPDash::refresh(const dash::Component& component) {
  _ws->cleanupClients(DASH_MAX_WS_CLIENTS);
  if (!hasClient()) {
    return;
  }
  if (_beforeUpdateCallback)
    _beforeUpdateCallback(true);
  generateLayoutJSON(nullptr, true, &component);
}

/*
  Destructor
*/
ESPDash::~ESPDash() {
  _server->removeHandler(_ws);
  delete _ws;
  _components.clear();
  for (auto c : _componentsOwned)
    delete c;
  _componentsOwned.clear();
}
