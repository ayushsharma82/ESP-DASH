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

#if DASH_USE_LEGACY_CHART_STORAGE == 1
  void Chart::emptyXAxisVectors() {
    if(!_x_axis_i.Empty())
      _x_axis_i.Clear();
    if(!_x_axis_f.Empty())
      _x_axis_f.Clear();
    if(!_x_axis_s.Empty())
      _x_axis_s.Clear();
  }

  void Chart::emptyYAxisVectors() {
    if(!_y_axis_i.Empty())
      _y_axis_i.Clear();
    if(!_y_axis_f.Empty())
      _y_axis_f.Clear();
  }
#else
  void Chart::clearXAxisPointers() {
    _x_axis_i_ptr = nullptr;
    _x_axis_f_ptr = nullptr;
    _x_axis_char_ptr = nullptr;
    _x_axis_s_ptr = nullptr;
    _x_axis_ptr_size = 0;
  }

  void Chart::clearYAxisPointers() {
    _y_axis_i_ptr = nullptr;
    _y_axis_f_ptr = nullptr;
    _y_axis_ptr_size = 0;
  }
#endif

/*
  Value update methods
*/
void Chart::updateX(int arr_x[], size_t x_size){
  _x_axis_type = GraphAxisType::INTEGER;
  #if DASH_USE_LEGACY_CHART_STORAGE == 1
    emptyXAxisVectors();
    for(int i=0; i < x_size; i++){
      _x_axis_i.PushBack(arr_x[i]);
    }
  #else
    clearXAxisPointers();
    _x_axis_i_ptr = arr_x;
    _x_axis_ptr_size = x_size;
  #endif
  _changed = true;
}

void Chart::updateX(float arr_x[], size_t x_size){
  _x_axis_type = GraphAxisType::FLOAT;
  #if DASH_USE_LEGACY_CHART_STORAGE == 1
    emptyXAxisVectors();
    for(int i=0; i < x_size; i++){
      _x_axis_f.PushBack(arr_x[i]);
    }
  #else 
    clearXAxisPointers();
    _x_axis_f_ptr = arr_x;
    _x_axis_ptr_size = x_size;
  #endif
  _changed = true;
}

void Chart::updateX(String arr_x[], size_t x_size){
  _x_axis_type = GraphAxisType::STRING;
  #if DASH_USE_LEGACY_CHART_STORAGE == 1
    emptyXAxisVectors();
    for(int i=0; i < x_size; i++){
      _x_axis_s.PushBack(arr_x[i].c_str());
    }
  #else
    clearXAxisPointers();
    _x_axis_s_ptr = arr_x;
    _x_axis_ptr_size = x_size;
  #endif
  _changed = true;
}

void Chart::updateX(const char* arr_x[], size_t x_size){
  _x_axis_type = GraphAxisType::CHAR;
  #if DASH_USE_LEGACY_CHART_STORAGE == 1
    emptyXAxisVectors();
    for(int i=0; i < x_size; i++){
      _x_axis_s.PushBack(String(arr_x[i]));
    }
  #else
    clearXAxisPointers();
    _x_axis_char_ptr = arr_x;
    _x_axis_ptr_size = x_size;
  #endif
  _changed = true;
}

void Chart::updateY(int arr_y[], size_t y_size){
  _y_axis_type = GraphAxisType::INTEGER;
  #if DASH_USE_LEGACY_CHART_STORAGE == 1
    emptyYAxisVectors();
    for(int i=0; i < y_size; i++){
      _y_axis_i.PushBack(arr_y[i]);
    }
  #else
    clearYAxisPointers();
    _y_axis_i_ptr = arr_y;
    _y_axis_ptr_size = y_size;
  #endif
  _changed = true;
}

void Chart::updateY(float arr_y[], size_t y_size){
  _y_axis_type = GraphAxisType::FLOAT;
  #if DASH_USE_LEGACY_CHART_STORAGE == 1
    emptyYAxisVectors();
    for(int i=0; i < y_size; i++){
      _y_axis_f.PushBack(arr_y[i]);
    }
  #else
    clearYAxisPointers();
    _y_axis_f_ptr = arr_y;
    _y_axis_ptr_size = y_size;
  #endif
  _changed = true;
}

/*
  Destructor
*/
Chart::~Chart(){
  _dashboard->remove(this);
}