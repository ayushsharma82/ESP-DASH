#pragma once

// set to 1 to see debug logs
// keep to 0 for production: logging impacts performance
// #define DASH_DEBUG 1

#if defined(ESP8266)
  #include <ets_sys.h>
  #define DASH_LOGD(tag, format, ...) ets_printf("DEBUG [%s] " format "\n", tag, ##__VA_ARGS__)
  #define DASH_LOGW(tag, format, ...) ets_printf("WARN  [%s] " format "\n", tag, ##__VA_ARGS__)
#elif defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
  #include <stdio.h>
  #define DASH_LOGD(tag, format, ...) printf("DEBUG [%s] " format "\n", tag, ##__VA_ARGS__)
  #define DASH_LOGW(tag, format, ...) printf("WARN  [%s] " format "\n", tag, ##__VA_ARGS__)
#else
  #include <esp32-hal-log.h>
  #define DASH_LOGD ESP_LOGD
  #define DASH_LOGW ESP_LOGW
#endif

#include <ArduinoJson.h>
#include <inttypes.h>
#include <sys/time.h>

#include <charconv>
#include <functional>
#include <list>
#include <optional>
#include <string>

class ESPDash;

namespace dash {
#ifdef DASH_USE_STL_STRING
  using string = std::string;
#else
  using string = String;
#endif

  // function to convert an unknown type T to a JSON value by applying the correct precision for floats and doubles
  template <typename T, uint8_t Precision = 2>
  static bool toJsonValue(const JsonVariant& json, const T& value) {
    if constexpr (std::is_same_v<T, float>) {
      return json.set(String(static_cast<float>(value), (size_t)Precision));
    } else if constexpr (std::is_same_v<T, double>) {
      return json.set(String(static_cast<double>(value), (size_t)Precision));
    } else {
      // convert unknown other types eventually using convertToJson functions
      return json.set(value);
    }
  }

  // dash::to_string

  template <typename T, uint8_t Precision = 2, std::enable_if_t<std::is_same_v<T, dash::string>, bool> = true>
  static const dash::string& to_string(const T& value) { return value; }

  template <typename T, uint8_t Precision = 2, std::enable_if_t<std::is_same_v<T, const char*>, bool> = true>
  static dash::string to_string(const T& value) { return value; }

  template <typename T, uint8_t Precision = 2, std::enable_if_t<std::is_integral_v<T>, bool> = true>
  static dash::string to_string(const T& value) {
#ifdef DASH_USE_STL_STRING
    return std::to_string(value);
#else
    return String(value);
#endif
  }

  template <typename T, uint8_t Precision = 2, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
  static dash::string to_string(const T& value) {
#ifdef DASH_USE_STL_STRING
    return String(value, (size_t)Precision).c_str();
#else
    return String(value, (size_t)Precision);
#endif
  }

  // dash::string_as

  template <typename T, std::enable_if_t<std::is_same_v<T, dash::string> || std::is_same_v<T, const char*>, bool> = true>
  static std::optional<T> string_as(const char* str) {
    if (str == nullptr)
      return std::nullopt;
    return str;
  }

#ifdef ESP8266
  template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
  static std::optional<T> string_as(const char* str) {
    auto value = T{};
    size_t len = strlen(str);
    if (!len)
      return std::nullopt;
    auto [ptr, error] = std::from_chars(str, str + len, value);
    if (error != std::errc())
      return std::nullopt;
    return value;
  }
  template <typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
  static std::optional<T> string_as(const char* str) {
    char* end;
    auto value = strtod(str, &end);
    if (end == str)
      return std::nullopt;
    return value;
  }
#else
  template <typename T, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, bool> = true>
  static std::optional<T> string_as(const char* str) {
    auto value = T{};
    size_t len = strlen(str);
    if (!len)
      return std::nullopt;
    auto [ptr, error] = std::from_chars(str, str + len, value);
    if (error != std::errc())
      return std::nullopt;
    return value;
  }
#endif
}
