/*
 ___ ___ ___     ___   _   ___ _  _
| __/ __| _ \___|   \ /_\ / __| || |
| _|\__ \  _/___| |) / _ \\__ \ __ |
|___|___/_|     |___/_/ \_\___/_||_|

Author: Ayush Sharma (Github @ayushsharma82)
First Commit: Nov 5, 2017
Repository URL: https://github.com/ayushsharma82/ESP-DASH
*/

#pragma once

#include "Arduino.h"
// #include "edp.h"
#include "stdlib_noniso.h"

#if defined(ESP8266)
  #define DASH_HARDWARE "ESP8266"
  #include "ESP8266WiFi.h"
  #include "ESPAsyncTCP.h"
#elif defined(ESP32)
  #define DASH_HARDWARE "ESP32"
  #include "AsyncTCP.h"
  #include "WiFi.h"
#elif defined(TARGET_RP2040) || defined(PICO_RP2040)
  #define DASH_HARDWARE "RP2040"
  #include "RPAsyncTCP.h"
  #include "WiFi.h"
#elif defined(TARGET_RP2350) || defined(PICO_RP2350)
  #define DASH_HARDWARE "RP2350"
  #include "RPAsyncTCP.h"
  #include "WiFi.h"
#endif

#include "ArduinoJson.h"
#include "ESPAsyncWebServer.h"

#include "dash/Cards.h"
#include "dash/Charts.h"
#include "dash/Component.h"
#include "dash/Defines.h"
#include "dash/Statistics.h"
#include "dash/Widget.h"

// Controls the payload size: as soon as the payload size reaches this value, the payload is sent to the client
// This allows to split in batches the payload to avoid sending too large payloads at once
#ifndef DASH_JSON_SIZE
  #define DASH_JSON_SIZE 2048
#endif

#ifndef DASH_MAX_WS_CLIENTS
  #define DASH_MAX_WS_CLIENTS DEFAULT_MAX_WS_CLIENTS
#endif

// ESPDASH Class
class ESPDash {
  public:
    // changes_only: true (equivalent to sendUpdates(false)) - when sending updates to the client
    // changes_only: false (equivalent to sendUpdates(true)) - when sending the entire layout to the client or when forcing a full update
    typedef std::function<void(bool changes_only)> BeforeUpdateCallback;

  private:
    AsyncWebServer* _server = nullptr;
    AsyncWebSocket* _ws = nullptr;

    std::list<dash::Component*> _components;      // all components
    std::list<dash::Component*> _componentsOwned; // components created by ESPDash (like statistics), which should be deleted in the destructor
    bool basic_auth = false;
    dash::string username;
    dash::string password;
    BeforeUpdateCallback _beforeUpdateCallback = nullptr;

    volatile bool _asyncAccessInProgress = false;

    // Generate layout json
    void generateLayoutJSON(AsyncWebSocketClient* client, bool changes_only, const dash::Component* onlyComponent);
    size_t generateLayoutJSON(AsyncWebSocketClient* client, bool changes_only, const dash::Component* onlyComponent, JsonDocument& doc, uint8_t familyMask);
    void send(AsyncWebSocketClient* client, JsonDocument& doc);

    static const char* jsonKey(const dash::Component* c) { return jsonKey(c->family()); }
    static const char* jsonKey(dash::Component::Family family);

  public:
    ESPDash(AsyncWebServer& server, const char* uri, bool enable_default_stats);
    ESPDash(AsyncWebServer& server, bool enable_default_stats) : ESPDash(server, "/", enable_default_stats) {}
    ESPDash(AsyncWebServer& server) : ESPDash(server, "/", true) {}
    ~ESPDash();

    // Set Authentication
    void setAuthentication(const char* user, const char* pass);
    void setAuthentication(const dash::string& user, const dash::string& pass) { setAuthentication(user.c_str(), pass.c_str()); }

    // Add a component to the dashboard and return true if the component was added, false if the component ID was already present
    bool add(dash::Component& component);
    void remove(dash::Component& component);

    // Notify client side to update values
    void sendUpdates(bool force = false);
    void refreshLayout() { sendUpdates(true); }
    void refresh(const dash::Component& component);

    bool hasClient() { return _ws->count() > 0; }

    // can be used to check if the async_http task might currently access the cards data,
    // in which case you should not modify them
    bool isAsyncAccessInProgress() { return _asyncAccessInProgress; }

    // Register a callback that will be called before some updates will be sent to the client.
    // This callback can be used for example to refresh some card values that never change after only when a full layout is request (i.e. on page reload).
    // This allows to avoid spending time refreshing cards that never change, but still allows them to be refreshed hen the user refresh the dashboard.
    // If called from the async_http task, isAsyncAccessInProgress() will return true while in this callback.
    void onBeforeUpdate(BeforeUpdateCallback callback) { _beforeUpdateCallback = callback; }
};
