/*
* ESP-DASH V2
* Made by Ayush Sharma
* Github URL: https://github.com/ayushsharma82/ESP-DASH
* Support Me: https://www.patreon.com/asrocks5
*
*
* Core routines rewritten by Cassiano Martin <cassiano.martin@gmail.com>
* Not all functions implemented yet, missing button and slider routines.
* Next step is to reduce json library dependency, in fact we need only a
* parser, and not a full-blown library.
*
*/

#include "ESPDash.h"


/*
  Constructor
*/
ESPDash::ESPDash(AsyncWebServer& server) {
  // Initialize AsyncWebSocket
  ws.reset(new AsyncWebSocket("/dashws"));

  // Attach AsyncWebServer Routes
  server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request){
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
  ws.onEvent([&](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
    StaticJsonDocument<200> json;
    String response;

    if (type == WS_EVT_DATA) {
      AwsFrameInfo * info = (AwsFrameInfo * ) arg;
      if (info -> final && info -> index == 0 && info -> len == len) {
        if (info -> opcode == WS_TEXT) {
          data[len] = 0;
          deserializeJson(json, reinterpret_cast <
            const char * > (data));

          // client side commands parsing
          if (json["command"] == "getLayout")
            response = ESPDash.UpdateLayout();
          else if (json["command"] == "ping")
            response = "{\"response\":\"pong\"}";
          else if (json["command"] == "getStats")
            response = ESPDash.UpdateLayout(true);
          else if (json["command"] == "buttonClicked") {
            // execute and reference card data struct to funtion
            int id = json["id"];
            if (id >= 0 && ESPDash.cards[id].value_ptr != nullptr)
              ESPDash.cards[id].value_ptr( & ESPDash.cards[id]);

            return;
          } else if (json["command"] == "sliderChanged") {
            // execute and reference card data struct to funtion
            int id = json["id"];
            int value = json["value"];
            ESPDash.UpdateCard(id, value);
            if (id >= 0 && ESPDash.cards[id].value_ptr != nullptr)
              ESPDash.cards[id].value_ptr( & ESPDash.cards[id]);

            response = ESPDash.RefreshCards();
          }

          // update only requested socket
          ws.text(client -> id(), response);
        }
      }
    }
  });

  // Attach Websocket Instance to AsyncWebServer
  server.addHandler(&ws);
}


void ESPDash::setAuthentication(const char *user, const char *pass) {
  username = user;
  password = pass;
  basic_auth = true;
  ws.setAuthentication(user, pass);
}


// Add Card
void ESPDash::add(Card *card) {
  cards.PushBack(card);
}

// Remove Card
void ESPDash::remove(Card *card) {
  for(int i=0; i < cards.Size(); i++){
    Card *p = cards[i];
    if(strcmp(p->_id, card->_id) === 0){
      delete cards[i];
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
    if(strcmp(p->_id, chart->_id) === 0){
      delete charts[i];
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
      data += p->generateJSON();
      data += ",";
    }    
  }

  // Remove Last Comma
  data.remove(data.length());
  return "{\"response\":\"updateCards\", ""\"cards\":[" + data + "]}";
}

// generates the layout JSON string to the frontend
String ESPDash::updateLayout(bool only_stats) {
  String data;
  String stats;

  if (stats_enabled) {
    // No need to use json library to build response packet
    stats += "\"enabled\":true,";
    stats += "\"releaseTag\": \"" + String(ESPDASH_RELEASE_TAG) + "\",";
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
    if(p->_changed || toAll){
      p->_changed = false;
      data += p->generateJSON();
      data += ",";
    }    
  }

  // Remove Last Comma
  data.remove(data.length());

  return "{\"response\":\"getLayout\", "
  "\"version\": \"1\", "
  "\"statistics\":{" + stats + "}, "
  "\"cards\":[" + data + "]}";
}

void ESPDash::sendUpdates() {
  ws.textAll(refresh(true));
}
