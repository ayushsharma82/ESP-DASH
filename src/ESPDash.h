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
    #include "ESPAsyncWebServer.h"
    #include "ArduinoJson.h"
#elif defined(ESP32)
    #define HARDWARE "ESP32"
    #include <esp_int_wdt.h>
    #include <esp_task_wdt.h>
    #include "WiFi.h"
    #include "AsyncTCP.h"
    #include "ESPAsyncWebServer.h"
    #include "ArduinoJson.h"
#endif

// functions defaults to zero (number card)
enum {
    TYPE_NUMBER_CARD,
    TYPE_BUTTON_CARD,
    TYPE_TEMPERATURE_CARD,
    TYPE_HUMIDITY_CARD,
    TYPE_STATUS_CARD,
    TYPE_LINE_CARD,
    TYPE_GAUGE_CARD,
    TYPE_SLIDER_CARD
};

enum {
    CARD_0,
    CARD_1,
    CARD_2,
    CARD_3,
    CARD_4,
    CARD_5,
    CARD_6,
    CARD_7,
    CARD_8,
    CARD_9,
    CARD_10,
    CARD_11,
    CARD_12,
    CARD_13,
    CARD_14,
    CARD_15,
    CARD_16,
    CARD_17,
    CARD_18,
    CARD_19
};

typedef int Card;

// values are stored in an union to keep them in the same memory area,
// as this struct is copied for each card added.
struct CardData {
    int id;
    int type;
    bool changed;
    enum { INTEGER, FLOAT, STRING } value_type;
    union {
        char *value_s;
        float value_f;
        int value_i;
        unsigned char __pad[8]; // force alignment
    };

    // used to run an attached function
    void (*value_ptr)(CardData *);

    int datatype;
    char *name;
};

struct CardNames {
    int value;
    const char *name;
    const char *json_method;
};

#define TEMPERATURE_CARD_TYPES 6
#define STATUS_CARD_TYPES 4
#define SLIDER_CARD_TYPES 4

class ESPDashV3
{
    private:
        Vector<CardData> cData;
        bool stats_enabled = true;
        bool basic_auth = false;
        const char *username;
        const char *password;

        // Async WebSocket event callback function
        static void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

    public:
        ESPDashV3();
        ~ESPDashV3();

        void init(AsyncWebServer& server);
        void webauth(const char *user, const char *pass);

        // adding a new card to layout, specialized functions
        int AddCard(const int type, const char *name, int datatype = 0);

        // Update card data, specialized functions
        void UpdateCard(const int cardID, int value);
        void UpdateCard(const int cardID, float value);
        void UpdateCard(const int cardID, String &value);
        void UpdateCard(const int cardID, void (*funptr)(CardData *));

        // Notify client side to update values
        void SendUpdates();

        // send generated layout json to client side
        String UpdateLayout(bool only_stats = false);

        // send generated update json to client side
        String RefreshCards(bool toAll = false);
};

extern ESPDashV3 ESPDash;

#endif
