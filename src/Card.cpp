#include "Card.h"

/*
  Constructor
*/
Card::Card(ESPDash *dashboard, const int type, const char* name, const char* symbol, const int min, const int max, const int step){
  _dashboard = dashboard;
  _id = dashboard->nextId();
  _type = type;
  _name = name;
  _symbol = symbol;
  _value_min = min;
  _value_max = max;
  _value_step = step;
  _dashboard->add(this);
}

Card::Card(ESPDash *dashboard, const int type, const char* name, const char* symbol, const float min, const float max, const float step){
  _dashboard = dashboard;
  _id = dashboard->nextId();
  _type = type;
  _name = name;
  _symbol = symbol;
  _value_min_f = min;
  _value_max_f = max;
  _value_step_f = step;

  _value_type = Card::FLOAT;

  _dashboard->add(this);
}

/*
  Attach Function Callback
*/
void Card::attachCallback(std::function<void(int value)> cb){
  _callback = cb;
}

/*
  Attach Function Callback
*/
void Card::attachCallbackF(std::function<void(float value)> cb){
  _callback_f = cb;
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
  if(strcmp(_symbol.c_str(), symbol) != 0 || _value_i != value)
    _changed = true;
  _value_i = value;
  _symbol = symbol;
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
  if(strcmp(_symbol.c_str(), symbol) != 0 || _value_f != value)
    _changed = true;
  _value_f = value;
  _symbol = symbol;
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
  if (strcmp(_symbol.c_str(), symbol) != 0) {
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
  if(strcmp(_symbol.c_str(), symbol) != 0 || _value_i != value)
    _changed = true;
  _value_i = value;
  _symbol = symbol;
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

/*
  Destructor
*/
Card::~Card(){
  _dashboard->remove(this);
}
