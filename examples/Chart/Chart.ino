/*
  -----------------------
  ESPDASH - Chart Example
  -----------------------

  Skill Level: Intermediate

  In this example we will learn how to create a line chart
  and then update it at a regular interval.

  Github: https://github.com/ayushsharma82/ESP-DASH
  WiKi: https://ayushsharma82.github.io/ESP-DASH/

  Works with both ESP8266 & ESP32
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

/* Start Webserver & ESPDash */
AsyncWebServer server(80);
ESPDash dashboard(&server); // Attach ESPDash with our AsyncWebServer Instance

/* 
  Dashboard Charts
  Format - (Dashboard Instance, Chart Type, Chart Name )
*/
// Line Chart Data
String XAxis[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
int YAxis[] = {0, 0, 0, 0, 0, 0, 0};

// Line Chart Instance
Chart power(&dashboard, LINE_CHART, "Power Usage (kWh)");


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

  /* 
    Update Chart X Axis (xaxis_array, array_size)
    -------------------
    We need to update X Axis once only as it will not be changing in this example 
  */
  power.updateX(XAxis, 7);

  /* Start AsyncWebServer */
  server.begin();
}

void loop() {
  // Randomize YAxis Values ( for demonstration purposes only )
  for(int i=0; i < 7; i++){
    YAxis[i] = (int)random(0, 200);
  }

  /* Update Chart Y Axis (yaxis_array, array_size) */
  power.updateY(YAxis, 7);

  /* Send Updates to our Dashboard (realtime) */
  dashboard.sendUpdates();

  /* 
    Delay is just for demonstration purposes in this example,
    Replace this code with 'millis interval' in your final project.
  */
  delay(3000);
}