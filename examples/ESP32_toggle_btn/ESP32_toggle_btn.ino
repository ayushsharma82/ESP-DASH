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
*/

// This Example is a Demo of Realtime Capabilities of ESP-DASH with Access Point.
// Open Dashboard after Uploading and UI will auto update as a Card's Value changes


#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

AsyncWebServer server(80);

// Your ESP32 Access Point Name and Password
char ssid[15]; //Create a Unique AP from MAC address
const char* password = "12345678"; // Your WiFi Password / Empty Password = Open AP

int indicator = 2;

bool on = true;

void createSSID() {
  uint64_t chipid=ESP.getEfuseMac(); //The chip ID is essentially its MAC address(length: 6 bytes).
  uint16_t chip = (uint16_t)(chipid>>32);
  snprintf(ssid, 15, "esp32-%04X",chip);
}

void buttonClicked(const char* id){
  Serial.println("Button Clicked - "+String(id));
  on = !on;
  ESPDash.updateButtonStatusCard("btn1", on);
}

void setup() {

    Serial.begin(115200);

    WiFi.mode(WIFI_AP);
    createSSID();
    WiFi.softAP(ssid, password);
    delay(1000);
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("SSID: ");
    Serial.println(ssid);
        
    ESPDash.init(server);   // Initiate ESPDash and attach your Async webserver instance
    // Add Respective Cards and attach Button Click Function
    ESPDash.addButtonStatusCard("btn1", "Button Status", on);
    ESPDash.attachButtonClick(buttonClicked);
    
    server.begin();
}

void loop() {

}