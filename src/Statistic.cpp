#include "Statistic.h"

Statistic::Statistic(ESPDash *dashboard, const char *key, const char *value) {
    _dashboard = dashboard;
    _id = dashboard->nextId();
    // Safe copy
    _key = key;
    strncpy(_value, value, sizeof(_value));
    _dashboard->add(this);
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