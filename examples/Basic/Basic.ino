/*
ESP-DASH is a Blazing Fast Library to Create Great Looking Dashboards to Manage your ESP's

To Use this Library - (Step 1 and Step 2 Required only for First time Upload)
Step1: Download and install ESP8266 SPIFFS Tool V0.3.0 / Latest
        https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html#uploading-files-to-file-system
Step2: Now Connect your ESP8266 and Select Tools > ESP8266 Sketch Data Upload.
        (This Uploads the UI for your Dashboard)
Step3: After SPIFFS Upload is Completed, Upload the Arduino Sketch to ESP8266.
Step4: Restart ESP8266 and Access your Dashboard at it's IP Address.

Library Author: Ayush Sharma
Created on: 11/10/2017
*/

#include <EspDash.h>

const char* ssid = "";
const char* password = "";

int number = 0;   // Number of Artificial Visitors

void setup() {
Serial.begin(115200);

EspDash.debug(true);              // Print Debug Info Like Wifi Connection etc. on Serial.
EspDash.begin(ssid, password);    // Setup First Time SSID and Password. (STA Only)
EspDash.addTab("Visitors", number);   // Add 'Visitors' Tab
}

void loop() {
  number++;   // Increase Number of Artifical Visitors
  EspDash.updateTab("Visitors", number);  // Update 'Visitors' Tab
  delay(100);

  EspDash.loop(); // Required for Proper Functioning.
}
