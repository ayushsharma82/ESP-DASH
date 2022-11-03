#include "Statistic.h"

Statistic::Statistic(ESPDash *dashboard, const char *key, const char *value) {
    _dashboard = dashboard;
    #if defined(ESP8266)
        _id = RANDOM_REG32;
    #elif defined(ESP32)
        _id = esp_random();
    #endif
    // Safe copy
    strncpy(_key, key, sizeof(_key));
    strncpy(_value, value, sizeof(_value));
    _dashboard->add(this);
}

void Statistic::set(const char *key, const char *value) {
    // Safe copy
    strncpy(_key, key, sizeof(_key));
    strncpy(_value, value, sizeof(_value));
    _changed = true;
}

Statistic::~Statistic() {
    _dashboard->remove(this);
}