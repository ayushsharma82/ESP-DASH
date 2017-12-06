#ifndef EspDash_h
#define EspDash_h

#include "Arduino.h"

// Necessary for ESP
#if defined(ESP8266)
#include "stdlib_noniso.h"
#endif

#define TABS_LIMIT 15
#define SERVER_PORT 80

// Hardware data
#define HARDWARE "esp8266"
#include "FS.h"
#include "ESP8266WiFi.h"
#include "WiFiClient.h"
#include "ESP8266WebServer.h"
#include "ESP8266HTTPUpdateServer.h"
#include "ArduinoJson.h"
/*
#define HARDWARE "esp32"
#include "FS.h"
#include "SPIFFS.h"
#include "WiFi.h"
#include "ESP32WebServer.h"
#include "ArduinoJson.h"
#endif
*/

class EspDashClass{

public:
  void begin(const char* _ssid, const char* _pass = NULL);   // Begin Webserver & Get Base SSID / Pass
  void debug(bool stat = false);                                     // Print Out Serial Data or not.
  void addTab(const char* _tabName, String _value);     // Add User Tab
  void addTab(const char* _tabName, int _value);             // Add User Tab in Int
  void updateTab(const char* _tabName, String _value);       // Update Tab Value
  void updateTab(const char* _tabName, int _value);          // Update Tab Value in Int
  void loop();

  const char* _SSID = "";
  const char* _PASS = "";
  bool _debug = false;

  int tabCount = 0;
  String tabName[15] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
  String tabData[15] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};

private:

  void handleRootPage();        // Handle Index HTML
  void handleUpdatePage();      // Handle Update Page
  void handleSettingsPage();    // Handle WiFi Settings Page
  void handleCSS();             // Handle CSS
  void handleJS();              // Handle JS

  void handleRebootImage();     // Handle Reboot Image
  void handleLogo();            // Handle 'Dash' Logo
  void handleUpdateImage();     // Handle Update Image
  void handleWifiImage();       // Handle Wifi Image

  void handleRootJSON();        // Handle Tab Updates Etc.
  void handleSettingsUpdate();    // Handle Settings Input from Page

  bool wifiRestore();                                             // Restores Wifi SSID and PASSWORD from SPIFFS
  bool wifiBackup(const char* _ssid, const char* _pass = NULL);   // Backup SSID and PASSWORD to SPIFFS
  void handleReboot();                                            // Handle Reboot Call
};

extern EspDashClass EspDash;
#endif
