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
#include "Card.h"
#include "Chart.h"


class ESPDash{
  private:
    AsyncWebSocket* ws = nullptr;

    Vector<Card*> cards;
    Vector<Chart*> charts;
    bool stats_enabled = true;
    bool basic_auth = false;
    const char *username;
    const char *password;

  public:
    ESPDash(AsyncWebServer& server);

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
    void sendUpdates();

    // send generated layout json to client side
    String updateLayout(bool only_stats = false);

    // send generated update json to client side
    String refresh(bool toAll = false);

    ~ESPDash();
};

#endif
