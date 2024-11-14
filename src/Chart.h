#ifndef __CHART_H
#define __CHART_H

#include <functional>
#include "Arduino.h"

#include "ESPDash.h"
#include "ArduinoJson.h"

#ifndef DASH_USE_LEGACY_CHART_STORAGE
  #define DASH_USE_LEGACY_CHART_STORAGE 0
#endif

#if DASH_USE_LEGACY_CHART_STORAGE == 1
  #include <vector>
#endif

#ifdef DASH_USE_STL_STRING
#include <string>
namespace dash {
  using string = std::string;
}
#else
namespace dash {
  using string = String;
}
#endif

// Default to Line Chart
enum {
  BAR_CHART,
};

struct ChartNames {
  int value;
  const char* type;
};

enum GraphAxisType { INTEGER, FLOAT, CHAR, STRING };

// Forward Declaration
class ESPDash;

// Chart Class
class Chart {
  private:
    ESPDash *_dashboard;

    uint32_t _id;
    const char *_name;
    int   _type;
    bool  _x_changed;
    bool  _y_changed;
    GraphAxisType _x_axis_type;
    GraphAxisType _y_axis_type;

    #if DASH_USE_LEGACY_CHART_STORAGE == 1
      /* X-Axis */
      std::vector<int> _x_axis_i;
      std::vector<float> _x_axis_f;
      std::vector<dash::string> _x_axis_s;
      /* Y-Axis */
      std::vector<int> _y_axis_i;
      std::vector<float> _y_axis_f;

      void emptyXAxisVectors();
      void emptyYAxisVectors();
    #else 
      /* X-Axis */
      int *_x_axis_i_ptr = nullptr;
      float *_x_axis_f_ptr = nullptr;
      const char **_x_axis_char_ptr = nullptr;
      dash::string *_x_axis_s_ptr = nullptr;
      unsigned int _x_axis_ptr_size = 0;
      /* Y-Axis */
      int *_y_axis_i_ptr = nullptr;
      float *_y_axis_f_ptr = nullptr;
      unsigned int _y_axis_ptr_size = 0;

      void clearXAxisPointers();
      void clearYAxisPointers();
    #endif

  public:
    Chart(ESPDash *dashboard, const int type, const char* name);
    void updateX(int arr_x[], size_t x_size);
    void updateX(float arr_x[], size_t x_size);
    void updateX(dash::string arr_x[], size_t x_size);
    void updateX(const char* arr_x[], size_t x_size);
    void updateY(int arr_y[], size_t y_size);
    void updateY(float arr_y[], size_t y_size);
    ~Chart();

  friend class ESPDash;
};

#endif