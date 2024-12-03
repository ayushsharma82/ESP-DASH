#ifndef __CHART_H
#define __CHART_H

#include "dash/DashWidget.h"

#ifndef DASH_USE_LEGACY_CHART_STORAGE
  #define DASH_USE_LEGACY_CHART_STORAGE 0
#endif

#if DASH_USE_LEGACY_CHART_STORAGE == 1
  #include <vector>
#endif

enum GraphAxisType { INTEGER,
                     FLOAT,
                     CHAR,
                     STRING };

#define BAR_CHART  dash::Component::Type::CHART_BAR

// Chart Class
class [[deprecated("This class is deprecated. Use a dash::Chart sub-class instead.")]] Chart : public dash::Widget {
  private:
    ESPDash* _dashboard = nullptr;
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
    int* _x_axis_i_ptr = nullptr;
    float* _x_axis_f_ptr = nullptr;
    const char** _x_axis_char_ptr = nullptr;
    dash::string* _x_axis_s_ptr = nullptr;
    unsigned int _x_axis_ptr_size = 0;
    /* Y-Axis */
    int* _y_axis_i_ptr = nullptr;
    float* _y_axis_f_ptr = nullptr;
    unsigned int _y_axis_ptr_size = 0;

    void clearXAxisPointers();
    void clearYAxisPointers();
#endif

  public:
    Chart(ESPDash* dashboard, const dash::Component::Type type, const char* name) : dash::Widget(*dashboard, name, type), _dashboard(dashboard) {}
    void updateX(int arr_x[], size_t x_size);
    void updateX(float arr_x[], size_t x_size);
    void updateX(dash::string arr_x[], size_t x_size);
    void updateX(const char* arr_x[], size_t x_size);
    void updateY(int arr_y[], size_t y_size);
    void updateY(float arr_y[], size_t y_size);
    virtual void toJson(const JsonObject& json, bool onlyChanges) const override;
    ~Chart();
};

#endif