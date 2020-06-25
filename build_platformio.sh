#!/bin/bash

set -euo pipefail

pio lib -g install "ESP Async WebServer@1.2.3" "ArduinoJson@6.15.0"

pio ci --lib=. --board esp32dev "examples/ESP32_basic"
pio ci --lib=. --board esp12e "examples/ESP8266_basic"
