#include "Card.h"

// integral type to string pairs events
// ID, type, json_method call
struct CardNames cardTags[] = {
  {NUMBER_CARD, "number", "updateNumber"},
  {BUTTON_CARD, "button", NULL},
  {TEMPERATURE_CARD, "temperature", "updateTemperature"},
  {HUMIDITY_CARD, "humidity", "updateHumidity"},
  {STATUS_CARD, "status", "updateStatus"},
  {SLIDER_CARD, "slider", "updateSlider"},
  {GAUGE_CARD, "gauge", "updateGauge"},
};

/*
  Constructor
*/
Card::Card(const int type, const char* name, const char* symbol, const int min, const int max){
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
}


/*
  Attach Function Callback for Button Card etc.
*/
void Card::attachCallback(std::function<void()> cb){
  _callback = cb;
}


/*
  Value update methods
*/
void Card::update(int value){
  _value_type = Card::INTEGER;
  if(_value_i != value)
    _changed = true;
  _value_i = value;
}

void Card::update(float value){
  _value_type = Card::FLOAT;
  if(_value_f != value)
    _changed = true;
  _value_f = value;
}

void Card::update(const String &value){
  _value_type = Card::STRING;
  if(strcmp(_value_s, value.c_str()) != 0)
    _changed = true;
  // _value_s = value; // TODO: Convert string to char array
}


/*
  Generate JSON for UI
*/
const String Card::generateJSON(bool change_only){
  String data = "";

  StaticJsonDocument<256> doc;
  doc["id"] = _id;
  if(change_only){
    doc["method"] = cardTags[_type].method;
  }else{
    doc["name"] = _name;
    doc["type"] = _type;
    doc["symbol"] = _symbol;
    doc["value_min"] = _value_min;
    doc["value_max"] = _value_max;
  }

  switch (_value_type) {
    case Card::INTEGER:
      doc["value"] = String(_value_i);
      break;
    case Card::FLOAT:
      doc["value"] = String(_value_f, 2);
      break;
    case Card::STRING:
      doc["value"] = _value_s;
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

}