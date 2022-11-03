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
  Constructor
*/
ESPDash::ESPDash(AsyncWebServer* server, bool enable_default_stats) {
  _server = server;
  default_stats_enabled = enable_default_stats;

  // Initialize AsyncWebSocket
  _ws = new AsyncWebSocket("/dashws");

  // Attach AsyncWebServer Routes
  _server->on("/", HTTP_GET, [this](AsyncWebServerRequest *request){
    if(basic_auth){
      if(!request->authenticate(username, password))
      return request->requestAuthentication();
    }
    // respond with the compressed frontend
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", DASH_HTML, sizeof(DASH_HTML));
    response->addHeader("Content-Encoding","gzip");
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
            Serial.println("Got get:layout");
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
            return;
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
            return;
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
  basic_auth = true;
  _ws->setAuthentication(user, pass);
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
size_t ESPDash::generateLayoutJSON(AsyncWebSocketClient *client, bool changes_only) {
  String buf = "";
  buf.reserve(DASH_LAYOUT_JSON_SIZE);

  if (changes_only) {
    buf += "{\"command\":\"update:components\",";
  } else {
    buf += "{\"command\":\"update:layout\",";
  }
  
  buf += "\"cards\":[";

  StaticJsonDocument<DASH_CARD_JSON_SIZE> carddoc;
  uint8_t card_count = 0;
  // Generate JSON for all Cards
  for (int i=0; i < cards.Size(); i++) {
    Card *c = cards[i];
    if (changes_only) {
      if (c->_changed) {
        c->_changed = false;
      } else {
        continue;
      }
    }
    if (card_count > 0) {
      buf += ",";
    }
    // Generate JSON
    JsonObject obj = carddoc.to<JsonObject>();
    generateComponentJSON(obj, c, changes_only);
    // Append to buf
    serializeJson(carddoc, buf);
    carddoc.clear();
    card_count++;
  }

  buf += "],\"charts\":[";

  DynamicJsonDocument chartdoc(DASH_CHART_JSON_SIZE);
  uint8_t chart_count = 0;
  // Generate JSON for all Charts
  for (int i=0; i < charts.Size(); i++) {
    Chart *c = charts[i];
    if (changes_only) {
      if (c->_changed) {
        c->_changed = false;
      } else {
        continue;
      }
    }
    if (chart_count > 0) {
      buf += ",";
    }
    // Generate JSON
    JsonObject obj = chartdoc.to<JsonObject>();
    generateComponentJSON(obj, c, changes_only);
    // Append to buf
    serializeJson(chartdoc, buf);
    chartdoc.clear();
    chart_count++;
  }

  buf += "],\"stats\": [";

  // Generate JSON for all Statistics
  // Check if default statistics are needed
  if (default_stats_enabled) {
    // Hardware
    StaticJsonDocument<64> hardware;
    hardware["k"] = "Hardware";
    hardware["v"] = DASH_HARDWARE;
    serializeJson(hardware, buf);
    buf += ",";

    // SDK Version
    StaticJsonDocument<64> sdk;
    sdk["k"] = "SDK Version";
    #if defined(ESP8266)
      sdk["v"] = ESP.getCoreVersion();
    #elif defined(ESP32)
      sdk["v"] = String(esp_get_idf_version());
    #endif
    serializeJson(sdk, buf);
    buf += ",";

    // MAC Address
    StaticJsonDocument<64> mac;
    mac["k"] = "MAC Address";
    mac["v"] = WiFi.macAddress();
    serializeJson(mac, buf);
    buf += ",";

    // Free Heap
    StaticJsonDocument<64> heap;
    heap["k"] = "Free Heap (SRAM)";
    heap["v"] = ESP.getFreeHeap();
    serializeJson(heap, buf);
    buf += ",";

    // WiFi Mode
    StaticJsonDocument<64> wmode;
    wmode["k"] = "WiFi Mode";
    wmode["v"] = WiFi.getMode();
    serializeJson(wmode, buf);
    buf += ",";

    // WiFi Signal
    StaticJsonDocument<64> signal;
    signal["k"] = "WiFi Signal";
    signal["v"] = WiFi.RSSI();
    serializeJson(signal, buf);
  }

  // Loop through user defined stats
  StaticJsonDocument<128> obj;
  for (int i=0; i < statistics.Size(); i++) {
    Statistic *s = statistics[i];
    if (changes_only) {
      if (s->_changed) {
        s->_changed = false;
      } else {
        continue;
      }
    }
    buf += ",";
    obj["k"] = s->_key;
    obj["v"] = s->_value;
    serializeJson(obj, buf);
    obj.clear();
  }

  buf += "]";

  // Close JSON
  buf += "}";

  // Store the length of the JSON string
  size_t total = buf.length();
  // Send resp
  if (client != nullptr) {
    _ws->text(client->id(), buf.c_str(), total);
  } else {
    _ws->textAll(buf.c_str(), total);
  }

  // Serial.println("Free Heap (During Update): "+String( ESP.getFreeHeap() ));
  // Return length
  return total;
}


/*
  Generate Card JSON
*/
void ESPDash::generateComponentJSON(JsonObject& doc, Card* card, bool change_only){
  doc["id"] = card->_id;
  if(!change_only){
    doc["name"] = card->_name;
    doc["type"] = cardTags[card->_type].type;
    doc["value_min"] = card->_value_min;
    doc["value_max"] = card->_value_max;
  }
  doc["symbol"] = card->_symbol;

  switch (card->_value_type) {
    case Card::INTEGER:
      doc["value"] = card->_value_i;
      break;
    case Card::FLOAT:
      doc["value"] = String(card->_value_f, 2);
      break;
    case Card::STRING:
      doc["value"] = card->_value_s;
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
    doc["name"] = chart->_name;
    doc["type"] = chartTags[chart->_type].type;
  }

  JsonArray xAxis = doc["x_axis"].to<JsonArray>();
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
  
  JsonArray yAxis = doc["y_axis"].to<JsonArray>();
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
  _ws->textAll("{\"command\":\"refreshLayout\"}");
}

void ESPDash::refreshStatistics() {
  generateLayoutJSON(nullptr, true);
}


/*
  Destructor
*/
ESPDash::~ESPDash(){
  _server->removeHandler(_ws);
  delete _ws;
}