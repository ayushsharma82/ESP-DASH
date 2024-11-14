#include "Statistic.h"

#include <utility>

Statistic::Statistic(ESPDash *dashboard, const char *key, const char *value) {
    _dashboard = dashboard;
    _id = dashboard->nextId();
    // Safe copy
    _key = key;
    _value = value;
    _dashboard->add(this);
}

void Statistic::set(const char *value) {
    // Safe copy
    _changed = _value != value;
    if(_changed)
        _value = value;
}

void Statistic::set(String&& value) {
    // Safe copy
    _changed = _value != value;
    if(_changed)
        _value = std::move(value);
}

Statistic::~Statistic() {
    _dashboard->remove(this);
}