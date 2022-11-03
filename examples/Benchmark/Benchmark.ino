/*
  -----------------------------
  ESPDASH Lite - Benchmark Example
  -----------------------------
  Use this benchmark example to test if ESP-DASH is working properly on your platform.

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

Card generic(&dashboard, GENERIC_CARD, "Generic");
Card temp(&dashboard, TEMPERATURE_CARD, "Temperature", "°C");
Card hum(&dashboard, HUMIDITY_CARD, "Humidity", "%");
Card status1(&dashboard, STATUS_CARD, "Status 1", "success");
Card status2(&dashboard, STATUS_CARD, "Status 2", "warning");
Card status3(&dashboard, STATUS_CARD, "Status 3", "danger");
Card status4(&dashboard, STATUS_CARD, "Status 4", "idle");
Card progress(&dashboard, PROGRESS_CARD, "Progress", "", 0, 100);
Card button(&dashboard, BUTTON_CARD, "Test Button");
Card slider(&dashboard, SLIDER_CARD, "Test Slider", "", 0, 255);

Chart bar(&dashboard, BAR_CHART, "Power Usage (kWh)");

// Bar Chart Data
String XAxis[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
int YAxis[] = {0, 0, 0, 0, 0, 0, 0};


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

  bar.updateX(XAxis, 7);

  /* Attach Button Callback */
  button.attachCallback([&](bool value){
    /* Print our new button value received from dashboard */
    Serial.println("Button Triggered: "+String((value)?"true":"false"));
    /* Make sure we update our button's value and send update to dashboard */
    button.update(value);
    dashboard.sendUpdates();
  });

  /* Attach Slider Callback */
  slider.attachCallback([&](int value){
    /* Print our new slider value received from dashboard */
    Serial.println("Slider Triggered: "+String(value));
    /* Make sure we update our slider's value and send update to dashboard */
    slider.update(value);
    dashboard.sendUpdates();
  });

  /* Start AsyncWebServer */
  server.begin();
}

void loop() {
  // Randomize YAxis Values ( for demonstration purposes only )
  for(int i=0; i < 7; i++){
    YAxis[i] = (int)random(0, 200);
  }

  /* Update Chart Y Axis (yaxis_array, array_size) */
  bar.updateY(YAxis, 7);

  // Update all cards with random values
  generic.update((int)random(0, 100));
  temp.update((int)random(0, 100));
  hum.update((int)random(0, 100));
  status1.update("success");
  status2.update("warning");
  status3.update("danger");
  status4.update("idle");
  progress.update((int)random(0, 100));
  
  dashboard.sendUpdates();
  delay(2000);
}