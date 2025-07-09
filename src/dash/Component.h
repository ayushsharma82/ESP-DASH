#pragma once

#include "Defines.h"

namespace dash {
  class Component {
    public:
      // general component families
      enum Family : uint8_t {
        CARD = 0b01,
        CHART = 0b10,
        STATISTIC = 0b100,
      };

      // describes the component fields that can be changed
      enum class Property : uint8_t {
        AXIS_X = 1,
        AXIS_Y,
        MAX,
        MIN,
        NAME, // name or title
        STEP,
        SYMBOL,
        VALUE,
      };

      virtual ~Component() = default;

      // get the component family
      virtual Family family() const = 0;

      // component ID
      uint16_t id() const { return _id; }
      // component name or title
      const char* name() const { return _name; }

      // check if one of the component property has changed
      bool hasChanged() const { return _bitset >> 1; }
      // check if a specific component property has changed
      bool hasChanged(Property property) const { return _bitset & (0b1 << static_cast<uint8_t>(property)); }
      // clear all component change flags.
      // hasChanged() will return false after this call
      void clearChanges() { _bitset &= 0b1; }

      // change component name (not all components support a name change)
      bool setName(const char* name) {
        if (strcmp(_name, name) == 0)
          return false;
        _name = name;
        setChange(Property::NAME);
        return true;
      }

      // auto-update the component internally
      // some components like StatisticProvider are capable of automatically updating their values before a dashboard refresh
      virtual bool selfUpdate() { return false; }

      virtual void toJson(const JsonObject& json, bool onlyChanges) const {
        json["id"] = id();
        switch (family()) {
          case Family::CARD:
          case Family::CHART:
            if (!onlyChanges || hasChanged(Property::NAME))
              json["n"] = name();
            break;
          case Family::STATISTIC:
            if (!onlyChanges || hasChanged(Property::NAME))
              json["k"] = name();
            break;
          default:
            assert(false);
            break;
        }
      }

      virtual void onEvent(__unused const JsonObject& json) {}

    protected:
      // construct a new component without adding it to any dashboard
      Component(const char* name) : _id(nextId()), _name(name) {}
      // construct a new component and add it to the dashboard
      Component(ESPDash& dashboard, const char* name);

      // mark a component property as changed
      void setChange(Property property) {

#ifdef DASH_DEBUG
        DASH_LOGD("DashComponent", "[%d] %s : property changed: %d", id(), name(), static_cast<uint8_t>(property));
#endif
        _bitset |= (0b1 << static_cast<uint8_t>(property));
      }

      // generate a new unique component ID
      static uint16_t nextId() {
        static uint16_t _IDS = 0;
        return _IDS++;
      }

    private:
      const uint16_t _id;     // component ID
      const char* _name;      // component name
      uint16_t _bitset = 0b1; // display is bit 0, bits 1-12 to track component changes
  };
} // namespace dash
