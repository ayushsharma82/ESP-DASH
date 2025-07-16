#pragma once

#include "Widget.h"

namespace dash {
  template <typename X, typename Y, std::enable_if_t<(std::is_integral_v<X> || std::is_floating_point_v<X> || std::is_same_v<X, dash::string> || std::is_same_v<X, const char*>) && (std::is_integral_v<Y> || std::is_floating_point_v<Y>), bool> = true>
  class Chart : public Widget {
    public:
      virtual ~Chart() = default;

      virtual Family family() const override { return Family::CHART; }

      const X* x() const { return _x_axis_i_ptr; }
      const Y* y() const { return _y_axis_i_ptr; }
      size_t xSize() const { return _x_axis_ptr_size; }
      size_t ySize() const { return _y_axis_ptr_size; }

      // set the x-axis values
      bool setX(X arr_x[], size_t x_size) {
        _x_axis_i_ptr = arr_x;
        _x_axis_ptr_size = x_size;
        setChange(Property::AXIS_X);
        return true;
      }

      // set the y-axis values
      bool setY(Y arr_y[], size_t y_size) {
        _y_axis_i_ptr = arr_y;
        _y_axis_ptr_size = y_size;
        setChange(Property::AXIS_Y);
        return true;
      }

      virtual void toJson(const JsonObject& json, bool onlyChanges) const override {
        Widget::toJson(json, onlyChanges);
        if (!onlyChanges || hasChanged(Property::AXIS_X)) {
          JsonArray xAxis = json["x"].to<JsonArray>();
          for (size_t i = 0; i < _x_axis_ptr_size; i++)
            xAxis.add(_x_axis_i_ptr[i]);
        }
        if (!onlyChanges || hasChanged(Property::AXIS_Y)) {
          JsonArray yAxis = json["y"].to<JsonArray>();
          for (size_t i = 0; i < _y_axis_ptr_size; i++)
            yAxis.add(_y_axis_i_ptr[i]);
        }
      }

    protected:
      // construct a new chart and add it to the dashboard
      Chart(ESPDash& dashboard, const char* name) : Widget(dashboard, name) {}
      // construct a new chart without adding it to any dashboard
      Chart(const char* name) : Widget(name) {}

      X* _x_axis_i_ptr = nullptr;
      Y* _y_axis_i_ptr = nullptr;
      size_t _x_axis_ptr_size = 0;
      size_t _y_axis_ptr_size = 0;
  };

  // Bar Chart
  template <typename X, typename Y, std::enable_if_t<(std::is_integral_v<X> || std::is_floating_point_v<X> || std::is_same_v<X, dash::string> || std::is_same_v<X, const char*>) && (std::is_integral_v<Y> || std::is_floating_point_v<Y>), bool> = true>
  class BarChart : public Chart<X, Y> {
    public:
      BarChart(ESPDash& dashboard, const char* name) : Chart<X, Y>(dashboard, name) {}
      BarChart(const char* name) : Chart<X, Y>(name) {}
      virtual ~BarChart() = default;
      virtual const char* type() const override { return "bch"; }
  };
} // namespace dash
