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
    #define DASH_HARDWARE "ESP8266"
    #include "ESP8266WiFi.h"
    #include "ESPAsyncTCP.h"
#elif defined(ESP32)
    #define DASH_HARDWARE "ESP32"
    #include "WiFi.h"
    #include "AsyncTCP.h"
#endif

#define DASH_STATUS_IDLE "i"
#define DASH_STATUS_SUCCESS "s"
#define DASH_STATUS_WARNING "w"
#define DASH_STATUS_DANGER "d"

#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "Card.h"
#include "Chart.h"
#include "Statistic.h"

#ifndef DASH_JSON_SIZE
#define DASH_JSON_SIZE 2048
#endif

#if ARDUINOJSON_VERSION_MAJOR == 6 && !defined(DASH_JSON_DOCUMENT_ALLOCATION)
#define DASH_JSON_DOCUMENT_ALLOCATION DASH_JSON_SIZE * 3
#endif

#ifndef DASH_USE_LEGACY_CHART_STORAGE
  #define DASH_USE_LEGACY_CHART_STORAGE 0
#endif

#ifndef DASH_MAX_WS_CLIENTS
  #define DASH_MAX_WS_CLIENTS DEFAULT_MAX_WS_CLIENTS
#endif

// Forward Declaration
class Card;
class Chart;
class Statistic;

// ESPDASH Class
class ESPDash{
  private:
    AsyncWebServer* _server = nullptr;
    AsyncWebSocket* _ws = nullptr;

    Vector<Card*> cards;
    Vector<Chart*> charts;
    Vector<Statistic*> statistics;
    bool default_stats_enabled = false;
    bool basic_auth = false;
    char username[64];
    char password[64];
    uint32_t _idCounter = 0;

    volatile bool _asyncAccessInProgress = false;

    // Generate layout json
    void generateLayoutJSON(AsyncWebSocketClient* client, bool changes_only = false, Card* onlyCard = nullptr);
    void send(AsyncWebSocketClient* client, JsonDocument& doc);
    bool overflowed(JsonDocument& doc);

    // Generate Component JSON
    void generateComponentJSON(JsonObject& obj, Card* card, bool change_only = false);
    void generateComponentJSON(JsonObject& obj, Chart* chart, bool change_only = false);

  public:
    ESPDash(AsyncWebServer* server, const char* uri, bool enable_default_stats = true);
    ESPDash(AsyncWebServer* server, bool enable_default_stats);
    ESPDash(AsyncWebServer* server);

    // Set Authentication
    void setAuthentication(const char* user, const char* pass);
    void setAuthentication(const String &user, const String &pass);

    // Add Card
    void add(Card *card);
    // Remove Card
    void remove(Card *card);

    // Add Chart
    void add(Chart *card);
    // Remove Chart
    void remove(Chart *card);

    // Add Statistic
    void add(Statistic *statistic);
    // Remove Statistic
    void remove(Statistic *statistic);

    // Notify client side to update values
    void sendUpdates(bool force = false);
    void refreshLayout() { sendUpdates(true); }
    void refreshCard(Card *card);

    uint32_t nextId();

    bool hasClient();

    // can be used to check if the async_http task might currently access the cards data, 
    // in which case you should not modify them
    bool isAsyncAccessInProgress() { return _asyncAccessInProgress; }

    ~ESPDash();
};

#endif
