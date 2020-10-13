#include "Chart.h"

// Integral type to string pairs events
// ID, type
struct ChartNames chartTags[] = {
  {LINE_CHART, "line"},
};


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
  Generate JSON for UI
*/
const String Chart::generateJSON(bool change_only){
  String data = "";

  DynamicJsonDocument doc(2048);
  doc["id"] = _id;
  if(!change_only){
    doc["name"] = _name;
    doc["type"] = chartTags[_type].type;
  }

  JsonArray xAxis = doc["x_axis"].to<JsonArray>();
  switch (_x_axis_type) {
    case GraphAxisType::INTEGER:
      for(int i=0; i < _x_axis_i.Size(); i++)
        xAxis.add(_x_axis_i[i]);
      break;
    case GraphAxisType::FLOAT:
      for(int i=0; i < _x_axis_f.Size(); i++)
        xAxis.add(_x_axis_f[i]);
      break;
    case GraphAxisType::STRING:
      for(int i=0; i < _x_axis_s.Size(); i++)
        xAxis.add(_x_axis_s[i].c_str());
      break;
    default:
      // blank value
      break;
  }
  
  JsonArray yAxis = doc["y_axis"].to<JsonArray>();
  switch (_y_axis_type) {
    case GraphAxisType::INTEGER:
      for(int i=0; i < _y_axis_i.Size(); i++)
        yAxis.add(_y_axis_i[i]);
      break;
    case GraphAxisType::FLOAT:
      for(int i=0; i < _y_axis_f.Size(); i++)
        yAxis.add(_y_axis_f[i]);
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
Chart::~Chart(){
  _dashboard->remove(this);
}