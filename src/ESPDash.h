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
#include "dash_webpage.h"
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
#include "Card.h"
#include "Chart.h"

// Forward Declaration
class Card;
class Chart;

// ESPDASH Class
class ESPDash{
  private:
    AsyncWebServer* _server = nullptr;
    AsyncWebSocket* _ws = nullptr;

    Vector<Card*> cards;
    Vector<Chart*> charts;
    bool stats_enabled = false;
    bool basic_auth = false;
    const char *username;
    const char *password;

    // Generate layout json
    String generateLayoutJSON(bool only_stats = false);

    // Generate cards/charts update json
    String generateUpdatesJSON(bool force = false);

    // Generate Component JSON
    const String generateComponentJSON(Card* card, bool change_only = false);
    const String generateComponentJSON(Chart* chart, bool change_only = false);

    // This method is called when a card/chart is added or removed
    void refreshLayout();

  public:

    ESPDash(AsyncWebServer* server, bool enable_stats = true);

    // Set Authentication
    void setAuthentication(const char *user, const char *pass);

    // Add Card
    void add(Card *card);
    // Remove Card
    void remove(Card *card);

    // Add Chart
    void add(Chart *card);
    // Remove Chart
    void remove(Chart *card);

    // Notify client side to update values
    void sendUpdates(bool force = false);
  
    ~ESPDash();
};

#endif
