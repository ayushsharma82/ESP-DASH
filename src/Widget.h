#pragma once

#include <cstdint>
#include <WString.h>
#include <Arduino.h>

#define WIDGET_JSON_SIZE 1024

struct WidgetNames {
  int value;
  const char* type;
};

class Tab;
namespace ArduinoJson {
  template<typename allocator>
  class BasicJsonDocument;
  class DefaultAllocator;
}

class Widget {
  public:
    using JsonDocument = ArduinoJson::BasicJsonDocument<ArduinoJson::DefaultAllocator>;

    Widget() {
      #if defined(ESP8266)
        _id = RANDOM_REG32;
      #elif defined(ESP32)
        _id = esp_random();
      #endif
    };
    bool isChanged() {
      return _changed;
    };
    uint32_t getId() const {
      return _id;
    };
    virtual ~Widget() = default;

  protected:
    uint32_t _id;
    String _name;
    int   _type;
    bool  _changed;

    virtual JsonDocument generateLayout() = 0;
    virtual JsonDocument generateUpdate() = 0;

    friend class Tab;
};