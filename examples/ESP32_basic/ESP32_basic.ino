

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

AsyncWebServer server(80);

const char* ssid = ""; // Your WiFi SSID
const char* password = ""; // Your WiFi Password

// these holds created cards IDs
Card number, temperature, humidity;

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
    
    // Initiate ESPDash and attach your Async webserver instance, it also starts the
    // server automatically now. no need to call server.begin
    ESPDash.init(server);

    // Add Respective Cards
    number = ESPDash.AddCard(TYPE_NUMBER_CARD, "Visitors");
    temperature = ESPDash.AddCard(TYPE_TEMPERATURE_CARD, "Temperature");
    humidity = ESPDash.AddCard(TYPE_HUMIDITY_CARD, "Humidity");    
}

void loop() {
    // cast values as integers
    ESPDash.UpdateCard(number, (int)random(0, 5000));
    ESPDash.UpdateCard(temperature, (int)random(0, 50));
    ESPDash.UpdateCard(humidity, (int)random(0, 100));

    // Notify frontend updates
    ESPDash.SendUpdates();

    delay(3000);
}