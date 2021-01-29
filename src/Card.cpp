#include "Card.h"

/*
  Constructor
*/
Card::Card(ESPDash *dashboard, const int type, const char* name, const char* symbol, const int min, const int max){
  _dashboard = dashboard;
  #if defined(ESP8266)
    _id = RANDOM_REG32;
  #elif defined(ESP32)
    _id = esp_random();
  #endif
  _type = type;
  _name = name;
  _symbol = symbol;
  _value_min = min;
  _value_max = max;
  _dashboard->add(this);
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
  _value_type = Card::INTEGER;
  _symbol = symbol;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void Card::update(int value){
  _value_type = Card::INTEGER;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void Card::update(float value, const char* symbol){
  _value_type = Card::FLOAT;
  _symbol = symbol;
  if(_value_f != value)
    _changed = true;
  _value_f = value;
}

void Card::update(float value){
  _value_type = Card::FLOAT;
  if(_value_f != value)
    _changed = true;
  _value_f = value;
}

void Card::update(const String &value, const char* symbol){
  if(_value_type == Card::STRING){
    if(strcmp(_value_s.c_str(), value.c_str()) != 0)
      _changed = true;
  }
  
  _value_type = Card::STRING;
  _symbol = symbol;
  _value_s = value;
}

void Card::update(const String &value){
    if(_value_type == Card::STRING){
    if(strcmp(_value_s.c_str(), value.c_str()) != 0)
      _changed = true;
  }
  
  _value_type = Card::STRING;
  _value_s = value;
}

void Card::update(bool value, const char* symbol){
  _value_type = Card::INTEGER;
  _symbol = symbol;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void Card::update(bool value){
  _value_type = Card::INTEGER;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

/*
  Destructor
*/
Card::~Card(){
  _dashboard->remove(this);
}