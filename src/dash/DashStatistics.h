#pragma once

#include "DashComponent.h"

namespace dash {
  // Statistic super class
  template <typename T = dash::string, uint8_t Precision = 2, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_same_v<T, dash::string> || std::is_same_v<T, const char*>, bool> = true>
  class Statistic : public Component {
    public:
      virtual ~Statistic() = default;

      // statistic value
      const T& value() const { return _value; }

      virtual void toJson(const JsonObject& json, bool onlyChanges) const override {
        Component::toJson(json, onlyChanges);
        if (!onlyChanges || hasChanged(Property::VALUE))
          dash::toJsonValue<T, Precision>(json["v"].to<JsonVariant>(), _value);
      }

      virtual Family family() const override { return Family::STATISTIC; }

    protected:
      // construct a new statistic and add it to the dashboard
      Statistic(ESPDash& dashboard, const char* name) : Component(dashboard, name), _value() {}
      // construct a new statistic without adding it to any dashboard
      Statistic(const char* name) : Component(name), _value() {}

      T _value;
  };

  // Statistic value class with set method
  template <typename T = dash::string, uint8_t Precision = 2, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_same_v<T, dash::string> || std::is_same_v<T, const char*>, bool> = true>
  class StatisticValue : public Statistic<T, Precision> {
    public:
      // construct a new statistic and add it to the dashboard
      StatisticValue(ESPDash& dashboard, const char* name) : Statistic<T, Precision>(dashboard, name) {}
      // construct a new statistic without adding it to any dashboard
      StatisticValue(const char* name) : Statistic<T, Precision>(name) {}

      ~StatisticValue() = default;

      // update the statistic value and returns true if the value has changed
      bool setValue(const T& value) {
        if (Statistic<T, Precision>::_value == value)
          return false;
        Statistic<T, Precision>::_value = value;
        Component::setChange(Component::Property::VALUE);
        return true;
      }

      // update the statistic value and returns true if the value has changed
      bool setValue(T&& value) {
        if (Statistic<T, Precision>::_value == value)
          return false;
        Statistic<T, Precision>::_value = std::forward<T>(value);
        Component::setChange(Component::Property::VALUE);
        return true;
      }
  };

  // Statistic provider class where the value if provided by a function
  template <typename T = dash::string, uint8_t Precision = 2, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_same_v<T, dash::string> || std::is_same_v<T, const char*>, bool> = true>
  class StatisticProvider : public Statistic<T, Precision> {
    private:
      std::function<T()> _provider = nullptr;

    public:
      // construct a new statistic and add it to the dashboard
      StatisticProvider(ESPDash& dashboard, const char* name) : Statistic<T, Precision>(dashboard, name) {}
      // construct a new statistic without adding it to any dashboard
      StatisticProvider(const char* name) : Statistic<T, Precision>(name) {}

      ~StatisticProvider() = default;

      // register a provider from where to get the statistic value
      void setProvider(std::function<T()> provider) { _provider = provider; }

      // update the statistic value by calling the provider and returns true if the value has changed
      virtual bool selfUpdate() override {
        if (!_provider)
          return false;
        T value = _provider();
        if (Statistic<T, Precision>::_value == value)
          return false;
        Statistic<T, Precision>::_value = std::forward<T>(value);
        Component::setChange(Component::Property::VALUE);
        return true;
      }
  };
} // namespace dash
