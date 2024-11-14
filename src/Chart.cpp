#include "Chart.h"

/*
  Constructor
*/
Chart::Chart(ESPDash *dashboard, const int type, const char* name){
  _dashboard = dashboard;
  _id = dashboard->nextId();
  _type = type;
  _name = name;
  _dashboard->add(this);
}

#if DASH_USE_LEGACY_CHART_STORAGE == 1
  void Chart::emptyXAxisVectors() {
    if(!_x_axis_i.empty())
      _x_axis_i.clear();
    if(!_x_axis_f.empty())
      _x_axis_f.clear();
    if(!_x_axis_s.empty())
      _x_axis_s.clear();
  }

  void Chart::emptyYAxisVectors() {
    if(!_y_axis_i.empty())
      _y_axis_i.clear();
    if(!_y_axis_f.empty())
      _y_axis_f.clear();
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
      _x_axis_i.push_back(arr_x[i]);
    }
  #else
    clearXAxisPointers();
    _x_axis_i_ptr = arr_x;
    _x_axis_ptr_size = x_size;
  #endif
  _x_changed = true;
}

void Chart::updateX(float arr_x[], size_t x_size){
  _x_axis_type = GraphAxisType::FLOAT;
  #if DASH_USE_LEGACY_CHART_STORAGE == 1
    emptyXAxisVectors();
    for(int i=0; i < x_size; i++){
      _x_axis_f.push_back(arr_x[i]);
    }
  #else 
    clearXAxisPointers();
    _x_axis_f_ptr = arr_x;
    _x_axis_ptr_size = x_size;
  #endif
  _x_changed = true;
}

void Chart::updateX(String arr_x[], size_t x_size){
  _x_axis_type = GraphAxisType::STRING;
  #if DASH_USE_LEGACY_CHART_STORAGE == 1
    emptyXAxisVectors();
    for(int i=0; i < x_size; i++){
      _x_axis_s.push_back(arr_x[i].c_str());
    }
  #else
    clearXAxisPointers();
    _x_axis_s_ptr = arr_x;
    _x_axis_ptr_size = x_size;
  #endif
  _x_changed = true;
}

void Chart::updateX(const char* arr_x[], size_t x_size){
  _x_axis_type = GraphAxisType::CHAR;
  #if DASH_USE_LEGACY_CHART_STORAGE == 1
    emptyXAxisVectors();
    for(int i=0; i < x_size; i++){
      _x_axis_s.push_back(String(arr_x[i]));
    }
  #else
    clearXAxisPointers();
    _x_axis_char_ptr = arr_x;
    _x_axis_ptr_size = x_size;
  #endif
  _x_changed = true;
}

void Chart::updateY(int arr_y[], size_t y_size){
  _y_axis_type = GraphAxisType::INTEGER;
  #if DASH_USE_LEGACY_CHART_STORAGE == 1
    emptyYAxisVectors();
    for(int i=0; i < y_size; i++){
      _y_axis_i.push_back(arr_y[i]);
    }
  #else
    clearYAxisPointers();
    _y_axis_i_ptr = arr_y;
    _y_axis_ptr_size = y_size;
  #endif
  _y_changed = true;
}

void Chart::updateY(float arr_y[], size_t y_size){
  _y_axis_type = GraphAxisType::FLOAT;
  #if DASH_USE_LEGACY_CHART_STORAGE == 1
    emptyYAxisVectors();
    for(int i=0; i < y_size; i++){
      _y_axis_f.push_back(arr_y[i]);
    }
  #else
    clearYAxisPointers();
    _y_axis_f_ptr = arr_y;
    _y_axis_ptr_size = y_size;
  #endif
  _y_changed = true;
}

/*
  Destructor
*/
Chart::~Chart(){
  _dashboard->remove(this);
}