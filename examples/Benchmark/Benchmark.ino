/*
  -----------------------------
  ESPDASH Pro - Benchmark Example
  -----------------------------
  Use this benchmark example to test if ESP-DASH Pro is working properly on your platform.

  Github: https://github.com/ayushsharma82/ESP-DASH
  WiKi: https://docs.espdash.pro

  Works with both ESP8266 & ESP32
  -------------------------------
*/

#include <Arduino.h>
#if defined(ESP8266)
  /* ESP8266 Dependencies */
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#elif defined(ESP32)
  /* ESP32 Dependencies */
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#elif defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
  /* RP2040 or RP2350 Dependencies */
  #include <ESPAsyncWebServer.h>
  #include <RPAsyncTCP.h>
  #include <WiFi.h>
#endif

#include <ESPDash.h>

/* Your WiFi Credentials */
const char* ssid = "";     // SSID
const char* password = ""; // Password

/* Start Webserver */
AsyncWebServer server(80);

/* Attach ESP-DASH to AsyncWebServer */
ESPDash dashboard(server, true);

// Cards
dash::FeedbackCard feedback(dashboard, "Status", dash::Status::SUCCESS);
dash::GenericCard genericString(dashboard, "Generic String");
dash::GenericCard<float> genericFloat(dashboard, "Generic Float");
dash::GenericCard<int> genericInt(dashboard, "Generic Int");
dash::HumidityCard<float, 3> hum(dashboard, "Humidity"); // set decimal precision is 3
dash::ProgressCard<float, 4> progressFloat(dashboard, "Progress Float", 0, 1, "kWh");
dash::ProgressCard progressInt(dashboard, "Progress Int", 0, 100, "%");
dash::SliderCard<float, 4> sliderFloatP4(dashboard, "Float Slider (4)", 0, 1, 0.0001f);
dash::SliderCard<float> sliderFloatP2(dashboard, "Float Slider (2)", 0, 1, 0.01f);
dash::SliderCard sliderInt(dashboard, "Int Slider", 0, 255, 1, "bits");
dash::SliderCard<uint32_t> updateDelay(dashboard, "Update Delay", 1000, 20000, 1000, "ms");
dash::SwitchCard button(dashboard, "Button");
dash::TemperatureCard temp(dashboard, "Temperature"); // default precision is 2

// Charts
dash::BarChart<const char*, int> bar(dashboard, "Power Usage (kWh)");

// Custom Statistics
dash::StatisticValue stat1(dashboard, "Statistic 1");
dash::StatisticValue<float, 4> stat2(dashboard, "Statistic 2");
dash::StatisticProvider<uint32_t> statProvider(dashboard, "Statistic Provider");

uint8_t test_status = 0;

/**
 * Note how we are keeping all the chart data in global scope.
 */
// Bar Chart Data
const char* BarXAxis[] = {"1/4/22", "2/4/22", "3/4/22", "4/4/22", "5/4/22", "6/4/22", "7/4/22", "8/4/22", "9/4/22", "10/4/22", "11/4/22", "12/4/22", "13/4/22", "14/4/22", "15/4/22", "16/4/22", "17/4/22", "18/4/22", "19/4/22", "20/4/22", "21/4/22", "22/4/22", "23/4/22", "24/4/22", "25/4/22", "26/4/22", "27/4/22", "28/4/22", "29/4/22", "30/4/22"};
int BarYAxis[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

unsigned long last_update_millis = 0;
uint32_t update_delay = 2000;

void setup() {
  Serial.begin(115200);
  Serial.println();
  /* Connect WiFi */

  // WiFi.persistent(false);
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.print("IP Address: ");
  // Serial.println(WiFi.localIP());

  WiFi.mode(WIFI_AP);
  WiFi.softAP("esp-captive");

  /* Attach Button Callback */
  button.onChange([&](bool state) {
    /* Print our new button value received from dashboard */
    Serial.println(String("Button Triggered: ") + (state ? "true" : "false"));
    /* Make sure we update our button's value and send update to dashboard */
    button.setValue(state);
    dashboard.refresh(button);
  });

  // Set Slider Index
  sliderInt.setIndex(1);

  /* Attach Slider Callback */
  sliderInt.onChange([&](int value) {
    /* Print our new slider value received from dashboard */
    Serial.println("Slider Triggered: " + String(value));
    /* Make sure we update our slider's value and send update to dashboard */
    sliderInt.setValue(value);
    dashboard.refresh(sliderInt);
  });

  sliderFloatP2.setIndex(2);
  sliderFloatP2.onChange([&](float value) {
    Serial.println("Slider Float P2 Triggered: " + String(value));
    sliderFloatP2.setValue(value);
    dashboard.refresh(sliderFloatP2);
  });

  sliderFloatP4.setIndex(3);
  sliderFloatP4.onChange([&](float value) {
    Serial.println("Slider Float P4 Triggered: " + String(value, 4));
    sliderFloatP4.setValue(value);
    dashboard.refresh(sliderFloatP4);
  });

  updateDelay.setValue(update_delay);
  updateDelay.onChange([&](uint32_t value) {
    update_delay = value;
    updateDelay.setValue(value);
    dashboard.refresh(updateDelay);
  });

  stat1.setValue("Value 1");
  stat2.setValue(10.0 / 3.0);
  statProvider.setProvider([]() { return millis(); });

  bar.setX(BarXAxis, 30);

  genericFloat.setValue(10.0 / 3.0); // default rounding is 2
  genericString.setValue("Hello World!");

  /* Start AsyncWebServer */
  server.begin();

  server.onNotFound([](AsyncWebServerRequest* request) {
    request->send(404);
  });
}

void loop() {
  // Update Everything every 2 seconds using millis if connected to WiFi
  if (millis() - last_update_millis > update_delay && dashboard.hasClient()) {
    last_update_millis = millis();

    // Randomize Bar Chart YAxis Values ( for demonstration purposes only )
    for (int i = 0; i < 30; i++) {
      BarYAxis[i] = (int)random(0, 200);
    }

    /* Update Chart Y Axis (yaxis_array, array_size) */
    bar.setY(BarYAxis, 30);

    // Update all cards with random values
    genericInt.setSymbol(random(0, 2) ? "unit1" : "unit2");
    genericInt.setValue((int)random(0, 100));
    temp.setValue(random(0, 100) / 3.0);
    hum.setValue(random(0, 100) / 3.0);

    progressInt.setValue(random(0, 200));             // if more than max, clamped to max
    progressFloat.setValue(random(0, 1000) / 2000.0); // if more than max, clamped to max

    sliderInt.setValue(random(0, 200)); // clamped at 255 by max
    sliderFloatP2.setValue(random(0, 100) / 333.0);
    sliderFloatP4.setValue(random(0, 100) / 333.0);

    // Loop through statuses
    if (test_status == 0) {
      feedback.setFeedback("Success Msg!", dash::Status::SUCCESS);
      test_status = 1;
    } else if (test_status == 1) {
      feedback.setFeedback("Warning Msg!", dash::Status::WARNING);
      test_status = 2;
    } else if (test_status == 2) {
      feedback.setFeedback("Danger Msg!", dash::Status::DANGER);
      test_status = 3;
    } else if (test_status == 3) {
      feedback.setFeedback("Idle Msg!", dash::Status::IDLE);
      test_status = 0;
    }

    if (random(0, 2))
      button.toggle();

#if defined(ESP8266) || defined(ESP32)
    Serial.println("Free Heap (Before Update): " + String(ESP.getFreeHeap()));
#elif defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
    Serial.println("Free Heap (Before Update): " + String(rp2040.getFreeHeap()));
#endif

    dashboard.sendUpdates();

#if defined(ESP8266) || defined(ESP32)
    Serial.println("Free Heap (After Update): " + String(ESP.getFreeHeap()));
#elif defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
    Serial.println("Free Heap (After Update): " + String(rp2040.getFreeHeap()));
#endif
  }
}