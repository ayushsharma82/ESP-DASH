#include "Chart.h"

/*
  Constructor
*/
Chart::Chart(ESPDash *dashboard, const int type, const char* name){
  _dashboard = dashboard;
  #if defined(ESP8266)
    _id = RANDOM_REG32;
  #elif defined(ESP32)
    _id = esp_random();
  #endif
  _type = type;
  _name = name;
  _dashboard->add(this);
}

/*
  Value update methods
*/
void Chart::updateX(int arr_x[], size_t x_size){
  _x_axis_type = GraphAxisType::INTEGER;
  if(!_x_axis_i.Empty())
    _x_axis_i.Clear();
  if(!_x_axis_f.Empty())
    _x_axis_f.Clear();
  if(!_x_axis_s.Empty())
    _x_axis_s.Clear();

  for(int i=0; i < x_size; i++){
    _x_axis_i.PushBack(arr_x[i]);
  }
  _changed = true;
}

void Chart::updateX(float arr_x[], size_t x_size){
  _x_axis_type = GraphAxisType::FLOAT;
  if(!_x_axis_i.Empty())
    _x_axis_i.Clear();
  if(!_x_axis_f.Empty())
    _x_axis_f.Clear();
  if(!_x_axis_s.Empty())
    _x_axis_s.Clear();

  for(int i=0; i < x_size; i++){
    _x_axis_f.PushBack(arr_x[i]);
  }
  _changed = true;
}

void Chart::updateX(String arr_x[], size_t x_size){
  _x_axis_type = GraphAxisType::STRING;
  if(!_x_axis_i.Empty())
    _x_axis_i.Clear();
  if(!_x_axis_f.Empty())
    _x_axis_f.Clear();
  if(!_x_axis_s.Empty())
    _x_axis_s.Clear();

  for(int i=0; i < x_size; i++){
    _x_axis_s.PushBack(arr_x[i].c_str());
  }
  _changed = true;
}

void Chart::updateY(int arr_y[], size_t y_size){
  _y_axis_type = GraphAxisType::INTEGER;
  if(!_y_axis_i.Empty())
    _y_axis_i.Clear();
  if(!_y_axis_f.Empty())
    _y_axis_f.Clear();

  for(int i=0; i < y_size; i++){
    _y_axis_i.PushBack(arr_y[i]);
  }
  _changed = true;
}

void Chart::updateY(float arr_y[], size_t y_size){
  _y_axis_type = GraphAxisType::FLOAT;
  if(!_y_axis_i.Empty())
    _y_axis_i.Clear();
  if(!_y_axis_f.Empty())
    _y_axis_f.Clear();

  for(int i=0; i < y_size; i++){
    _y_axis_f.PushBack(arr_y[i]);
  }
  _changed = true;
}

/*
  Destructor
*/
Chart::~Chart(){
  _dashboard->remove(this);
}