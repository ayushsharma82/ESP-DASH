#pragma once

#include "DashComponent.h"

namespace dash {
  class Widget : public Component {
    public:
      Widget(const char* name, Type type) : Component(name, type) {}
      Widget(ESPDash& dashboard, const char* name, Type type) : Component(dashboard, name, type) {}

      virtual ~Widget() {}

      // widget index (position) in the dashboard
      uint8_t index() const { return _index; }

      // set the widget position in the dashboard
      bool setIndex(uint8_t index) {
        if (_index == index)
          return false;
        _index = index;
        setChange(Property::INDEX);
        return true;
      }

      virtual void toJson(const JsonObject& json, bool onlyChanges) const override {
        Component::toJson(json, onlyChanges);
        if (!onlyChanges || hasChanged(Property::INDEX))
          json["t"] = _typeName(type());
        if (!onlyChanges || hasChanged(Property::INDEX))
          json["idx"] = _index;
      }

    private:
      uint8_t _index;

      // widget type name
      static const char* _typeName(Type type) {
        switch (type) {
          case Type::CARD_BUTTON:
            return "button";
          case Type::CARD_GENERIC:
            return "generic";
          case Type::CARD_HUMIDITY:
            return "humidity";
          case Type::CARD_PROGRESS:
            return "progress";
          case Type::CARD_SLIDER:
            return "slider";
          case Type::CARD_STATUS:
            return "status";
          case Type::CARD_TEMPERATURE:
            return "temperature";
          case Type::CHART_BAR:
            return "bar";
          default:
            assert(false);
            return "";
        }
      }
  };
} // namespace dash
