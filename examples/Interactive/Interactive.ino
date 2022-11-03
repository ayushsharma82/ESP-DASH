/*
  -----------------------------
  ESPDASH Lite - Interactive Example
  -----------------------------

  Skill Level: Intermediate

  In this example we will be creating a interactive dashboard which consists 
  of a button and a slider.

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
  Button Card
  Format - (Dashboard Instance, Card Type, Card Name)
*/
Card button(&dashboard, BUTTON_CARD, "Test Button");

/* 
  Slider Card
  Format - (Dashboard Instance, Card Type, Card Name, Card Symbol(optional), int min, int max)
*/
Card slider(&dashboard, SLIDER_CARD, "Test Slider", "", 0, 255);


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

  /* Attach Button Callback */
  button.attachCallback([&](bool value){
    /* Print our new button value received from dashboard */
    Serial.println("Button Triggered: "+String((value)?"true":"false"));
    /* Make sure we update our button's value and send update to dashboard */
    button.update(value);
    dashboard.sendUpdates();
  });

  /* Attach Slider Callback */
  slider.attachCallback([&](int value){
    /* Print our new slider value received from dashboard */
    Serial.println("Slider Triggered: "+String(value));
    /* Make sure we update our slider's value and send update to dashboard */
    slider.update(value);
    dashboard.sendUpdates();
  });

  /* Start AsyncWebServer */
  server.begin();
}

void loop() {
  /* Nothing so far */
}