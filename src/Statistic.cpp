#include "Statistic.h"

Statistic::Statistic(ESPDash *dashboard, const char *key, const char *value) {
    _dashboard = dashboard;
    #if defined(ESP8266)
        _id = RANDOM_REG32;
    #elif defined(ESP32)
        _id = esp_random();
    #endif
    snprintf(_key, sizeof(_key), "%s", key);
    snprintf(_value, sizeof(_value), "%s", value);
    _dashboard->add(this);
}

void Statistic::set(const char *key, const char *value) {
    // Safe copy
    snprintf(_key, sizeof(_key), "%s", key);
    snprintf(_value, sizeof(_value), "%s", value);
    _changed = true;
}

Statistic::~Statistic() {
    _dashboard->remove(this);
}
