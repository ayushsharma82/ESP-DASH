#include "Card.h"


/*
  Constructor
*/
Card::Card(const int type, const char* name, const int min = 0, const int max = 0){
  _type = type;
  // _name = name; // TODO: copy const char to char array
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
  _value_i = value;
}

void Card::update(float value){
  _value_type = Card::FLOAT;
  _value_f = value;
}

void Card::update(const String &value){
  _value_type = Card::STRING;
  // _value_s = value; // TODO: Convert string to char array
}


/*
  Generate JSON for UI
*/
const String Card::generateJSON(){
  String data = "";
  data += "{\"id\":" + String(_id) + ",";
  data += "\"method\":\"" + String(cardNames[_type].method) + "\",";
  data += "\"value\":\"";

  switch (_value_type) {
    case Card::INTEGER:
      data += String(_value_i);
      break;
    case Card::FLOAT:
      data += String(_value_f, 2);
      break;
    case Card::STRING:
      data += _value_s;
      break;
    default:
      // blank value
      break;
  }

  data += "\"}";
  return data;
}


/*
  Destructor
*/
Card::~Card(){

}