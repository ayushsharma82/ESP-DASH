#ifndef __CARD_H
#define __CARD_H


#include <functional>
#include "Arduino.h"

#include "ArduinoJson.h"

struct CardNames {
  int value;
  const char* tag;
  const char* method;
};

// functions defaults to zero (number card)
enum {
  NUMBER_CARD,
  TEMPERATURE_CARD,
  HUMIDITY_CARD,
  STATUS_CARD,
  SLIDER_CARD,
  GAUGE_CARD,
  BUTTON_CARD,
};


class Card {
  private:
    uint32_t _id;
    String _name;
    int   _type;
    bool  _changed;
    enum { INTEGER, FLOAT, STRING } _value_type;
    union alignas(8) {
        char *_value_s;
        float _value_f;
        int _value_i;
    };
    int _value_min;
    int _value_max;
    String _symbol;
    std::function<void()> _callback = nullptr;

  private:
    // Utility Methods
    const String generateJSON(bool change_only = false);

  public:
    Card(const int type, const char* name, const char* symbol = "", const int min = 0, const int max = 0);
    void attachCallback(std::function<void()> cb);
    void update(int value);
    void update(float value);
    void update(const String &value);
    ~Card();
  
  friend class ESPDash;
};


#endif