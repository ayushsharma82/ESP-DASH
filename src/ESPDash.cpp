#include "ESPDash.h"

#define ARDUINOJSON_NAMESPACE ArduinoJson
#include <ArduinoJson.hpp>

/*
  Constructors
*/
ESPDash::ESPDash()
{
  home_screen = new Tab(this, "Home", "Overview", "");
  current_tab_id = home_screen->getId();
}

ESPDash::ESPDash(AsyncWebServer* server, bool enable_stats):
  stats_enabled(enable_stats)
{
  init(server);
  home_screen = new Tab(this, "Home", "Overview", "");
  current_tab_id = home_screen->getId();
}

ESPDash& ESPDash::displayStatistics(bool enable_stats) {
  stats_enabled = enable_stats;
  return *this;
}

ESPDash& ESPDash::init(AsyncWebServer *server) {
  _server = server;

  // Initialize AsyncWebSocket
  _ws = new AsyncWebSocket("/dashws");

  // Attach AsyncWebServer Routes
  _server->on("/", HTTP_GET, onWebServerRequest());

  // Websocket Callback Handler
  _ws->onEvent(onWebSocketEvent());

  // Attach Websocket Instance to AsyncWebServer
  _server->addHandler(_ws);

  return *this;
}


void ESPDash::setAuthentication(const char *user, const char *pass) {
  username = user;
  password = pass;
  basic_auth = true;
  _ws->setAuthentication(user, pass);
}

// Add Tab
void ESPDash::add(Tab *tab) {
  tabs.PushBack(tab);
  refreshLayout();
}

// Remove Tab
void ESPDash::remove(Tab *tab) {
  for(int i=0; i < tabs.Size(); i++){
    auto *p = tabs[i];
    if(p->getId() == tab->getId()) {
      tabs.Erase(i);
      refreshLayout();
      return;
    }
  }
}

// Add Card
void ESPDash::add(Card *card) {
  home_screen->add(card);
}

// Remove Card
void ESPDash::remove(Card *card) {
  home_screen->remove(card);
}

// Add Chart
void ESPDash::add(Chart *chart) {
  home_screen->add(chart);
}

// Remove Chart
void ESPDash::remove(Chart *chart) {
  home_screen->remove(chart);
}

/* Send Card Updates to all clients */
void ESPDash::sendUpdates() {
  if (!_ws) return; // todo: log error
  if (auto tab = getTab(current_tab_id)) {
    String update;
    ArduinoJson::serializeJson(tab->generateUpdates(false), update);
    _ws->textAll(update);
  } // else todo: log error
}

ESPDash::OnWebServerRequest ESPDash::onWebServerRequest() {
  return [this](AsyncWebServerRequest *request) {
    if(basic_auth){
      if(!request->authenticate(username, password))
        return request->requestAuthentication();
    }
    // respond with the compressed frontend
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", DASH_HTML, DASH_HTML_SIZE);
    response->addHeader("Content-Encoding","gzip");
    request->send(response);
  };
}

ESPDash::OnWebSocketEvent ESPDash::onWebSocketEvent() {
  return [this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    ArduinoJson::StaticJsonDocument<200> json;
    String response;

    if (type == WS_EVT_DATA) {
      AwsFrameInfo * info = (AwsFrameInfo * ) arg;
      if (info -> final && info -> index == 0 && info -> len == len) {
        if (info -> opcode == WS_TEXT) {
          data[len] = 0;
          deserializeJson(json, reinterpret_cast<const char*>(data));
          String command = json["command"];
          // client side commands parsing
          if (command == "getLayout") {
            // When navigating directly it is required to cast the path to tab id
            auto toId = [this](uint32_t& id, const String& path) {
              for (int i = 0; i < tabs.Size(); ++i)
                if (tabs[i]->getName() == path) {
                  id = tabs[i]->getId();
                  return;
                }
            };
            uint32_t id = current_tab_id;
            toId(id, json["goto"].as<String>());
            current_tab_id = id;
            serializeJson(generateLayout(current_tab_id), response);
          }
          else if (command == "ping")
            response = "{\"command\":\"pong\"}";
          else if (command == "getStats")
            response = generateStatsJSON();
          else if (command == "buttonClicked") {
            if (auto tab = getTab(current_tab_id))
              tab->resolveCardCallback(
                      json["id"].as<uint32_t>(),
                      json["value"].as<bool>());
            return;
          } else if (command == "sliderChanged") {
            if (auto tab = getTab(current_tab_id)) {
              tab->resolveCardCallback(
                      json["id"].as<uint32_t>(),
                      json["value"].as<int>());
              serializeJson(tab->generateUpdates(true), response);
            } else return;
          } else if (command == "tabClicked") {
            current_tab_id = json["id"].as<uint32_t>();
            serializeJson(generateLayout(current_tab_id), response);
          }

          // update only requested socket
          _ws->text(client->id(), response);
        }
      }
    }
  };
}

Tab* ESPDash::getTab(uint32_t id) {
  for (int i = 0; i < tabs.Size(); ++i)
    if (tabs[i]->getId() == id) return tabs[i];
  return nullptr;
}

String ESPDash::generateStatsJSON() {
  if (!stats_enabled)
    return String("{\"command\":\"updateStats\", \"statistics\":{\"enabled\":\"false\"}}");

  String stats;
  stats += "\"enabled\":true,";
  #if defined(ESP8266)
  stats += "\"hardware\":\"ESP8266\",";
  stats += "\"sdk\":\"" + ESP.getCoreVersion() + "\",";
  stats += "\"chipId\":\"" + String(ESP.getChipId()) + "\",";
  #elif defined(ESP32)
  stats += "\"hardware\":\"ESP32\",";
  stats += "\"sdk\":\"" + String(esp_get_idf_version()) + "\",";
  stats += "\"chipId\":\"" + String((uint32_t) ESP.getEfuseMac()) + "\",";
  #endif

  stats += "\"sketchHash\":\"" + ESP.getSketchMD5() + "\",";
  stats += "\"macAddress\":\"" + WiFi.macAddress() + "\",";
  stats += "\"freeHeap\":\"" + String(ESP.getFreeHeap()) + "\",";
  stats += "\"wifiMode\":" + String(WiFi.getMode()) + ",";
  stats += "\"wifiSignal\":" + String(WiFi.RSSI());

  return "{\"command\":\"updateStats\", \"statistics\":{" + stats + "}}";
}

ESPDash::JsonDocument ESPDash::generateLayout(uint32_t id) {
  auto tab = getTab(id);

  auto doc = tab ? tab->generateLayout() : home_screen->generateLayout();

  doc["statistics"]["enabled"] = stats_enabled;

  auto jsonTabs = doc.createNestedArray("tabs");
  for(int i = 0; i < tabs.Size(); i++)
    jsonTabs.add(tabs[i]->toJSON());

  return std::move(doc);
}

void ESPDash::refreshLayout() {
  if (_ws)
    _ws->textAll("{\"command\":\"refreshLayout\"}");
}

/*
  Destructor
*/
ESPDash::~ESPDash(){
  _server->removeHandler(_ws);
  delete _ws;
  delete home_screen;
}


