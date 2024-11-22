#ifndef __STAT_H
#define __STAT_H

#include <functional>
#include "Arduino.h"

#include "ESPDash.h"
#include "ArduinoJson.h"

#ifdef DASH_USE_STL_STRING
#include <string>
namespace dash {
  using string = std::string;
}
#else
namespace dash {
  using string = String;
}
#endif

// Forward Declaration
class ESPDash;

class Statistic {
    private:
        ESPDash *_dashboard;
        uint32_t _id;
        const char *_key;
        dash::string _value;
        bool _changed = false;

    public:
        Statistic(ESPDash *dashboard, const char *key, const char *value = "");
        void set(const char *value);
        void set(const dash::string& value) { set(value.c_str()); }
        void set(dash::string&& value);
        ~Statistic();

    friend class ESPDash;
};

#endif