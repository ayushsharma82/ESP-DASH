/*
____ ____ ___  ___  ____ ____ _  _ 
|___ [__  |__] |  \ |__| [__  |__| 
|___ ___] |    |__/ |  | ___] |  | 
                                   
ESP-DASH V3
---------------------
Author: Ayush Sharma
First Commit: Nov 5, 2017
Github URL: https://github.com/ayushsharma82/ESP-DASH

*/

#ifndef ESPDash_h
#define ESPDash_h

#include <functional>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Arduino.h"
#include "stdlib_noniso.h"
#include "webpage.h"
#include "vector.h"

#if defined(ESP8266)
    #define HARDWARE "ESP8266"
    #include "ESP8266WiFi.h"
    #include "ESPAsyncTCP.h"
#elif defined(ESP32)
    #define HARDWARE "ESP32"
    #include "WiFi.h"
    #include "AsyncTCP.h"
#endif

#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "Widget.h"
#include "Card.h"
#include "Chart.h"
#include "Tab.h"


// ESPDASH Class
class ESPDash{
  private:
    AsyncWebServer* _server = nullptr;
    AsyncWebSocket* _ws = nullptr;

    Vector<Tab*> tabs;
    Tab* home_screen;
    bool stats_enabled = false;
    bool basic_auth = false;
    const char *username;
    const char *password;

    using OnWebServerRequest = std::function<void(AsyncWebServerRequest*)>;
    OnWebServerRequest onWebServerRequest();
    using OnWebSocketEvent = std::function<void(
            AsyncWebSocket*,
            AsyncWebSocketClient*,
            AwsEventType,
            void*,
            uint8_t*,
            size_t)>;
     OnWebSocketEvent onWebSocketEvent();

    // Generate statistics layout json
    String generateStatsJSON();

    using JsonDocument = Widget::JsonDocument;
    JsonDocument generateLayout(uint32_t* id = nullptr);

    // This method is called when a card/chart is added or removed
    void refreshLayout();

  public:

    ESPDash(AsyncWebServer* server, bool enable_stats = true);

    // Set Authentication
    void setAuthentication(const char *user, const char *pass);

    // Add Tab
    void add(Tab *tab);
    // Remove Tab
    void remove(Tab *tab);

    // Add Card
    void add(Card *card);
    // Remove Card
    void remove(Card *card);

    // Add Chart
    void add(Chart *chart);
    // Remove Chart
    void remove(Chart *chart);

    // Notify client side to update values
    void sendUpdates();
  
    ~ESPDash();

    friend class Tab;
};

#endif
