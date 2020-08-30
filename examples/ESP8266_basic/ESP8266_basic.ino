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

// This Example is a Demo of Realtime Capabilities of ESP-DASH.
// Open Dashboard after Uploading and UI will auto update as a Card's Value changes


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

AsyncWebServer server(80);
ESPDash dashboard(&server);

const char* ssid = ""; // Your WiFi SSID
const char* password = ""; // Your WiFi Password

// Dashboard Cards
Card number(NUMBER_CARD, "Random Number");
Card temperature(TEMPERATURE_CARD, "Temperature");
Card humidity(HUMIDITY_CARD, "Humidity");

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    
    // Add all cards to our dashboard
    dashboard.add(&number);
    dashboard.add(&temperature);
    dashboard.add(&humidity);

    // Start AsyncWebServer
    server.begin();
}

void loop() {
    // cast values as integers
    number.update((int)random(0, 5000));
    temperature.update((int)random(0, 50));
    hummidity.update((int)random(0, 100));

    // Notify frontend updates
    dashboard.sendUpdates();
    delay(3000);
}