/*
* ESP-DASH V2
* Made by Ayush Sharma
* Github URL: https://github.com/ayushsharma82/ESP-DASH
* Support Me: https://www.patreon.com/asrocks5
*
* - Version Changelog - 
* V1.0.0 - 11 Nov. 2017 - Library was Born
* V1.0.1 - 13 Nov. 2017 - Fixed Empty SPIFFS Issue
* V1.0.2 - 13 Nov. 2017 - Improvements on SPIFFS Issue
* V1.0.3 - 24 Dec. 2017 - Pushing to Library Manager
*
* = Library Rewritten! =
* V2.0.0 - 25 Jan 2019 - Wohoo! A breakthrough in performance and capabilities!
*
* 
* Credits:
* Malcolm Brook (https://github.com/malbrook) for Slider Card
*
*
* Core routines rewritten by Cassiano Martin <cassiano.martin@gmail.com>
* Not all functions implemented yet, missing button and slider routines.
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
    std::unique_ptr<AsyncWebSocket> ws;

    Vector<Card*> cards;
    Vector<Chart*> charts;
    bool stats_enabled = true;
    bool basic_auth = false;
    const char *username;
    const char *password;

    // Async WebSocket event callback function
    static void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

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
