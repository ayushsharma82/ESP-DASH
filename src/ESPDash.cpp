#include "ESPDash.h"

/*
  Constructor
*/
ESPDash::ESPDash(AsyncWebServer* server) {
  _server = server;

  // Initialize AsyncWebSocket
  _ws = new AsyncWebSocket("/dashws");

  // Attach AsyncWebServer Routes
  _server->on("/", HTTP_GET, [this](AsyncWebServerRequest *request){
    if(basic_auth){
      if(!request->authenticate(username, password))
      return request->requestAuthentication();
    }
    // respond with the compressed frontend
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", DASH_HTML, DASH_HTML_SIZE);
    response->addHeader("Content-Encoding","gzip");
    request->send(response);        
  });

  // Websocket Callback Handler
  _ws->onEvent([&](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
    StaticJsonDocument<200> json;
    String response;

    if (type == WS_EVT_DATA) {
      AwsFrameInfo * info = (AwsFrameInfo * ) arg;
      if (info -> final && info -> index == 0 && info -> len == len) {
        if (info -> opcode == WS_TEXT) {
          data[len] = 0;
          deserializeJson(json, reinterpret_cast<const char*>(data));
          // client side commands parsing
          if (json["command"] == "getLayout")
            response = updateLayout();
          else if (json["command"] == "ping")
            response = "{\"response\":\"pong\"}";
          else if (json["command"] == "getStats")
            response = updateLayout(true);
          else if (json["command"] == "buttonClicked") {
            // execute and reference card data struct to funtion
            uint32_t id = json["id"].as<uint32_t>();
            for(int i=0; i < cards.Size(); i++){
              Card *p = cards[i];
              if(id == p->_id){
                if(p->_btn_callback != nullptr){
                  p->_btn_callback(json["value"].as<bool>());
                }
              }
            }
            return;
          } else if (json["command"] == "sliderChanged") {
            // execute and reference card data struct to funtion
            uint32_t id = json["id"].as<uint32_t>();
            for(int i=0; i < cards.Size(); i++){
              Card *p = cards[i];
              if(id == p->_id){
                if(p->_slider_callback != nullptr){
                  p->_slider_callback(json["value"].as<int>());
                }
              }
            }
            response = refresh();
          }

          // update only requested socket
          _ws->text(client->id(), response);
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
  basic_auth = true;
  _ws->setAuthentication(user, pass);
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


// push updates to all connected clients
String ESPDash::refresh(bool toAll) {
  String data;

  // Generate JSON for all changed Cards
  for (int i=0; i < cards.Size(); i++) {
    Card *p = cards[i];
    if(p->_changed || toAll){
      p->_changed = false;
      data += p->generateJSON(true);
      data += ",";
    }    
  }

  // Remove Last Comma
  data.remove(data.length()-1);

  return "{\"response\":\"updateCards\", ""\"cards\":[" + data + "]}";
}

// generates the layout JSON string to the frontend
String ESPDash::updateLayout(bool only_stats) {
  String data;
  String stats;

  if (stats_enabled) {
    // No need to use json library to build response packet
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
  } else
    stats = "\"enabled\":\"false\",";

  // only status has been requested
  if (only_stats) {
    return "{\"response\":\"getStats\", "
    "\"statistics\":{" + stats + "}}";
  }

  // Generate JSON for all changed Cards
  for (int i=0; i < cards.Size(); i++) {
    Card *p = cards[i];
    p->_changed = false;
    data += p->generateJSON();
    data += ",";
  }

  // Remove Last Comma
  data.remove(data.length()-1);

  return "{\"response\":\"getLayout\", "
  "\"version\": \"1\", "
  "\"statistics\":{" + stats + "}, "
  "\"cards\":[" + data + "]}";
}

void ESPDash::sendUpdates() {
  _ws->textAll(refresh(true));
}


/*
  Destructor
*/
ESPDash::~ESPDash(){
  _server->removeHandler(_ws);
  delete _ws;
  delete _server;
}