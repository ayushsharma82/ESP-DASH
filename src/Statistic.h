#ifndef __STAT_H
#define __STAT_H

#include <functional>
#include "Arduino.h"
#include "vector.h"

#include "ESPDash.h"
#include "ArduinoJson.h"

// Forward Declaration
class ESPDash;

class Statistic {
    private:
        ESPDash *_dashboard;
        uint32_t _id;
        const char *_key;
        String _value;
        bool _changed = false;

    public:
        Statistic(ESPDash *dashboard, const char *key, const char *value = "");
        void set(const char *value);
        ~Statistic();

    friend class ESPDash;
};

#endif