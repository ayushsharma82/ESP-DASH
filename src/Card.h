#ifndef Card_h
#define Card_h


#include <functional>
#include "Arduino.h"

struct CardNames {
    int value;
    const char *tag;
    const char *method;
};

// functions defaults to zero (number card)
enum {
    NUMBER_CARD,
    BUTTON_CARD,
    TEMPERATURE_CARD,
    HUMIDITY_CARD,
    STATUS_CARD,
    SLIDER_CARD,
    GAUGE_CARD,
};

// integral type to string pairs events
// ID, type, json_method call
CardNames cardNames[] = {
    {NUMBER_CARD, "number", "updateNumber"},
    {BUTTON_CARD, "button", NULL},
    {TEMPERATURE_CARD, "temperature", "updateTemperature"},
    {HUMIDITY_CARD, "humidity", "updateHumidity"},
    {STATUS_CARD, "status", "updateStatus"},
    {SLIDER_CARD, "slider", "updateSlider"},
    {GAUGE_CARD, "gauge", "updateGauge"},
};

class Card {
  private:
    char* _name;
    int   _id;
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
    std::function<void()> _callback = nullptr;

  private:
    // Utility Methods
    const String generateJSON();

  public:
    Card(const int type, const char* name, const int min = 0, const int max = 0);
    void attachCallback(std::function<void()> cb);
    void update(int value);
    void update(float value);
    void update(const String &value);
    ~Card();
  
  friend class ESPDashV3;
};


#endif