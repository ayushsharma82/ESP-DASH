#ifndef __CARD_H
#define __CARD_H


#include <functional>
#include "Arduino.h"

#include "ESPDash.h"
#include "ArduinoJson.h"

struct CardNames {
  int value;
  const char* type;
};

// functions defaults to zero (number card)
enum {
  GENERIC_CARD,
  TEMPERATURE_CARD,
  HUMIDITY_CARD,
  STATUS_CARD,
  SLIDER_CARD,
  BUTTON_CARD,
  PROGRESS_CARD
};

// Forward Declaration
class ESPDash;

// Card Class
class Card {
  private:
    ESPDash *_dashboard;

    uint32_t _id;
    const char* _name;
    int   _type;
    bool  _changed;
    enum { INTEGER, FLOAT, STRING } _value_type;
    union alignas(4) {
        float _value_f;
        int _value_i;
    };
    String _value_s;
    union alignas(4) {
        float _value_min_f;
        int _value_min;
    };
    union alignas(4) {
        float _value_max_f;
        int _value_max;
    };
    union alignas(4) {
        float _value_step_f;
        int _value_step;
    };
    String _symbol;
    std::function<void(int value)> _callback = nullptr;
    std::function<void(float value)> _callback_f = nullptr;

  public:
    Card(ESPDash *dashboard, const int type, const char* name, const char* symbol = "", const int min = 0, const int max = 0, const int step = 1);
    Card(ESPDash *dashboard, const int type, const char* name, const char* symbol, const float min, const float max, const float step);
    void attachCallback(std::function<void(int)> cb);
    void attachCallbackF(std::function<void(float)> cb);
    void update(int value);
    void update(int value, const char* symbol);
    void update(bool value);
    void update(bool value, const char* symbol);
    void update(float value);
    void update(float value, const char* symbol);
    void update(const char* value);
    void update(const char* value, const char* symbol);
    void update(const String &value);
    void update(const String &value, const char* symbol);
    ~Card();
  
  friend class ESPDash;
};


#endif
