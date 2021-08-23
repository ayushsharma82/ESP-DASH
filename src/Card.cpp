#include "Card.h"
#include "ESPDash.h"
#include "Tab.h"

#define ARDUINOJSON_NAMESPACE ArduinoJson
#include <ArduinoJson.hpp>

// Integral type to string pairs events
// ID, type
struct WidgetNames cardTags[] = {
  {GENERIC_CARD, "generic"},
  {TEMPERATURE_CARD, "temperature"},
  {HUMIDITY_CARD, "humidity"},
  {STATUS_CARD, "status"},
  {SLIDER_CARD, "slider"},
  {BUTTON_CARD, "button"},
  {PROGRESS_CARD, "progress"},
};

/*
  Constructor
*/
Card::Card(ESPDash *dashboard, const int type, const char* name, const char* symbol, const int min, const int max):
Widget()
{
  _dashboard = dashboard;
  _tab = nullptr;
  _type = type;
  _name = name;
  _symbol = symbol;
  _value_min = min;
  _value_max = max;
  _dashboard->add(this);
}
Card::Card(Tab *tab, const int type, const char* name, const char* symbol, const int min, const int max):
Widget()
{
  _dashboard = nullptr;
  _tab = tab;
  _type = type;
  _name = name;
  _symbol = symbol;
  _value_min = min;
  _value_max = max;
  _tab->add(this);
}

/*
  Attach Function Callback
*/
void Card::attachCallback(std::function<void(int value)> cb){
  _callback = cb;
}


/*
  Value update methods
*/
void Card::update(int value, const char* symbol){
  /* Clear String if it was used before */
  if(_value_type == Card::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = Card::INTEGER;
  _symbol = symbol;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void Card::update(int value){
  /* Clear String if it was used before */
  if(_value_type == Card::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = Card::INTEGER;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void Card::update(float value, const char* symbol){
  /* Clear String if it was used before */
  if(_value_type == Card::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = Card::FLOAT;
  _symbol = symbol;
  if(_value_f != value)
    _changed = true;
  _value_f = value;
}

void Card::update(float value){
  /* Clear String if it was used before */
  if(_value_type == Card::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = Card::FLOAT;
  if(_value_f != value)
    _changed = true;
  _value_f = value;
}

void Card::update(const String &value, const char* symbol){
  update(value.c_str(), symbol);
}

void Card::update(const String &value){
  update(value.c_str());
}

void Card::update(const char* value, const char* symbol){
  if(_value_type == Card::STRING){
    if(strcmp(_value_s.c_str(), value) != 0)
      _changed = true;
  }
  
  _value_type = Card::STRING;
  _symbol = symbol;
  _value_s = value;
}

void Card::update(const char* value){
    if(_value_type == Card::STRING){
    if(strcmp(_value_s.c_str(), value) != 0)
      _changed = true;
  }
  
  _value_type = Card::STRING;
  _value_s = value;
}

void Card::update(bool value, const char* symbol){
  /* Clear String if it was used before */
  if(_value_type == Card::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = Card::INTEGER;
  _symbol = symbol;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void Card::update(bool value){
  /* Clear String if it was used before */
  if(_value_type == Card::STRING){
    _value_s = "";
  }
  /* Store new value */
  _value_type = Card::INTEGER;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void Card::resolveCallback(int value) {
  if (_callback) _callback(value);
}

Card::JsonDocument Card::generateLayout() {
  auto doc = generateUpdate();
  doc["name"] = _name;
  doc["type"] = cardTags[_type].type;
  doc["value_min"] = _value_min;
  doc["value_max"] = _value_max;
  return std::move(doc);
}

Card::JsonDocument Card::generateUpdate() {
  Card::JsonDocument doc(256);
  doc["id"] = _id;
  doc["symbol"] = _symbol;
  switch (_value_type) {
    case Card::INTEGER: doc["value"] = _value_i; break;
    case Card::FLOAT: doc["value"] = _value_f; break;
    case Card::STRING: doc["value"] = _value_s; break;
    default: doc["value"] = "ERROR"; break;
  }
  return std::move(doc);
}


/*
  Destructor
*/
Card::~Card() {
  if (_dashboard)
    _dashboard->remove(this);
  if (_tab)
    _tab->remove(this);
}
