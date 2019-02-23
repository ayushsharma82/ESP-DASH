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

// This Example is a Demo of Realtime Capabilities of ESP-DASH in Access Point Mode.
// Open Dashboard after Uploading and UI will auto update as a Card's Value changes


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

AsyncWebServer server(80);

// These variables would be your desired ESP8266 Access Point Name and Password
const char* ssid = ""; // Your WiFi SSID
const char* password = ""; // Your WiFi Password / Empty Password = Open AP


void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
    
    ESPDash.init(server);   // Initiate ESPDash and attach your Async webserver instance
    // Add Respective Cards
    ESPDash.addNumberCard("num1", "Number Card", 264);
    ESPDash.addTemperatureCard("temp1", "Temperature Card", 0, 20);
    ESPDash.addHumidityCard("hum1", "Humidity Card", 98);
    
    server.begin();
}

void loop() {
    ESPDash.updateNumberCard("num1", random(0, 5000));
    ESPDash.updateTemperatureCard("temp1", random(0, 50));
    ESPDash.updateHumidityCard("hum1", random(0, 100));
    delay(3000);
}