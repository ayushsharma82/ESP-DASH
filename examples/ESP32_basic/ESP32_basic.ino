

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

AsyncWebServer server(80);
ESPDash dashboard(&server);

const char* ssid = ""; // Your WiFi SSID
const char* password = ""; // Your WiFi Password

// Dashboard Cards
Card card1(&dashboard, NUMBER_CARD, "Random Number");
Card temperature(&dashboard, TEMPERATURE_CARD, "Temperature", "°C");
Card humidity(&dashboard, HUMIDITY_CARD, "Humidity", "%");

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

    // Start AsyncWebServer
    server.begin();
}

void loop() {
    // cast values as integers
    card1.update((int)random(0, 5000));
    temperature.update((int)random(0, 50));
    humidity.update((int)random(0, 100));

    // Notify frontend updates
    dashboard.sendUpdates();
    delay(3000);
}