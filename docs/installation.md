---
title: Installation
sidebar_label: Installation
sidebar_position: 3
---

This document explains the installation procedure for getting started with ESP-DASH.

### Dependencies

*ESP-DASH depends on the following libraries present in your libraries folder. Please stricly install the compatible versions of these dependencies only! Using any other version might break ESP-DASH or may cause ESP-DASH to work partially.*

#### For ESP8266:
- [ESP8266 Arduino Core](https://github.com/esp8266/Arduino) @ **latest**
- [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP) @ **latest**
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) @ **latest**
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) @ **v7.0.2**

#### For ESP32:
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) @ **latest**
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) @ **latest**
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) @ **latest**
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) @ **v7.0.2**

:::tip Recommended Dependencies

Although ESP-DASH supports the **official** dependencies, If your dashboard contains a lot of components, It's advised to switch to the following **fork of dependencies** for a crash-free experience. These forks are drop-in replacements which contain bugfixes and offer much better performance.

#### For ESP8266:
- [esphome/ESPAsyncTCP](https://github.com/esphome/ESPAsyncTCP) @ **latest**
- [mathieucarbou/ESPAsyncWebServer](https://github.com/mathieucarbou/ESPAsyncWebServer) @ **2.5.1**

#### For ESP32:
- [esphome/AsyncTCP](https://github.com/esphome/AsyncTCP) @ **latest**
- [mathieucarbou/ESPAsyncWebServer](https://github.com/mathieucarbou/ESPAsyncWebServer) @ **2.5.1**

*Please make sure to uninstall the 'original' dependencies from your libraries folder if you have installed any of these forks. If the previous dependencies remain are still installed, the compiler will throw an error.*
:::


### Installing ESP-DASH 

#### 1. Directly Through Arduino IDE - Library Manager

Go to Sketch > Include Library > Library Manager > Search for "ESP-DASH" > Install


#### 2. Manual Install

##### For Windows:
- Download the [Repository](https://github.com/ayushsharma82/ESP-DASH/archive/master.zip)
- Extract the .zip in `Documents > Arduino > Libraries > {Place "ESP-DASH" folder Here}`

##### For Linux:
- Download the [Repository](https://github.com/ayushsharma82/ESP-DASH/archive/master.zip) 
- Extract the .zip in `Sketchbook > Libraries > {Place "ESP-DASH" folder Here}`


#### 3. Import through Arduino IDE

- Download the [Repository](https://github.com/ayushsharma82/ESP-DASH/archive/master.zip)
- Go to `Sketch > Include Library > Add .zip Library > Select the Downloaded .zip File.`
