#!/bin/bash

set -euo pipefail

pio lib -g install "ESP Async WebServer@1.2.3" "ArduinoJson@6.15.0"
for dir in examples/ESP32_*; do
  pio ci --lib=. --board esp32dev "${dir?}"
done

for dir in examples/ESP8266_*; do
  pio ci --lib=. --board esp12e "${dir?}"
done
