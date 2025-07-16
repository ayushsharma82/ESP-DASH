/*
  -----------------------------
  ESPDASH Lite - AccessPoint Example
  -----------------------------

  Skill Level: Intermediate

  In this example we will be booting up our ESP Module in Access Point (SoftAP) mode
  and initialize our dashboard which can be accessed via 192.168.4.1 

  Github: https://github.com/ayushsharma82/ESP-DASH
  WiKi: https://docs.espdash.pro

  Works with ESP32, RP2040+W and RP2350+W based devices / projects.
  -------------------------------

  Upgrade to ESP-DASH Pro: https://espdash.pro
*/

#include <Arduino.h>
#if defined(ESP8266)
  /* ESP8266 Dependencies */
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#elif defined(ESP32)
  /* ESP32 Dependencies */
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#elif defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
  /* RP2040 or RP2350 Dependencies */
  #include <WiFi.h>
  #include <RPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#endif
#include <ESPDash.h>


/* Your SoftAP WiFi Credentials */
const char* ssid = ""; // SSID
const char* password = ""; // Password

/* Start Webserver */
AsyncWebServer server(80);

/* Attach ESP-DASH to AsyncWebServer */
ESPDash dashboard(server);

/* 
  Dashboard Cards 
  Format - (Dashboard Instance, Card Type, Card Name, Card Symbol(optional) )
*/
dash::TemperatureCard temperature(dashboard, "Temperature");
dash::HumidityCard humidity(dashboard, "Humidity");


void setup() {
  Serial.begin(115200);

  /* Start Access Point */
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  /* Start AsyncWebServer */
  server.begin();
}

void loop() {
  /* Update Card Values */
  temperature.setValue((int)random(0, 50));
  humidity.setValue((int)random(0, 100));

  /* Send Updates to our Dashboard (realtime) */
  dashboard.sendUpdates();

  /* 
    Delay is just for demonstration purposes in this example,
    Replace this code with 'millis interval' in your final project.
  */
  delay(3000);
}