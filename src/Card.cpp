#include "Card.h"

// integral type to string pairs events
// ID, type, json_method call
struct CardNames cardTags[] = {
  {NUMBER_CARD, "number"},
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
  Attach Function Callback for Button Card etc.
*/
void Card::attachCallback(std::function<void(bool value)> cb){
  _btn_callback = cb;
}

/*
  Attach Function Callback for Slider Card etc.
*/
void Card::attachCallback(std::function<void(int value)> cb){
  _slider_callback = cb;
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
  _value_type = Card::STRING;
  _symbol = symbol;
  if(strcmp(_value_s, value.c_str()) != 0)
    _changed = true;
  // _value_s = value; // TODO: Convert string to char array
}

void Card::update(const String &value){
  _value_type = Card::STRING;
  if(strcmp(_value_s, value.c_str()) != 0)
    _changed = true;
  // _value_s = value; // TODO: Convert string to char array
}

void Card::update(bool value, const char* symbol){
  _value_type = Card::BOOLEAN;
  _symbol = symbol;
  if(_value_b != value)
    _changed = true;
  _value_b = value;
}

void Card::update(bool value){
  _value_type = Card::BOOLEAN;
  if(_value_b != value)
    _changed = true;
  _value_b = value;
}


/*
  Generate JSON for UI
*/
const String Card::generateJSON(bool change_only){
  String data = "";

  StaticJsonDocument<256> doc;
  doc["id"] = _id;
  if(!change_only){
    doc["name"] = _name;
    doc["type"] = cardTags[_type].type;
    doc["value_min"] = _value_min;
    doc["value_max"] = _value_max;
  }
  doc["symbol"] = _symbol;

  switch (_value_type) {
    case Card::INTEGER:
      doc["value"] = _value_i;
      break;
    case Card::FLOAT:
      doc["value"] = String(_value_f, 2);
      break;
    case Card::STRING:
      doc["value"] = _value_s;
      break;
    case Card::BOOLEAN:
      doc["value"] = _value_b;
      break;
    default:
      // blank value
      break;
  }

  serializeJson(doc, data);
  return data;
}


/*
  Destructor
*/
Card::~Card(){
  _dashboard->remove(this);
}