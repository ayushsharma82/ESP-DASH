#include "ESPDash.h"

/*
  Constructor
*/
ESPDash::ESPDash(AsyncWebServer* server, bool enable_stats):
  _server(server),
  stats_enabled(enable_stats)
{
  // Initialize AsyncWebSocket
  _ws = new AsyncWebSocket("/dashws");

  home_screen = new Tab(this, "Home", "Overview", "");
  // Attach AsyncWebServer Routes
  _server->on("/", HTTP_GET, onWebServerRequest());

  // Websocket Callback Handler
  _ws->onEvent(onWebSocketEvent());

  // Attach Websocket Instance to AsyncWebServer
  _server->addHandler(_ws);
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
    StaticJsonDocument<200> json;
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
            auto toId = [this](uint32_t& id, const String& path) -> bool {
              for (int i = 0; i < tabs.Size(); ++i)
                if (tabs[i]->getName() == path) {
                  id = tabs[i]->getId();
                  return true;
                }
              return false;
            };
            uint32_t id;
            if (toId(id, json["goto"].as<String>()))
              serializeJson(generateLayout(&id), response);
            else
              serializeJson(generateLayout(), response);
          }
          else if (command == "ping")
            response = "{\"command\":\"pong\"}";
          else if (command == "getStats")
            response = generateStatsJSON();
          else if (command == "buttonClicked") {
            home_screen->resolveCardCallback(
                    json["id"].as<uint32_t>(),
                    json["value"].as<bool>());
            return;
          } else if (command == "sliderChanged") {
            home_screen->resolveCardCallback(
                    json["id"].as<uint32_t>(),
                    json["value"].as<int>());
            serializeJson(home_screen->generateUpdates(true), response);
          } else if (command == "tabClicked") {
            auto id = json["id"].as<uint32_t>();
            serializeJson(generateLayout(&id), response);
          }

          // update only requested socket
          _ws->text(client->id(), response);
        }
      }
    }
  };
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

/* Send Card Updates to all clients */
void ESPDash::sendUpdates() {
  String update;
  serializeJson(home_screen->generateUpdates(false), update);
  _ws->textAll(update);
}

ESPDash::JsonDocument ESPDash::generateLayout(uint32_t* id) {
  auto findTab = [this](uint32_t* id) -> Tab* {
    if (!id) return nullptr;
    for (int i = 0; i < tabs.Size(); ++i)
      if (tabs[i]->getId() == *id)
        return tabs[i];
    return nullptr;
  };

  auto tab = findTab(id);

  auto doc = tab ? tab->generateLayout() : home_screen->generateLayout();

  doc["statistics"]["enabled"] = stats_enabled;

  auto jsonTabs = doc.createNestedArray("tabs");
  for(int i = 0; i < tabs.Size(); i++)
    jsonTabs.add(tabs[i]->toJSON());

  return std::move(doc);
}

void ESPDash::refreshLayout() {
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