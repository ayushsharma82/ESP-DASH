/*
  -----------------------
  ESPDASH Lite - Basic Example
  -----------------------

  Skill Level: Intermediate

  In this example we will be creating a basic dashboard which consists 
  of some cards and then update them in realtime ( at 3s interval ).

  Github: https://github.com/ayushsharma82/ESP-DASH
  WiKi: https://docs.espdash.pro

  Works with both ESP8266 & ESP32

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
#endif
#include <ESPDash.h>


/* Your WiFi Credentials */
const char* ssid = ""; // SSID
const char* password = ""; // Password

/* Start Webserver */
AsyncWebServer server(80);

/* Attach ESP-DASH to AsyncWebServer */
ESPDash dashboard(&server); 

/* 
  Dashboard Cards 
  Format - (Dashboard Instance, Card Type, Card Name, Card Symbol(optional) )
*/
Card temperature(&dashboard, TEMPERATURE_CARD, "Temperature", "°C");
Card humidity(&dashboard, HUMIDITY_CARD, "Humidity", "%");


void setup() {
  Serial.begin(115200);

  /* Connect WiFi */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  /* Start AsyncWebServer */
  server.begin();
}

void loop() {
  /* Update Card Values */
  temperature.update((int)random(0, 50));
  humidity.update((int)random(0, 100));

  /* Send Updates to our Dashboard (realtime) */
  dashboard.sendUpdates();

  /* 
    Delay is just for demonstration purposes in this example,
    Replace this code with 'millis interval' in your final project.
  */
  delay(3000);
}