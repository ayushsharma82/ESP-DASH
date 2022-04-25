#!/bin/bash
cd ${HOME}/Arduino/libraries
git clone https://github.com/me-no-dev/ESPAsyncWebServer.git ESPAsyncWebServer
git clone https://github.com/me-no-dev/ESPAsyncTCP.git ESPAsyncTCP
git clone https://github.com/me-no-dev/AsyncTCP.git AsyncTCP
git clone --single-branch --branch 6.x https://github.com/bblanchon/ArduinoJson.git ArduinoJson
