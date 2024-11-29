#pragma once

#include "DashDefines.h"

namespace dash {
  class Component {
    public:
      // general component type
      enum class Family {
        CARD,
        CHART,
        STATISTIC,
      };

      // component sub-type
      enum class Type {
        // cards
        CARD_BUTTON,
        CARD_GENERIC,
        CARD_HUMIDITY,
        CARD_PROGRESS,
        CARD_SLIDER,
        CARD_STATUS,
        CARD_TEMPERATURE,
        // charts
        CHART_BAR,
        // statistics
        STATISTIC_PROVIDER,
        STATISTIC_VALUE,
      };

      // describes the component fields that can be changed
      enum Property : uint8_t {
        AXIS_X = 1,
        AXIS_Y,
        INDEX,
        MAX,
        MIN,
        NAME, // name or title
        STEP,
        SYMBOL,
        VALUE,
      };

      virtual ~Component() = default;

      // component ID
      uint16_t id() const { return _id; }
      // component name or title
      const char* name() const { return _name; }
      // component type
      Type type() const { return _type; }
      // check if the component belongs to a specific family (card, chart, statistic, tab)
      bool is(Family family) const {
        switch (family) {
          case Family::CARD:
            return _type >= Type::CARD_BUTTON && _type <= Type::CARD_TEMPERATURE;
          case Family::CHART:
            return _type == Type::CHART_BAR;
          case Family::STATISTIC:
            return _type >= Type::STATISTIC_PROVIDER && _type <= Type::STATISTIC_VALUE;
          default:
            return false;
        }
      }
      // get the component family
      Family family() const {
        if (is(Family::CARD))
          return Family::CARD;
        if (is(Family::CHART))
          return Family::CHART;
        if (is(Family::STATISTIC))
          return Family::STATISTIC;
        // should never happen => crash
        assert(false);
        return Family::CARD;
      }

      // check if one of the component property has changed
      bool hasChanged() const { return _bitset >> 1; }
      // check if a specific component property has changed
      bool hasChanged(Property property) const { return _bitset & (0b1 << property); }
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
        switch (family()) {
          case Family::CARD:
          case Family::CHART:
            json["id"] = id();
            if (!onlyChanges || hasChanged(Property::NAME))
              json["n"] = name();
            break;
          case Family::STATISTIC:
            json["i"] = id();
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
      Component(const char* name, Type type) : _id(nextId()), _name(name), _type(type) {}
      // construct a new component and add it to the dashboard
      Component(ESPDash& dashboard, const char* name, Type type);

      // mark a component property as changed
      void setChange(Property property) {

#ifdef DASH_DEBUG
        DASH_LOGD("DashComponent", "[%d] %s : property changed: %d", id(), name(), property);
#endif
        _bitset |= (0b1 << property);
      }

      // generate a new unique component ID
      static uint16_t nextId() {
        static uint16_t _IDS = 0;
        return _IDS++;
      }

    private:
      const uint16_t _id;     // component ID
      const char* _name;      // component name
      const Type _type;       // component type
      uint16_t _bitset = 0b1; // display is bit 0, bits 1-12 to track component changes
  };
} // namespace dash
