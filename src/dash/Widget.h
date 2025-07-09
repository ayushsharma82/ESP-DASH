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

      virtual void toJson(const JsonObject& json, bool onlyChanges) const override {
        Component::toJson(json, onlyChanges);
        if (!onlyChanges)
          json["t"] = type();
      }
  };
} // namespace dash
