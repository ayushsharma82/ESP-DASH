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
      if(!request->authenticate(username, password))
      return request->requestAuthentication();
    }
    // respond with the compressed frontend
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", DASH_HTML, sizeof(DASH_HTML));
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Cache-Control", "public, max-age=900");
    request->send(response);
  });

  // Websocket Callback Handler
  _ws->onEvent([&](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
    // Request Buffer
    StaticJsonDocument<200> json;

    if (type == WS_EVT_DATA) {
      AwsFrameInfo * info = (AwsFrameInfo * ) arg;
      if (info -> final && info -> index == 0 && info -> len == len) {
        if (info -> opcode == WS_TEXT) {
          data[len] = 0;
          deserializeJson(json, reinterpret_cast<const char*>(data));
          // client side commands parsing
          if (json["command"] == "get:layout") {
            generateLayoutJSON(client, false);
          } else if (json["command"] == "ping") {
            return _ws->text(client->id(), "{\"command\":\"pong\"}");
          } else if (json["command"] == "get:stats") {
            generateLayoutJSON(client, true);
          } else if (json["command"] == "button:clicked") {
            // execute and reference card data struct to funtion
            uint32_t id = json["id"].as<uint32_t>();
            for(int i=0; i < cards.Size(); i++){
              Card *p = cards[i];
              if(id == p->_id){
                if(p->_callback != nullptr){
                  p->_callback(json["value"].as<int>());
                }
              }
            }
          } else if (json["command"] == "slider:changed") {
            // execute and reference card data struct to funtion
            uint32_t id = json["id"].as<uint32_t>();
            for(int i=0; i < cards.Size(); i++){
              Card *p = cards[i];
              if(id == p->_id){
                if(p->_callback != nullptr){
                  p->_callback(json["value"].as<int>());
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
  basic_auth = strlen(user) > 0 && strlen(pass) > 0;
  if(basic_auth) {
    strncpy(username, user, sizeof(username));
    strncpy(password, pass, sizeof(password));
    _ws->setAuthentication(user, pass);
  }
}

void ESPDash::setAuthentication(const String &user, const String &pass) {
  setAuthentication(user.c_str(), pass.c_str());
}

// Add Card
void ESPDash::add(Card *card) {
  cards.PushBack(card);
  refreshLayout();
}

// Remove Card
void ESPDash::remove(Card *card) {
  for(int i=0; i < cards.Size(); i++){
    Card *p = cards[i];
    if(p->_id == card->_id){
      cards.Erase(i);
      refreshLayout();
      return;
    }
  }
}


// Add Chart
void ESPDash::add(Chart *chart) {
  charts.PushBack(chart);
  refreshLayout();
}

// Remove Card
void ESPDash::remove(Chart *chart) {
  for(int i=0; i < charts.Size(); i++){
    Chart *p = charts[i];
    if(p->_id == chart->_id){
      charts.Erase(i);
      refreshLayout();
      return;
    }
  }
}

// Add Statistic
void ESPDash::add(Statistic *statistic) {
  statistics.PushBack(statistic);
  refreshStatistics();
}

// Remove Statistic
void ESPDash::remove(Statistic *statistic) {
  for(int i=0; i < statistics.Size(); i++){
    Statistic *p = statistics[i];
    if(p->_id == statistic->_id){
      statistics.Erase(i);
      refreshStatistics();
      return;
    }
  }
}

// generates the layout JSON string to the frontend
void ESPDash::generateLayoutJSON(AsyncWebSocketClient *client, bool changes_only, Card *onlyCard) {
  // https://github.com/me-no-dev/ESPAsyncWebServer#limiting-the-number-of-web-socket-clients
  // Browsers sometimes do not correctly close the websocket connection, even when the close() function is called in javascript.
  // This will eventually exhaust the web server's resources and will cause the server to crash.
  // Use DEFAULT_MAX_WS_CLIENTS or DASH_MAX_WS_CLIENTS (specific to ESP-DASH) to set the maximum number of clients
  _ws->cleanupClients();

  const size_t clients = _ws->count();
  
  if (clients == 0) {
    // do not consume cpu and memory if no client is connected
    return;
  }

  StaticJsonDocument<DASH_JSON_SIZE> doc;

  if (!changes_only) {
    doc["command"] = changes_only ? "update:components" : "update:layout:begin";
    send(client, doc);
  }

  // Generate JSON for all Cards
  doc["command"] = changes_only ? "update:components" : "update:layout:next";
  size_t idx = 0;
  for (int i=0; i < cards.Size(); i++) {
    Card *c = cards[i];
    if (changes_only) {
      if (c->_changed) {
        c->_changed = false;
      } else if (onlyCard == nullptr || onlyCard->_id != c->_id) {
        continue;
      }
    }
    // Generate JSON
    JsonObject obj = doc["cards"].createNestedObject();
    generateComponentJSON(obj, c, changes_only);
    
    if (doc.overflowed()) {
      doc["cards"].as<JsonArray>().remove(idx);
      send(client, doc);
#ifdef DASH_DEBUG
    Serial.printf("overflow: %d %s\n", c->_id, c->_name);
#endif
      doc["command"] = changes_only ? "update:components" : "update:layout:next";
      idx = 0;
      JsonObject obj = doc["cards"].createNestedObject();
      generateComponentJSON(obj, c, changes_only);
    }

    idx++;
  }
  if (idx > 0)
    send(client, doc);

  // Generate JSON for all Charts
  doc["command"] = changes_only ? "update:components" : "update:layout:next";
  idx = 0;
  for (int i=0; i < charts.Size(); i++) {
    Chart *c = charts[i];
    if (changes_only) {
      if (c->_changed) {
        c->_changed = false;
      } else {
        continue;
      }
    }
    // Generate JSON
    JsonObject obj = doc["charts"].createNestedObject();
    generateComponentJSON(obj, c, changes_only);

    if (doc.overflowed()) {
      doc["charts"].as<JsonArray>().remove(idx);
      send(client, doc);
#ifdef DASH_DEBUG
    Serial.printf("overflow: %d %s\n", c->_id, c->_name);
#endif
      doc["command"] = changes_only ? "update:components" : "update:layout:next";
      idx = 0;
      JsonObject obj = doc["charts"].createNestedObject();
      generateComponentJSON(obj, c, changes_only);
    }

    idx++;
  }
  if (idx > 0)
    send(client, doc);

  // Generate JSON for all Statistics
  // Check if default statistics are needed
  if (default_stats_enabled) {
    doc["command"] = changes_only ? "update:components" : "update:layout:next";
    idx = 0;

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
    doc["stats"][idx]["v"] = ESP.getFreeHeap();
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
    
    send(client, doc);
  }

  // Loop through user defined stats
  doc["command"] = changes_only ? "update:components" : "update:layout:next";
  idx = 0;
  for (int i=0; i < statistics.Size(); i++) {
    Statistic *s = statistics[i];
    if (changes_only) {
      if (s->_changed) {
        s->_changed = false;
      } else {
        continue;
      }
    }
    doc["stats"][idx]["i"] = s->_id;
    doc["stats"][idx]["k"] = s->_key;
    if(changes_only || strlen(s->_value) > 0)
      doc["stats"][idx]["v"] = s->_value;
    doc["stats"][idx]["v"] = s->_value;

    if (doc.overflowed()) {
      doc["stats"].as<JsonArray>().remove(idx);
      send(client, doc);
#ifdef DASH_DEBUG
    Serial.printf("overflow: %d %s\n", s->_id, s->_key);
#endif
      doc["command"] = changes_only ? "update:components" : "update:layout:next";
      idx = 0;
      
      doc["stats"][idx]["i"] = s->_id;
      doc["stats"][idx]["k"] = s->_key;
      if(changes_only || strlen(s->_value) > 0)
        doc["stats"][idx]["v"] = s->_value;
      doc["stats"][idx]["v"] = s->_value;
    }

    idx++;
  }
  if (idx > 0)
    send(client, doc);
}

void ESPDash::send(AsyncWebSocketClient *client, JsonDocument &json) {
  String buffer;
  buffer.reserve(json.memoryUsage());
  serializeJson(json, buffer);
#ifdef DASH_DEBUG
  Serial.printf("client_id=%d, json_cap=%d, json_mem=%d, len=%d bytes\n%s\n", (client == nullptr ? -1 : client->id()), json.capacity(), json.memoryUsage(), buffer.length(), buffer.c_str());
#endif
  if (client != nullptr) {
    client->text(buffer);
  } else {
    _ws->textAll(buffer);
  }
  json.clear();
}

/*
  Generate Card JSON
*/
void ESPDash::generateComponentJSON(JsonObject& doc, Card* card, bool change_only){
  doc["id"] = card->_id;
  if(!change_only){
    doc["n"] = card->_name.c_str();
    doc["t"] = cardTags[card->_type].type;
    doc["min"] = card->_value_min;
    doc["max"] = card->_value_max;
  }
  if(change_only || !card->_symbol.isEmpty())
    doc["s"] = card->_symbol;

  switch (card->_value_type) {
    case Card::INTEGER:
      doc["v"] = card->_value_i;
      break;
    case Card::FLOAT:
      doc["v"] = String(card->_value_f, 2);
      break;
    case Card::STRING:
      if(change_only || !card->_value_s.isEmpty()) {
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
    doc["n"] = chart->_name.c_str();
    doc["t"] = chartTags[chart->_type].type;
  }

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

/* Send Card Updates to all clients */
void ESPDash::sendUpdates(bool force) {
  generateLayoutJSON(nullptr, !force);
}

void ESPDash::refreshLayout() {
  _ws->textAll("{\"command\":\"refresh:layout\"}");
}

void ESPDash::refreshStatistics() {
  generateLayoutJSON(nullptr, true);
}

void ESPDash::refreshCard(Card *card) {
  generateLayoutJSON(nullptr, true, card);
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
