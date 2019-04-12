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

// This Example is a Demo of Button Capability in ESP-DASH.
// Open Dashboard after Uploading and Drag the Slider to see changes on Gauge Card


#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

AsyncWebServer server(80);

const char* ssid = ""; // Your WiFi SSID
const char* password = ""; // Your WiFi Password


void sliderChanged(const char* id, int value){
   Serial.println("Slider Changed - "+String(id)+" "+String(value));
   ESPDash.updateGaugeChart("gauge1", value);
}


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
    
    ESPDash.init(server);   // Initiate ESPDash and attach your Async webserver instance
    
    // Attach Slider Change Events
    ESPDash.attachSliderChanged(sliderChanged);

    ESPDash.addSliderCard("slider1", "Gauge Slider", 3);
    ESPDash.addGaugeChart("gauge1", "Gauge 1");
    server.begin();
}

void loop() {

}