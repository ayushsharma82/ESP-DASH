#ifndef __CHART_H
#define __CHART_H

#include <functional>
#include "Arduino.h"
#include "vector.h"

#include "ESPDash.h"
#include "ArduinoJson.h"

// Default to Line Chart
enum {
  LINE_CHART,
};

struct ChartNames {
  int value;
  const char* type;
};

enum GraphAxisType { INTEGER, FLOAT, STRING };

// Chart X-Axis Data Structure
struct GraphAxisData {
  union alignas(8) {
      char *_value_s;
      float _value_f;
      int _value_i;
  };
};

// Forward Declaration
class ESPDash;

// Chart Class
class Chart {
  private:
    ESPDash *_dashboard;

    uint32_t _id;
    String _name;
    int   _type;
    bool  _changed;
    GraphAxisType _x_axis_type;
    GraphAxisType _y_axis_type;
    Vector<GraphAxisData> _x_axis;
    Vector<GraphAxisData> _y_axis;

  private:
    // Utility Methods
    const String generateJSON(bool change_only = false);

  public:
    Chart(ESPDash *dashboard, const int type, const char* name);
    void updateX(int arr_x[], int x_size);
    void updateX(float arr_x[], int x_size);
    void updateX(const String arr_x[], int x_size);
    void updateY(int arr_y[], int y_size);
    void updateY(float arr_y[], int y_size);
    ~Chart();

  friend class ESPDash;
};

#endif