#include "Statistic.h"

Statistic::Statistic(ESPDash *dashboard, const char *key, const char *value) {
    _dashboard = dashboard;
    _id = dashboard->nextId();
    // Safe copy
    strncpy(_key, key, sizeof(_key));
    strncpy(_value, value, sizeof(_value));
    _dashboard->add(this);
}

void Statistic::set(const char *key, const char *value) {
    // Safe copy
    _changed = strcmp(_value, value) != 0 || strcmp(_key, key) != 0;
    if(_changed) {
        strncpy(_key, key, sizeof(_key));
        strncpy(_value, value, sizeof(_value));
    }
}

void Statistic::set(const char *value) {
    // Safe copy
    _changed = strcmp(_value, value) != 0;
    if(_changed)
        strncpy(_value, value, sizeof(_value));
    
}

Statistic::~Statistic() {
    _dashboard->remove(this);
}