#ifndef __CARD_H
#define __CARD_H

#include "dash/DashCards.h"

#define BUTTON_CARD         dash::Component::Type::CARD_BUTTON
#define GENERIC_CARD        dash::Component::Type::CARD_GENERIC
#define HUMIDITY_CARD       dash::Component::Type::CARD_HUMIDITY
#define PROGRESS_CARD      dash::Component::Type::CARD_PROGRESS
#define SLIDER_CARD        dash::Component::Type::CARD_SLIDER
#define STATUS_CARD         dash::Component::Type::CARD_STATUS
#define TEMPERATURE_CARD    dash::Component::Type::CARD_TEMPERATURE

#define DASH_STATUS_IDLE "i"
#define DASH_STATUS_SUCCESS "s"
#define DASH_STATUS_WARNING "w"
#define DASH_STATUS_DANGER "d"

// Card Class
class [[deprecated("This class is deprecated. Use a dash::Card sub-class instead.")]] Card : public dash::Widget {
  private:
    ESPDash* _dashboard = nullptr;

    enum { INTEGER,
           FLOAT,
           STRING } _value_type;
    union alignas(4) {
        float _value_f;
        int _value_i;
    };
    dash::string _value_s;
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
    dash::string _symbol;

    std::function<void(int value)> _callback = nullptr;
    std::function<void(float value)> _callback_f = nullptr;

  public:
    Card(ESPDash* dashboard, const dash::Component::Type type, const char* name, const char* symbol = "", const int min = 0, const int max = 0, const int step = 1);
    Card(ESPDash* dashboard, const dash::Component::Type type, const char* name, const char* symbol, const float min, const float max, const float step);
    void attachCallback(std::function<void(int)> cb) { _callback = cb; }
    void attachCallbackF(std::function<void(float)> cb) { _callback_f = cb; }
    void update(int value, const char* symbol = nullptr);
    void update(bool value, const char* symbol = nullptr);
    void update(float value, const char* symbol = nullptr);
    void update(const char* value, const char* symbol = nullptr);
    void update(const dash::string& value, const char* symbol = nullptr) { update(value.c_str(), symbol); }
    void update(dash::string&& value, const char* symbol = nullptr);
    virtual void toJson(const JsonObject& json, bool onlyChanges) const override;
    virtual void onEvent(const JsonObject& json) override;
    ~Card();
};

#endif
