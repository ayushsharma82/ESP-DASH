#pragma once

#include "Component.h"

namespace dash {
  class Widget : public Component {
    public:
      Widget(const char* name) : Component(name) {}
      Widget(ESPDash& dashboard, const char* name) : Component(dashboard, name) {}

      virtual ~Widget() {
      }

      // component type (for UI rendering)
      virtual const char* type() const = 0;

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
        if (!onlyChanges)
          json["t"] = type();
        if (!onlyChanges || hasChanged(Property::INDEX))
          json["idx"] = _index;
      }

    protected:
      uint8_t _index;
  };
} // namespace dash
