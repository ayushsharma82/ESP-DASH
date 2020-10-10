#ifndef __CHART_H
#define __CHART_H

#include <functional>
#include "Arduino.h"
#include "vector.h"

// Default to Line Chart
enum {
  LINE_CHART,
};

// Chart X-Axis Data Structure
struct GraphAxisData {
    enum { INTEGER, FLOAT, STRING } value_type;
    union alignas(8) {
        char *value_s;
        float value_f;
        int value_i;
    };
};

// Forward Declaration
class ESPDash;

// Chart Class
class Chart {
  private:
    uint32_t _id;
    String _name;
    int   _type;
    bool  _changed;
    Vector<GraphAxisData> x_axis;
    Vector<int> y_axis;

  private:
    // Utility Methods
    const String generateJSON(bool change_only = false);

  public:
    Chart(ESPDash *dashboard, const int type, const char* name);
    void update(int arr_x[], int x_size, int arr_y[], int y_size);
    ~Chart();

  friend class ESPDash;
};

#endif