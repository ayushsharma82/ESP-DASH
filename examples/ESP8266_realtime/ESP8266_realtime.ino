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

// This Example is a Demo of Realtime Capabilities of ESP-DASH with a Line Chart.
// Open Dashboard after Uploading and UI will auto update as the Chart Value Changes


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

AsyncWebServer server(80);

const char* ssid = ""; // Your WiFi SSID
const char* password = ""; // Your WiFi Password

// Line Chart Data
int x_axis_size = 7;
String x_axis[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; 
int y_axis_size = 7;
int y_axis[7] = {2, 5, 10, 12, 18, 8, 5};


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
    // Add Respective Cards
    ESPDash.addLineChart("chart1", "Example Line Chart", x_axis, x_axis_size, "Power KwH", y_axis, y_axis_size);
    ESPDash.addGaugeChart("chart2", "Gauge 1", 30);
    server.begin();
}

void loop() {
    // Fill Data with random Values
    for(int i=0; i < 7; i++){
        y_axis[i] = random(2, 20);
    }

    ESPDash.updateLineChart("chart1", x_axis, x_axis_size, y_axis, y_axis_size);
    ESPDash.updateGaugeChart("chart2", 50);
    delay(1000);
    ESPDash.updateGaugeChart("chart2", 80);
    delay(1000);
    ESPDash.updateGaugeChart("chart2", 10);
    delay(1000);
}