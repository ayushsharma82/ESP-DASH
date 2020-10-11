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
void Chart::updateX(int arr_x[], int x_size){
  _x_axis_type = GraphAxisType::INTEGER;
  _x_axis.Empty();

  for(int i=0; i < x_size; i++){
    struct GraphAxisData data;
    data._value_i = arr_x[i];
    _x_axis.PushBack(data);
  }
  _changed = true;
}

void Chart::updateX(float arr_x[], int x_size){
  _x_axis_type = GraphAxisType::FLOAT;
  _x_axis.Empty();

  for(int i=0; i < x_size; i++){
    struct GraphAxisData data;
    data._value_f = arr_x[i];
    _x_axis.PushBack(data);
  }
  _changed = true;
}

void Chart::updateX(const String arr_x[], int x_size){
  _x_axis_type = GraphAxisType::STRING;
  _x_axis.Empty();

  for(int i=0; i < x_size; i++){
    struct GraphAxisData data;
    int size = arr_x[i].length();
    data._value_s = new char[size+1];
    strncpy(data._value_s, arr_x[i].c_str(), size);
    _x_axis.PushBack(data);
  }
  _changed = true;
}

void Chart::updateY(int arr_y[], int y_size){
  _y_axis_type = GraphAxisType::INTEGER;
  _y_axis.Empty();

  for(int i=0; i < y_size; i++){
    struct GraphAxisData data;
    data._value_i = arr_y[i];
    _y_axis.PushBack(data);
  }
  _changed = true;
}

void Chart::updateY(float arr_y[], int y_size){
  _y_axis_type = GraphAxisType::FLOAT;
  _y_axis.Empty();

  for(int i=0; i < y_size; i++){
    struct GraphAxisData data;
    data._value_f = arr_y[i];
    _y_axis.PushBack(data);
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
  for(int i=0; i < _x_axis.Size(); i++){
    switch (_x_axis_type) {
      case GraphAxisType::INTEGER:
        xAxis.add(_x_axis[i]._value_i);
        break;
      case GraphAxisType::FLOAT:
        xAxis.add(_x_axis[i]._value_f);
        break;
      case GraphAxisType::STRING:
        xAxis.add(_x_axis[i]._value_s);
        break;
      default:
        // blank value
        break;
    }
  }
  
  JsonArray yAxis = doc["y_axis"].to<JsonArray>();
  for(int i=0; i < _y_axis.Size(); i++){
    switch (_y_axis_type) {
      case GraphAxisType::INTEGER:
        xAxis.add(_y_axis[i]._value_i);
        break;
      case GraphAxisType::FLOAT:
        xAxis.add(_y_axis[i]._value_f);
        break;
      default:
        // blank value
        break;
    }
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