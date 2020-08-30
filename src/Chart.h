#ifndef Chart_h
#define Chart_h

#include <functional>
#include "Arduino.h"

// Default to Line Chart
enum {
    LINE_CHART,
};

struct GraphAxisData {
    enum { INTEGER, FLOAT, STRING } value_type;
    union alignas(8) {
        char *value_s;
        float value_f;
        int value_i;
    };
};

class Chart {
  private:
    char* _name;
    int   _id;
    int   _type;
    bool  _changed;
    Vector<GraphAxisData> x_axis;
    Vector<int> y_axis;

  private:
    // Utility Methods
    const String generateJSON();

  public:
    Chart();
    void update(const int cardID, int arr_x[], int x_size, int arr_y[], int y_size);
    ~Chart();

  friend class ESPDashV3;
};

#endif