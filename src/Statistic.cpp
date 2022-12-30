#include "Statistic.h"

Statistic::Statistic(ESPDash *dashboard, const char *key, const char *value) {
    _dashboard = dashboard;
    #if defined(ESP8266)
        _id = RANDOM_REG32;
    #elif defined(ESP32)
        _id = esp_random();
    #endif
    // Safe copy
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wstringop-truncation"
        strncpy(_key, key, sizeof(_key));
        strncpy(_value, value, sizeof(_value));
    #pragma GCC diagnostic pop
    _dashboard->add(this);
}

void Statistic::set(const char *key, const char *value) {
    // Safe copy
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wstringop-truncation"
        strncpy(_key, key, sizeof(_key));
        strncpy(_value, value, sizeof(_value));
    #pragma GCC diagnostic pop
    _changed = true;
}

Statistic::~Statistic() {
    _dashboard->remove(this);
}