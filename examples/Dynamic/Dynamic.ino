/*
  -------------------------
  ESPDASH Lite - Dynamic Example
  -------------------------

  Skill Level: Advanced ( Must have good knowledge about heap, pointers and destructors )

  In this example we will be creating a dynamic dashboard which consists 
  of some cards and then remove a card from dashboard after some time.

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
Card* temperature = new Card(&dashboard, TEMPERATURE_CARD, "Temperature", "°C");
Card* humidity = new Card(&dashboard, HUMIDITY_CARD, "Humidity", "%");

/* 
  Removal Time for demonstration purposes only
  In your final project,
  You will decide when to add or remove cards, these variables are not requried.
*/
unsigned long removalTime = 30000; // Remove after 30s ( 30000 Millis )
bool cardRemoved = false;

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
  if(temperature != nullptr) // Check if our pointer has not been deleted & then only access 'update' method
    temperature->update((int)random(0, 50));

  if(humidity != nullptr) // Check if our pointer has not been deleted & then only access 'update' method
    humidity->update((int)random(0, 100));

  
  /* Remove our card when removal time is elapsed */
  if(millis() > removalTime && !cardRemoved){
    if(humidity != nullptr){
      /* Calling 'delete' will remove this card from our dashboard instance and will free-up consumed heap */
      delete humidity; 
      humidity = nullptr; // Make sure to set this pointer to 'nullptr' when deleted 
    }
    // Set our removal flag
    cardRemoved = true;
  }

  /* Send Updates to our Dashboard (realtime) */
  dashboard.sendUpdates();

  /* 
    Delay is just for demonstration purposes in this example,
    Replace this code with 'millis interval' in your final project.
  */
  delay(3000);
}
