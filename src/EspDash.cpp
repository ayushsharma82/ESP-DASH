#include "EspDash.h"

#include <functional>
using namespace std;
using namespace std::placeholders;

ESP8266WebServer server(80);     // Create Unique Instance for Webserver
ESP8266HTTPUpdateServer httpUpdater;

void EspDashClass::handleRebootImage(){
    File file = SPIFFS.open("/dash/img/loading.png", "r");
    server.sendHeader("Cache-Control", "max-age=2628000,public");
    server.streamFile(file, "image/png");
    file.close();
}

void EspDashClass::handleLogo(){
    File file = SPIFFS.open("/dash/img/logo.png", "r");
    server.sendHeader("Cache-Control", "max-age=2628000,public");
    server.streamFile(file, "image/png");
    file.close();
}

void EspDashClass::handleUpdateImage(){
    File file = SPIFFS.open("/dash/img/serverupdate.png", "r");
    server.sendHeader("Cache-Control", "max-age=2628000,public");
    server.streamFile(file, "image/png");
    file.close();
}

void EspDashClass::handleWifiImage(){
    File file = SPIFFS.open("/dash/img/wifi.png", "r");
    server.sendHeader("Cache-Control", "max-age=2628000,public");
    server.streamFile(file, "image/png");
    file.close();
}

void EspDashClass::handleRootPage(){
    File file = SPIFFS.open("/dash/index.html.gz", "r");
    server.streamFile(file, "text/html");
    file.close();
}

void EspDashClass::handleUpdatePage(){
    File file = SPIFFS.open("/dash/update.html.gz", "r");
    server.streamFile(file, "text/html");
    file.close();
}

void EspDashClass::handleSettingsPage(){
    File file = SPIFFS.open("/dash/settings.html.gz", "r");
    server.streamFile(file, "text/html");
    file.close();
}

void EspDashClass::handleCSS(){
    File file = SPIFFS.open("/dash/css/style.css.gz", "r");
    server.streamFile(file, "text/css");
    file.close();
}

void EspDashClass::handleJS(){
    File file = SPIFFS.open("/dash/js/script.js.gz", "r");
    server.streamFile(file, "application/javascript");
    file.close();
}

void EspDashClass::addTab(const char* _tabName, String _value){
    if(tabCount > TABS_LIMIT) return;

    tabName[tabCount] = _tabName;
    tabData[tabCount] = _value;
    tabCount++;
}

void EspDashClass::addTab(const char* _tabName, int _value){
    if(tabCount > TABS_LIMIT) return;

    tabName[tabCount] = _tabName;
    tabData[tabCount] = String(_value);
    tabCount++;
}

void EspDashClass::updateTab(const char* _tabName, String _value){
    for(int i; i < tabCount; i++){
        if(tabName[i] == _tabName){
            tabData[i] = _value;
        }
    }
}

void EspDashClass::updateTab(const char* _tabName, int _value){
    for(int i; i < tabCount; i++){
        if(tabName[i] == _tabName){
            tabData[i] = String(_value);
        }
    }
}

void EspDashClass::handleReboot(){
    server.send(200, "application/json", "{'status' : 'ok'}");
    if(_debug){
      Serial.println("[ESP-DASH]: Got Reboot Command. Rebooting...");
    }
    ESP.restart();
}

void EspDashClass::handleRootJSON(){
    StaticJsonBuffer<800> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    if(WiFi.status() == WL_CONNECTED){
      root["wifiStatus"] = 1;
      root["wifiSSID"] = WiFi.SSID();
    }else{
      root["wifiStatus"] = 0;
    }
    int heap = ESP.getFreeHeap();

    int free_heap_percentage = 100 * heap/98000;
    int consumed_heap_percentage = 100 - free_heap_percentage;

    root["usedHeap"] = String(consumed_heap_percentage)+"%";

    JsonArray& data = root.createNestedArray("userTab");
    if(tabCount >= 1){
        for(int i=0; i < tabCount; i++){
           JsonObject& object = data.createNestedObject();
           object["tabName"] = tabName[i];
           object["tabValue"] = tabData[i];
        }
    }

    String json = "";
    root.printTo(json);
    server.send(200, "application/json", json);
}

void EspDashClass::handleSettingsUpdate(){
    if(server.argName(0) == "ssid" && server.argName(1) == "password"){
        String new_SSID = "";
        String new_PASS = "";

        new_SSID = server.arg(0);
        new_PASS = server.arg(1);

        if(_debug){
          Serial.println("[ESP-DASH]: Got WiFi Switch Command.");
        }

      if(new_SSID != ""){
        if(wifiBackup(new_SSID.c_str(), new_PASS.c_str())){
          server.send(200, "application/json", "{'status' : 'ok'}");
          if(_debug){
            Serial.println("[ESP-DASH]: New SSID - "+new_SSID);
            Serial.println("[ESP-DASH]: New PASSWORD - "+new_PASS);
            Serial.println("[ESP-DASH]: Rebooting...");
          }
          ESP.restart();
        }else{
          server.send(200, "application/json", "{'status' : 'ko'}");
          if(_debug){
            Serial.println("[ESP-DASH]: Failed...");
          }
        }
      }else{
        server.send(200, "application/json", "{'status' : 'ko'}");
        if(_debug){
          Serial.println("[ESP-DASH]: Failed...");
        }
      }
    }
}

bool EspDashClass::wifiBackup(const char* _ssid, const char* _pass){
  if(_ssid != ""){
    File f = SPIFFS.open("/dash/wifi/ssid.txt", "w");
    if (!f) return false;
    f.print(_ssid);
    f.close();

    File v = SPIFFS.open("/dash/wifi/pass.txt", "w");
    if (!v) return false;
    v.print(_pass);
    v.close();

    return true;
  }else{
    return false;
  }
}

bool EspDashClass::wifiRestore(){
    if(SPIFFS.exists("/dash/wifi/ssid.txt") && SPIFFS.exists("/dash/wifi/pass.txt")){
        File f = SPIFFS.open("/dash/wifi/ssid.txt", "r");    // Get SSID
        if(!f) return false;
        String doc = "";
            while(f.available()){
              doc += char(f.read());
            }
        _SSID = doc.c_str();
        f.close();

        File v = SPIFFS.open("/dash/wifi/pass.txt", "r");    // Get PASSWORD
        if(!v) return false;
        String doc2 = "";
            while(v.available()){
              doc2 += char(v.read());
            }
        _PASS = doc2.c_str();
        v.close();

        if(doc == ""){
          return false;
        }
        else{
          return true;
        }
    }else{
        return false; // Return False incase SSID / PASSWORD Missing.
    }
}

void EspDashClass::debug(bool stat){
  _debug = stat;
}

void EspDashClass::begin(const char* _ssid, const char* _pass){
    SPIFFS.begin();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);

    if(wifiRestore()){
      WiFi.begin(_SSID, _PASS);     // Restored SSID and Pass
      if(_debug){
        Serial.println("");
        Serial.println("[ESP-DASH]: Recovered WiFi Credentials.");
        Serial.println("[ESP-DASH]: Recovered SSID - "+String(_SSID));
        Serial.println("[ESP-DASH]: Recovered PASSWORD - "+String(_PASS));
        Serial.print("[ESP-DASH]: Connecting to WiFi..");
      }
    }else{
      _SSID = _ssid;
      _PASS = _pass;
      WiFi.begin(_SSID, _PASS);     // Base SSID & Pass
      if(_debug){
        Serial.println("");
        Serial.println("[ESP-DASH]: Using Base WiFi Credentials.");
        Serial.println("[ESP-DASH]: SSID - "+String(_SSID));
        Serial.println("[ESP-DASH]: PASSWORD - "+String(_PASS));
        Serial.print("[ESP-DASH]: Connecting to WiFi..");
      }
    }

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      if(_debug){
        Serial.print(".");
      }
    }

    if(_debug){
      Serial.println("");
      Serial.println("[ESP-DASH]: Started ESP-DASH Server.");
      Serial.print("[ESP-DASH]: IP Address - ");
      Serial.print(WiFi.localIP());
      Serial.println("");
    }

    server.on("/", std::bind(&EspDashClass::handleRootPage, this));
    server.on("/dash", std::bind(&EspDashClass::handleRootPage, this));
    server.on("/settings", std::bind(&EspDashClass::handleSettingsPage, this));
    server.on("/update", HTTP_GET,std::bind(&EspDashClass::handleUpdatePage, this));
    server.on("/dash/data.json", std::bind(&EspDashClass::handleRootJSON, this));
    server.on("/dash/settings.json", std::bind(&EspDashClass::handleSettingsUpdate, this));
    server.on("/dash/reboot", std::bind(&EspDashClass::handleReboot, this));
    server.on("/css/style.css", std::bind(&EspDashClass::handleCSS, this));
    server.on("/js/script.js", std::bind(&EspDashClass::handleJS, this));
    server.on("/img/loading.png", std::bind(&EspDashClass::handleRebootImage, this));
    server.on("/img/wifi.png", std::bind(&EspDashClass::handleWifiImage, this));
    server.on("/img/serverupdate.png", std::bind(&EspDashClass::handleUpdateImage, this));
    server.on("/img/logo.png", std::bind(&EspDashClass::handleLogo, this));

    httpUpdater.setup(&server, "/update");

    server.begin();
}

void EspDashClass::loop(){
    server.handleClient();
}

EspDashClass EspDash;
