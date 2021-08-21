#ifndef __CHART_H
#define __CHART_H

#include <functional>
#include <Arduino.h>
#include <ArduinoJson.h>

#include "vector.h"
#include "Widget.h"

// Default to Line Chart
enum {
  BAR_CHART,
};


enum GraphAxisType { INTEGER, FLOAT, STRING };

// Forward Declaration
class ESPDash;
class Tab;

// Chart Class
class Chart: public Widget{
  private:
    ESPDash *_dashboard;
    Tab *_tab;

    GraphAxisType _x_axis_type;
    GraphAxisType _y_axis_type;
    /* X-Axis */
    Vector<int> _x_axis_i;
    Vector<float> _x_axis_f;
    Vector<String> _x_axis_s;
    /* Y-Axis */
    Vector<int> _y_axis_i;
    Vector<float> _y_axis_f;

    Widget::JsonDocument generateLayout() override;
    Widget::JsonDocument generateUpdate() override;

  public:
    Chart(ESPDash *dashboard, const int type, const char* name);
    Chart(Tab *tab, const int type, const char* name);
    void updateX(int arr_x[], size_t x_size);
    void updateX(float arr_x[], size_t x_size);
    void updateX(String arr_x[], size_t x_size);
    void updateY(int arr_y[], size_t y_size);
    void updateY(float arr_y[], size_t y_size);
    ~Chart();

    friend class Tab;
};

#endif