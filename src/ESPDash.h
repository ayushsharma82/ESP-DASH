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

#if defined(ESP8266)
  #define DASH_HARDWARE "ESP8266"
  #include "ESP8266WiFi.h"
  #include "ESPAsyncTCP.h"
#elif defined(ESP32)
  #define DASH_HARDWARE "ESP32"
  #include "WiFi.h"
  #include "AsyncTCP.h"
#elif defined(TARGET_RP2040) || defined(PICO_RP2040)
  #define DASH_HARDWARE "RP2040"
  #include "WiFi.h"
  #include "RPAsyncTCP.h"
#elif defined(TARGET_RP2350) || defined(PICO_RP2350)
  #define DASH_HARDWARE "RP2350"
  #include "WiFi.h"
  #include "RPAsyncTCP.h"
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

#include <vector>

// If DASH_JSON_SIZE is set to a value, ESP-DASH will frequently measure the Json payload to make sure it remains within this size.
// If the Json payload to send is larger, the payload will be split in several parts and sent in multiple messages.
//
// When this value is set:
// - it should not be too large to avoid sending a big message, which takes longer to send and to build because of the frequent json size measurements. 4096 and 8192 are good values for large dashboards.
// - it should not be too small to avoid sending too many messages, which can slow down the dashboard rendering and fill the websocket message queue. 2048 is a good minimum value.
//
// When using ArduinoJson 7, you can set this value to 0 (by default) to disable the websocket message fragmentation in smaller parts and to disable the measurements, to improve performance.
// This will speed up the rendering, at the expense of risking to exhaust the heap in the case of large dashboard.
// To workaround that, when using DASH_JSON_SIZE == 0 with ArduinoJson 7, you can also set DASH_MIN_FREE_HEAP to a value which is more than the size of the biggest payload for your dashboard.
// For example, if your app is big and has a payload sie of 12kb, then you can set DASH_MIN_FREE_HEAP to 16384 (16kb) to make sure the heap is never exhausted.
// When DASH_MIN_FREE_HEAP is set to a value, you instruct ESP-DASH to check the free heap to make sure there is enough heap to send the payload.
//
// In summary:
//
// - With ArduinoJson 6: DASH_JSON_SIZE should be set to a value greater than 0 and fragmentation is used.
// - With ArduinoJson 7: DASH_JSON_SIZE can be set to 0 to disable the fragmentation and the measurements, at the risk of going out of heap. This option gives the best performance but you need to make sure to have enough heap in case your application is large.
// - With ArduinoJson 7: if DASH_JSON_SIZE is set to 0 and DASH_MIN_FREE_HEAP is set to a value greater than 0, heap will be checked before sending the payload and fragmentation will trigger if not enough heap..
// - DASH_MIN_FREE_HEAP will have no effect is DASH_JSON_SIZE is not set to 0
// 
// To help you decide, you can uncomment line 543 in the cpp which will display the free heap size and teh required heap size to build the websocket message.
// ESP_LOGW("ESPDash", "Required Heap size to build WebSocket message: %d bytes. Free Heap: %" PRIu32 " bytes", len, ESP.getFreeHeap());
#ifndef DASH_JSON_SIZE
#if ARDUINOJSON_VERSION_MAJOR == 6 && !defined(DASH_JSON_DOCUMENT_ALLOCATION)
#define DASH_JSON_SIZE 2048
#else
#define DASH_JSON_SIZE 0
#endif // ARDUINOJSON_VERSION_MAJOR == 6 && !defined(DASH_JSON_DOCUMENT_ALLOCATION)
#endif // DASH_JSON_SIZE

// Only for ArduinoJson 7
#ifndef DASH_MIN_FREE_HEAP
#define DASH_MIN_FREE_HEAP 0
#endif

#if ARDUINOJSON_VERSION_MAJOR == 6 && !defined(DASH_JSON_DOCUMENT_ALLOCATION)
#if DASH_JSON_SIZE == 0
#error "DASH_JSON_SIZE must be set to a value greater than 0 when using ArduinoJson 6"
#endif
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
  public:
    // changes_only: true (equivalent to sendUpdates(false)) - when sending updates to the client
    // changes_only: false (equivalent to sendUpdates(true)) - when sending the entire layout to the client or when forcing a full update
    typedef std::function<void(bool changes_only)> BeforeUpdateCallback;

  private:
    AsyncWebServer* _server = nullptr;
    AsyncWebSocket* _ws = nullptr;

    std::vector<Card*> cards;
    std::vector<Chart*> charts;
    std::vector<Statistic*> statistics;
    bool default_stats_enabled = false;
    bool basic_auth = false;
    dash::string username;
    dash::string password;
    uint32_t _idCounter = 0;
    BeforeUpdateCallback _beforeUpdateCallback = nullptr;

    volatile bool _asyncAccessInProgress = false;

    // Generate layout json
    void generateLayoutJSON(AsyncWebSocketClient* client, bool changes_only = false, Card* onlyCard = nullptr, Chart* onlyChart = nullptr);
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
    void setAuthentication(const dash::string &user, const dash::string &pass);

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
    void refreshChart(Chart* chart);

    uint32_t nextId();

    bool hasClient();

    // can be used to check if the async_http task might currently access the cards data, 
    // in which case you should not modify them
    bool isAsyncAccessInProgress() { return _asyncAccessInProgress; }

    // Register a callback that will be called before some updates will be sent to the client.
    // This callback can be used for example to refresh some card values that never change after only when a full layout is request (i.e. on page reload).
    // This allows to avoid spending time refreshing cards that never change, but still allows them to be refreshed hen the user refresh the dashboard.
    // If called from the async_http task, isAsyncAccessInProgress() will return true while in this callback.
    void onBeforeUpdate(BeforeUpdateCallback callback) { _beforeUpdateCallback = callback; }

    ~ESPDash();
};

#endif
