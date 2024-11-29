// This file holds all the deprecated class and method implementations

#include "Card.h"
#include "Chart.h"
#include "Statistic.h"

#include "ESPDash.h"

Statistic::~Statistic() { _dashboard->remove(*this); }

/*
  Chart
*/

#if DASH_USE_LEGACY_CHART_STORAGE == 1
void Chart::emptyXAxisVectors() {
  if (!_x_axis_i.empty())
    _x_axis_i.clear();
  if (!_x_axis_f.empty())
    _x_axis_f.clear();
  if (!_x_axis_s.empty())
    _x_axis_s.clear();
}

void Chart::emptyYAxisVectors() {
  if (!_y_axis_i.empty())
    _y_axis_i.clear();
  if (!_y_axis_f.empty())
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

void Chart::updateX(int arr_x[], size_t x_size) {
  _x_axis_type = GraphAxisType::INTEGER;
#if DASH_USE_LEGACY_CHART_STORAGE == 1
  emptyXAxisVectors();
  for (int i = 0; i < x_size; i++) {
    _x_axis_i.push_back(arr_x[i]);
  }
#else
  clearXAxisPointers();
  _x_axis_i_ptr = arr_x;
  _x_axis_ptr_size = x_size;
#endif
  setChange(Property::AXIS_X);
}

void Chart::updateX(float arr_x[], size_t x_size) {
  _x_axis_type = GraphAxisType::FLOAT;
#if DASH_USE_LEGACY_CHART_STORAGE == 1
  emptyXAxisVectors();
  for (int i = 0; i < x_size; i++) {
    _x_axis_f.push_back(arr_x[i]);
  }
#else
  clearXAxisPointers();
  _x_axis_f_ptr = arr_x;
  _x_axis_ptr_size = x_size;
#endif
  setChange(Property::AXIS_X);
}

void Chart::updateX(dash::string arr_x[], size_t x_size) {
  _x_axis_type = GraphAxisType::STRING;
#if DASH_USE_LEGACY_CHART_STORAGE == 1
  emptyXAxisVectors();
  for (int i = 0; i < x_size; i++) {
    _x_axis_s.push_back(arr_x[i].c_str());
  }
#else
  clearXAxisPointers();
  _x_axis_s_ptr = arr_x;
  _x_axis_ptr_size = x_size;
#endif
  setChange(Property::AXIS_X);
}

void Chart::updateX(const char* arr_x[], size_t x_size) {
  _x_axis_type = GraphAxisType::CHAR;
#if DASH_USE_LEGACY_CHART_STORAGE == 1
  emptyXAxisVectors();
  for (int i = 0; i < x_size; i++) {
    _x_axis_s.push_back(arr_x[i]);
  }
#else
  clearXAxisPointers();
  _x_axis_char_ptr = arr_x;
  _x_axis_ptr_size = x_size;
#endif
  setChange(Property::AXIS_X);
}

void Chart::updateY(int arr_y[], size_t y_size) {
  _y_axis_type = GraphAxisType::INTEGER;
#if DASH_USE_LEGACY_CHART_STORAGE == 1
  emptyYAxisVectors();
  for (int i = 0; i < y_size; i++) {
    _y_axis_i.push_back(arr_y[i]);
  }
#else
  clearYAxisPointers();
  _y_axis_i_ptr = arr_y;
  _y_axis_ptr_size = y_size;
#endif
  setChange(Property::AXIS_Y);
}

void Chart::updateY(float arr_y[], size_t y_size) {
  _y_axis_type = GraphAxisType::FLOAT;
#if DASH_USE_LEGACY_CHART_STORAGE == 1
  emptyYAxisVectors();
  for (int i = 0; i < y_size; i++) {
    _y_axis_f.push_back(arr_y[i]);
  }
#else
  clearYAxisPointers();
  _y_axis_f_ptr = arr_y;
  _y_axis_ptr_size = y_size;
#endif
  setChange(Property::AXIS_Y);
}

void Chart::toJson(const JsonObject& json, bool onlyChanges) const {
  dash::Widget::toJson(json, onlyChanges);

  if (!onlyChanges || hasChanged(Property::AXIS_X)) {
    JsonArray xAxis = json["x"].to<JsonArray>();
    switch (_x_axis_type) {
      case GraphAxisType::INTEGER:
#if DASH_USE_LEGACY_CHART_STORAGE == 1
        for (int i = 0; i < _x_axis_i.size(); i++)
          xAxis.add(_x_axis_i[i]);
#else
        if (_x_axis_i_ptr != nullptr) {
          for (unsigned int i = 0; i < _x_axis_ptr_size; i++)
            xAxis.add(_x_axis_i_ptr[i]);
        }
#endif
        break;
      case GraphAxisType::FLOAT:
#if DASH_USE_LEGACY_CHART_STORAGE == 1
        for (int i = 0; i < _x_axis_f.size(); i++)
          xAxis.add(_x_axis_f[i]);
#else
        if (_x_axis_f_ptr != nullptr) {
          for (unsigned int i = 0; i < _x_axis_ptr_size; i++)
            xAxis.add(_x_axis_f_ptr[i]);
        }
#endif
        break;
      case GraphAxisType::CHAR:
#if DASH_USE_LEGACY_CHART_STORAGE == 1
        for (int i = 0; i < _x_axis_s.size(); i++)
          xAxis.add(_x_axis_s[i].c_str());
#else
        if (_x_axis_char_ptr != nullptr) {
          for (unsigned int i = 0; i < _x_axis_ptr_size; i++)
            xAxis.add(_x_axis_char_ptr[i]);
        }
#endif
        break;
      case GraphAxisType::STRING:
#if DASH_USE_LEGACY_CHART_STORAGE == 1
        for (int i = 0; i < _x_axis_s.size(); i++)
          xAxis.add(_x_axis_s[i].c_str());
#else
        if (_x_axis_s_ptr != nullptr) {
          for (unsigned int i = 0; i < _x_axis_ptr_size; i++)
            xAxis.add(_x_axis_s_ptr[i]);
        }
#endif
        break;
      default:
        // blank value
        break;
    }
  }

  if (!onlyChanges || hasChanged(Property::AXIS_Y)) {
    JsonArray yAxis = json["y"].to<JsonArray>();
    switch (_y_axis_type) {
      case GraphAxisType::INTEGER:
#if DASH_USE_LEGACY_CHART_STORAGE == 1
        for (int i = 0; i < _y_axis_i.size(); i++)
          yAxis.add(_y_axis_i[i]);
#else
        if (_y_axis_i_ptr != nullptr) {
          for (unsigned int i = 0; i < _y_axis_ptr_size; i++)
            yAxis.add(_y_axis_i_ptr[i]);
        }
#endif
        break;
      case GraphAxisType::FLOAT:
#if DASH_USE_LEGACY_CHART_STORAGE == 1
        for (int i = 0; i < _y_axis_f.size(); i++)
          yAxis.add(_y_axis_f[i]);
#else
        if (_y_axis_f_ptr != nullptr) {
          for (unsigned int i = 0; i < _y_axis_ptr_size; i++)
            yAxis.add(_y_axis_f_ptr[i]);
        }
#endif
        break;
      default:
        // blank value
        break;
    }
  }
}

Chart::~Chart() {
  _dashboard->remove(*this);
}

/*
  Card
*/

Card::Card(ESPDash* dashboard, const dash::Component::Type type, const char* name, const char* symbol, const int min, const int max, const int step) : dash::Widget(*dashboard, name, type), _dashboard(dashboard) {
  _symbol = symbol ? symbol : "";
  _value_min = min;
  _value_max = max;
  _value_step = step;
  setIndex(255);
  _value_type = Card::INTEGER;
}

Card::Card(ESPDash* dashboard, const dash::Component::Type type, const char* name, const char* symbol, const float min, const float max, const float step) : dash::Widget(*dashboard, name, type), _dashboard(dashboard) {
  _symbol = symbol ? symbol : "";
  _value_min_f = min;
  _value_max_f = max;
  _value_step_f = step;
  setIndex(255);
  _value_type = Card::FLOAT;
}

void Card::update(int value, const char* symbol) {
  if (_value_type == Card::STRING) {
    _value_s = "";
  }
  _value_type = Card::INTEGER;
  if (_value_i != value) {
    _value_i = value;
    setChange(Property::VALUE);
  }
  if (symbol && _symbol != symbol) {
    _symbol = symbol;
    setChange(Property::SYMBOL);
  }
}

void Card::update(float value, const char* symbol) {
  if (_value_type == Card::STRING) {
    _value_s = "";
  }
  _value_type = Card::FLOAT;
  if (_value_f != value) {
    _value_f = value;
    setChange(Property::VALUE);
  }
  if (symbol && _symbol != symbol) {
    _symbol = symbol;
    setChange(Property::SYMBOL);
  }
}

void Card::update(const char* value, const char* symbol) {
  if (_value_type == Card::STRING) {
    if (_value_s != value) {
      _value_s = value;
      setChange(Property::VALUE);
    }
  }
  _value_type = Card::STRING;
  if (symbol && _symbol != symbol) {
    _symbol = symbol;
    setChange(Property::SYMBOL);
  }
}

void Card::update(dash::string&& value, const char* symbol) {
  if (_value_type == Card::STRING) {
    if (_value_s != value)
      _value_s = std::move(value);
    setChange(Property::VALUE);
  }
  _value_type = Card::STRING;
  if (symbol && _symbol != symbol) {
    _symbol = symbol;
    setChange(Property::SYMBOL);
  }
}

void Card::update(bool value, const char* symbol) {
  if (_value_type == Card::STRING) {
    _value_s = "";
  }
  _value_type = Card::INTEGER;
  if (_value_i != value) {
    _value_i = value;
    setChange(Property::VALUE);
  }
  if (symbol && _symbol != symbol) {
    _symbol = symbol;
    setChange(Property::SYMBOL);
  }
}

void Card::toJson(const JsonObject& json, bool onlyChanges) const {
  dash::Widget::toJson(json, onlyChanges);

  if (!onlyChanges) {
    // Don't add useless values to cards which don't require them
    dash::Component::Type type = dash::Widget::type();
    if (type == SLIDER_CARD || type == PROGRESS_CARD) {
      if (_value_type == Card::FLOAT) {
        json["min"] = String(_value_min_f, 2);
        json["max"] = String(_value_max_f, 2);
        json["step"] = String(_value_step_f, 2);
      } else {
        json["min"] = _value_min;
        json["max"] = _value_max;
        if (_value_step != 1)
          json["step"] = _value_step;
      }
    }
  }

  if (!onlyChanges || hasChanged(Property::SYMBOL))
    json["s"] = _symbol;

  if (!onlyChanges || hasChanged(Property::VALUE)) {
    switch (_value_type) {
      case Card::INTEGER:
        json["v"] = _value_i;
        break;
      case Card::FLOAT:
        json["v"] = String(_value_f, 2);
        break;
      case Card::STRING:
        if (_value_s.length()) {
          json["v"] = _value_s;
        }
        break;
      default:
        // blank value
        break;
    }
  }
}

void Card::onEvent(const JsonObject& json) {
  if (_callback && json["command"] == "button:clicked") {
    _callback(json["value"].as<int>());
    return;
  }

  if (_callback_f && _value_type == Card::FLOAT && json["command"] == "slider:changed") {
    _callback_f(json["value"].as<float>());
    return;
  }

  if (_callback && json["command"] == "slider:changed") {
    _callback(json["value"].as<int>());
    return;
  }
}

Card::~Card() {
  _dashboard->remove(*this);
}
