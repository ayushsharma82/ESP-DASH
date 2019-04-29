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
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

AsyncWebServer server(80);

const char* ssid = ""; // Your WiFi SSID
const char* password = ""; // Your WiFi Password

// DASHv2 can use a variable to hold the card ID, like the following way.
Card temperature, humidity;

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

    // Initiate ESPDash and attach to webserver instance, it also starts the webserver
    ESPDash.init(server);

    // Associate the card, set the type on the first argument.
    // See ESPDash.h for information on card types enum
    // datatype is not mandatory, only if you want to change default value
    temperature = ESPDash.AddCard(TYPE_TEMPERATURE_CARD, "Temperature");
    humidity = ESPDash.AddCard(TYPE_HUMIDITY_CARD, "Humidity");
}

void loop() {
    int temp = random(0, 50)
    float humid = (float)(random(0, 100)/random(0, 100));

    // DASHv2 cards can be direct referenced by CARD_0, CARD_1... or by the assigned variable
    ESPDash.UpdateCard(temperature, temp);

    // OR if you prefer, this way also works. Cards now are referenced by its integer ID
    ESPDash.UpdateCard(CARD_0, temp);

    // Update functions accept both integer or floating point values
    ESPDash.UpdateCard(humidity, humid);

    // Notify frontend we have changes
    ESPDash.SendUpdates()

    delay(3000);
}