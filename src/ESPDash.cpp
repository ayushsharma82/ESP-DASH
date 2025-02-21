#include "ESPDash.h"

// Integral type to string pairs events
// ID, type
struct CardNames cardTags[] = {
  {GENERIC_CARD, "generic"},
  {TEMPERATURE_CARD, "temperature"},
  {HUMIDITY_CARD, "humidity"},
  {STATUS_CARD, "status"},
  {SLIDER_CARD, "slider"},
  {BUTTON_CARD, "button"},
  {PROGRESS_CARD, "progress"},
};

// Integral type to string pairs events
// ID, type
struct ChartNames chartTags[] = {
  {BAR_CHART, "bar"},
};


/*
  Constructors
*/
ESPDash::ESPDash(AsyncWebServer* server) : ESPDash(server, "/", true) {}

ESPDash::ESPDash(AsyncWebServer* server, bool enable_default_stats) : ESPDash(server, "/", enable_default_stats) {}

ESPDash::ESPDash(AsyncWebServer* server, const char* uri, bool enable_default_stats) {
  _server = server;
  default_stats_enabled = enable_default_stats;

  // Initialize AsyncWebSocket
  _ws = new AsyncWebSocket("/dashws");

  // Attach AsyncWebServer Routes
  _server->on(uri, HTTP_GET, [this](AsyncWebServerRequest *request){
    if(basic_auth){
      if(!request->authenticate(username.c_str(), password.c_str()))
      return request->requestAuthentication();
    }
    // respond with the compressed frontend
    AsyncWebServerResponse *response = request->beginResponse(200, "text/html", DASH_HTML, sizeof(DASH_HTML));
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Cache-Control", "public, max-age=900");
    request->send(response);
  });

  // Websocket Callback Handler
  _ws->onEvent([&](__unused AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
  // Request Buffer
#if ARDUINOJSON_VERSION_MAJOR == 7
    JsonDocument json;
#else
    StaticJsonDocument<200> json;
#endif

    if (type == WS_EVT_DATA) {
      AwsFrameInfo * info = (AwsFrameInfo * ) arg;
      if (info -> final && info -> index == 0 && info -> len == len) {
        if (info -> opcode == WS_TEXT) {
          data[len] = 0;
          deserializeJson(json, reinterpret_cast<const char*>(data));
          // client side commands parsing
          if (json["command"] == "get:layout") {
            _asyncAccessInProgress = true;
            if (_beforeUpdateCallback)
              _beforeUpdateCallback(false);
            generateLayoutJSON(client, false);
            _asyncAccessInProgress = false;
          } else if (json["command"] == "ping") {
            _ws->text(client->id(), "{\"command\":\"pong\"}");
          } else if (json["command"] == "button:clicked") {
            // execute and reference card data struct to funtion
            uint32_t id = json["id"].as<uint32_t>();
            for(int i=0; i < cards.Size(); i++){
              Card *p = cards[i];
              if(id == p->_id){
                if(p->_callback != nullptr){
                  _asyncAccessInProgress = true;
                  p->_callback(json["value"].as<int>());
                  _asyncAccessInProgress = false;
                }
              }
            }
          } else if (json["command"] == "slider:changed") {
            // execute and reference card data struct to funtion
            uint32_t id = json["id"].as<uint32_t>();
            for(int i=0; i < cards.Size(); i++){
              Card *p = cards[i];
              if(id == p->_id){
                if(p->_callback_f != nullptr && p->_value_type == Card::FLOAT){
                  _asyncAccessInProgress = true;
                  p->_callback_f(json["value"].as<float>());
                  _asyncAccessInProgress = false;
                } else if(p->_callback != nullptr) {
                  _asyncAccessInProgress = true;
                  p->_callback(json["value"].as<int>());
                  _asyncAccessInProgress = false;
                }
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

void ESPDash::setAuthentication(const char *user, const char *pass) {
  username = user;
  password = pass;
  basic_auth = username.length() && password.length();
  if(basic_auth) {
    _ws->setAuthentication(username.c_str(), password.c_str());
  }
}

void ESPDash::setAuthentication(const String &user, const String &pass) {
  setAuthentication(user.c_str(), pass.c_str());
}

// Add Card
void ESPDash::add(Card *card) {
  cards.PushBack(card);
}

// Remove Card
void ESPDash::remove(Card *card) {
  for(int i=0; i < cards.Size(); i++){
    Card *p = cards[i];
    if(p->_id == card->_id){
      cards.Erase(i);
      return;
    }
  }
}


// Add Chart
void ESPDash::add(Chart *chart) {
  charts.PushBack(chart);
}

// Remove Card
void ESPDash::remove(Chart *chart) {
  for(int i=0; i < charts.Size(); i++){
    Chart *p = charts[i];
    if(p->_id == chart->_id){
      charts.Erase(i);
      return;
    }
  }
}

// Add Statistic
void ESPDash::add(Statistic *statistic) {
  statistics.PushBack(statistic);
}

// Remove Statistic
void ESPDash::remove(Statistic *statistic) {
  for(int i=0; i < statistics.Size(); i++){
    Statistic *p = statistics[i];
    if(p->_id == statistic->_id){
      statistics.Erase(i);
      return;
    }
  }
}

// generates the layout JSON string to the frontend
void ESPDash::generateLayoutJSON(AsyncWebSocketClient* client, bool changes_only, Card* onlyCard, Chart* onlyChart) {
#if ARDUINOJSON_VERSION_MAJOR == 6
  DynamicJsonDocument doc(DASH_JSON_DOCUMENT_ALLOCATION);
#else
  JsonDocument doc;
#endif

  // preparing layout
  if (!changes_only) {
    doc["command"] = "update:layout:begin";
  } else {
    doc["command"] = "update:components";
  }
  if (!changes_only) {
    send(client, doc);
  }

  // Generate JSON for all Cards
  doc["command"] = changes_only ? "update:components" : "update:layout:next";
  for (int i = 0; i < cards.Size(); i++) {
    Card* c = cards[i];
    if (changes_only) {
      if (!c->_changed && (onlyCard == nullptr || onlyCard->_id != c->_id)) {
        continue;
      }
    }

    // Generate JSON
#if ARDUINOJSON_VERSION_MAJOR == 6
    JsonObject obj = doc["cards"].createNestedObject();
#else
    JsonObject obj = doc["cards"].add<JsonObject>();
#endif
    generateComponentJSON(obj, c, changes_only);

    if (overflowed(doc)) {
      doc["cards"].as<JsonArray>().remove(doc["cards"].as<JsonArray>().size() - 1);
      send(client, doc);
      doc["command"] = changes_only ? "update:components" : "update:layout:next";
      i--;
      continue;
    }

    // Clear change flags
    if (changes_only) {
      c->_changed = false;
    }
  }

  if (doc["cards"].as<JsonArray>().size() > 0)
    send(client, doc);

  // Generate JSON for all Charts
  doc["command"] = changes_only ? "update:components" : "update:layout:next";
  for (int i = 0; i < charts.Size(); i++) {
    Chart* c = charts[i];
    if (changes_only) {
      if (!c->_x_changed && !c->_y_changed && (onlyChart == nullptr || onlyChart->_id != c->_id)) {
        continue;
      }
    }

    // Generate JSON
#if ARDUINOJSON_VERSION_MAJOR == 7
    JsonObject obj = doc["charts"].add<JsonObject>();
#else
    JsonObject obj = doc["charts"].createNestedObject();
#endif
    generateComponentJSON(obj, c, changes_only);

    if (overflowed(doc)) {
      doc["charts"].as<JsonArray>().remove(doc["charts"].as<JsonArray>().size() - 1);
      send(client, doc);
      doc["command"] = changes_only ? "update:components" : "update:layout:next";
      i--;
      continue;
    }

    // Clear change flags
    if (changes_only) {
      c->_x_changed = false;
      c->_y_changed = false;
    }
  }

  if (doc["charts"].as<JsonArray>().size() > 0)
    send(client, doc);

  // Generate JSON for all Statistics
  doc["command"] = changes_only ? "update:components" : "update:layout:next";
  int idx = 0;

  // Check if default statistics are needed
  if (default_stats_enabled) {
    if (!changes_only) {
      // Hardware
      doc["stats"][idx]["i"] = -1;
      doc["stats"][idx]["k"] = "Hardware";
      doc["stats"][idx]["v"] = DASH_HARDWARE;
      idx++;

      // SDK Version
      doc["stats"][idx]["i"] = -2;
      doc["stats"][idx]["k"] = "SDK Version";
#if defined(ESP8266)
      doc["stats"][idx]["v"] = ESP.getCoreVersion();
#elif defined(ESP32)
      doc["stats"][idx]["v"] = String(esp_get_idf_version());
#elif defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
      char sdk_version[16];
      sprintf(sdk_version, "%s.%s.%s", ARDUINO_PICO_MAJOR, ARDUINO_PICO_MINOR, ARDUINO_PICO_REVISION);
      doc["stats"][idx]["v"] = sdk_version;
#else
      doc["stats"][idx]["v"] = "Unknown Platform";
#endif
      idx++;

      // MAC Address
      doc["stats"][idx]["i"] = -3;
      doc["stats"][idx]["k"] = "MAC Address";
      doc["stats"][idx]["v"] = WiFi.macAddress();
      idx++;
    }

    // Free Heap
    doc["stats"][idx]["i"] = -4;
    doc["stats"][idx]["k"] = "Free Heap (SRAM)";
#if defined(ESP8266) || defined(ESP32)
    doc["stats"][idx]["v"] = ESP.getFreeHeap();
#elif defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
    doc["stats"][idx]["v"] = rp2040.getFreeHeap();
#else
    doc["stats"][idx]["v"] = "Unknown Platform";
#endif
    idx++;

    // WiFi Mode
    doc["stats"][idx]["i"] = -5;
    doc["stats"][idx]["k"] = "WiFi Mode";
    doc["stats"][idx]["v"] = WiFi.getMode();
    idx++;

    // WiFi Signal
    doc["stats"][idx]["i"] = -6;
    doc["stats"][idx]["k"] = "WiFi Signal";
    doc["stats"][idx]["v"] = WiFi.RSSI();
    idx++;
  }

  // Loop through user defined stats
  for (int i = 0; i < statistics.Size(); i++) {
    Statistic* s = statistics[i];
    if (changes_only) {
      if (!s->_changed) {
        continue;
      }
    }

    doc["stats"][idx]["i"] = s->_id;
    doc["stats"][idx]["k"] = s->_key;
    if (changes_only || s->_value.length() > 0)
      doc["stats"][idx]["v"] = s->_value;
    doc["stats"][idx]["v"] = s->_value;
    idx++;

    if (overflowed(doc)) {
      doc["stats"].as<JsonArray>().remove(idx - 1);
      send(client, doc);
      doc["command"] = changes_only ? "update:components" : "update:layout:next";
      i--;
      idx = 0;
      continue;
    }

    // Clear change flags
    if (changes_only) {
      s->_changed = false;
    }
  }

  if (idx > 0)
    send(client, doc);
}

void ESPDash::send(AsyncWebSocketClient* client, JsonDocument& doc) {
  const size_t len = measureJson(doc);
  // ESP_LOGW("ESPDash", "Required Heap size to build WebSocket message: %d bytes. Free Heap: %" PRIu32 " bytes", len, ESP.getFreeHeap());
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

bool ESPDash::overflowed(JsonDocument& doc) {
#if DASH_JSON_SIZE > 0 // ArduinoJson 6 (mandatory) or 7
  return doc.overflowed() || measureJson(doc.as<JsonObject>()) > DASH_JSON_SIZE;
#elif DASH_MIN_FREE_HEAP > 0 // ArduinoJson 7 only
  return ESP.getFreeHeap() >= DASH_MIN_FREE_HEAP;
#else // ArduinoJson 7 only
  return doc.overflowed();
#endif
}

/*
  Generate Card JSON
*/
void ESPDash::generateComponentJSON(JsonObject& doc, Card* card, bool change_only){
  doc["id"] = card->_id;
  if (!change_only){
    doc["n"] = card->_name;
    doc["t"] = cardTags[card->_type].type;
    if (card->_type == SLIDER_CARD || card->_type == PROGRESS_CARD) {
      if(card->_value_type == Card::FLOAT) {
        doc["min"] = String(card->_value_min_f, 2);
        doc["max"] = String(card->_value_max_f, 2);
        doc["step"] = String(card->_value_step_f, 2);
      } else {
        doc["min"] = card->_value_min;
        doc["max"] = card->_value_max;
        doc["step"] = card->_value_step;
      }
    }
  }
  
#if defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
  if(change_only || card->_symbol.length() > 0)
#else
  if(change_only || !card->_symbol.isEmpty())
#endif
    doc["s"] = card->_symbol;

  switch (card->_value_type) {
    case Card::INTEGER:
      doc["v"] = card->_value_i;
      break;
    case Card::FLOAT:
      doc["v"] = String(card->_value_f, 2);
      break;
    case Card::STRING:
#if defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
      if(change_only || card->_value_s.length() > 0) {
#else
      if(change_only || !card->_value_s.isEmpty()) {
#endif
        doc["v"] = card->_value_s;
      }
      break;
    default:
      // blank value
      break;
  }
}


/*
  Generate Chart JSON
*/
void ESPDash::generateComponentJSON(JsonObject& doc, Chart* chart, bool change_only){
  doc["id"] = chart->_id;
  if(!change_only){
    doc["n"] = chart->_name;
    doc["t"] = chartTags[chart->_type].type;
  }

  if(!change_only || chart->_x_changed) {
    JsonArray xAxis = doc["x"].to<JsonArray>();
    switch (chart->_x_axis_type) {
      case GraphAxisType::INTEGER:
        #if DASH_USE_LEGACY_CHART_STORAGE == 1
          for(int i=0; i < chart->_x_axis_i.Size(); i++)
            xAxis.add(chart->_x_axis_i[i]);
        #else
          if (chart->_x_axis_i_ptr != nullptr) {
            for(unsigned int i=0; i < chart->_x_axis_ptr_size; i++)
              xAxis.add(chart->_x_axis_i_ptr[i]);
          }
        #endif
        break;
      case GraphAxisType::FLOAT:
        #if DASH_USE_LEGACY_CHART_STORAGE == 1
          for(int i=0; i < chart->_x_axis_f.Size(); i++)
            xAxis.add(chart->_x_axis_f[i]);
        #else
          if (chart->_x_axis_f_ptr != nullptr) {
            for(unsigned int i=0; i < chart->_x_axis_ptr_size; i++)
              xAxis.add(chart->_x_axis_f_ptr[i]);
          }
        #endif
        break;
      case GraphAxisType::CHAR:
        #if DASH_USE_LEGACY_CHART_STORAGE == 1
          for(int i=0; i < chart->_x_axis_s.Size(); i++)
            xAxis.add(chart->_x_axis_s[i].c_str());
        #else
          if (chart->_x_axis_char_ptr != nullptr) {
            for(unsigned int i=0; i < chart->_x_axis_ptr_size; i++)
              xAxis.add(chart->_x_axis_char_ptr[i]);
          }
        #endif
        break;
      case GraphAxisType::STRING:
        #if DASH_USE_LEGACY_CHART_STORAGE == 1
          for(int i=0; i < chart->_x_axis_s.Size(); i++)
            xAxis.add(chart->_x_axis_s[i].c_str());
        #else
          if (chart->_x_axis_s_ptr != nullptr) {
            for(unsigned int i=0; i < chart->_x_axis_ptr_size; i++)
              xAxis.add(chart->_x_axis_s_ptr[i]);
          }
        #endif
        break;
      default:
        // blank value
        break;
    }
  }

  if(!change_only || chart->_y_changed) {
    JsonArray yAxis = doc["y"].to<JsonArray>();
    switch (chart->_y_axis_type) {
      case GraphAxisType::INTEGER:
        #if DASH_USE_LEGACY_CHART_STORAGE == 1
          for(int i=0; i < chart->_y_axis_i.Size(); i++)
            yAxis.add(chart->_y_axis_i[i]);
        #else
          if (chart->_y_axis_i_ptr != nullptr) {
            for(unsigned int i=0; i < chart->_y_axis_ptr_size; i++)
              yAxis.add(chart->_y_axis_i_ptr[i]);
          }
        #endif
        break;
      case GraphAxisType::FLOAT:
        #if DASH_USE_LEGACY_CHART_STORAGE == 1
          for(int i=0; i < chart->_y_axis_f.Size(); i++)
            yAxis.add(chart->_y_axis_f[i]);
        #else
          if (chart->_y_axis_f_ptr != nullptr) {
            for(unsigned int i=0; i < chart->_y_axis_ptr_size; i++)
              yAxis.add(chart->_y_axis_f_ptr[i]);
          }
        #endif
        break;
      default:
        // blank value
        break;
    }
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
  generateLayoutJSON(nullptr, !force);
}

void ESPDash::refreshCard(Card *card) {
  _ws->cleanupClients(DASH_MAX_WS_CLIENTS);
  if (!hasClient()) {
    return;
  }
  if (_beforeUpdateCallback)
    _beforeUpdateCallback(true);
  generateLayoutJSON(nullptr, true, card);
}

void ESPDash::refreshChart(Chart* chart) {
  _ws->cleanupClients(DASH_MAX_WS_CLIENTS);
  if (!hasClient()) {
    return;
  }
  if (_beforeUpdateCallback)
    _beforeUpdateCallback(true);
  generateLayoutJSON(nullptr, true, nullptr, chart);
}

uint32_t ESPDash::nextId() {
  return _idCounter++;
}

bool ESPDash::hasClient() {
  return _ws->count() > 0;
}

/*
  Destructor
*/
ESPDash::~ESPDash(){
  _server->removeHandler(_ws);
  delete _ws;
}
