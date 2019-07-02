#ifndef ESPDash_h
#define ESPDash_h

/*
* ESP-DASH V2
* Made by Ayush Sharma
* Github URL: https://github.com/ayushsharma82/ESP-DASH
* Support Me: https://www.patreon.com/asrocks5
*
* - Version Changelog - 
* V1.0.0 - 11 Nov. 2017 - Library was Born
* V1.0.1 - 13 Nov. 2017 - Fixed Empty SPIFFS Issue
* V1.0.2 - 13 Nov. 2017 - Improvements on SPIFFS Issue
* V1.0.3 - 24 Dec. 2017 - Pushing to Library Manager
*
* = Library Rewritten! =
* V2.0.0 - 25 Jan 2019 - Wohoo! A breakthrough in performance and capabilities!
*
* 
* Credits:
* Malcolm Brook (https://github.com/malbrook) for Slider Card
*/

#include "Arduino.h"
#include "stdlib_noniso.h"

#if defined(ESP8266)
    #define HARDWARE "ESP8266"
    #include "ESP8266WiFi.h"
    #include "ESPAsyncTCP.h"
    #include "ESPAsyncWebServer.h"
    #include "ArduinoJson.h"
#elif defined(ESP32)
    #define HARDWARE "ESP32"
    #include <esp_int_wdt.h>
    #include <esp_task_wdt.h>
    #include "WiFi.h"
    #include "AsyncTCP.h"
    #include "ESPAsyncWebServer.h"
    #include "ArduinoJson.h"
#endif

#include "webpage.h"

typedef std::function<void(const char* buttonId)> DashButtonHandler;
typedef std::function<void(const char* sliderId, int sliderValue)> DashSliderHandler;

#define DEBUG_MODE 1 // change to 1 for DEBUG Messages

// Debug mode
#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif

#define TEMPERATURE_CARD_TYPES 6
#define STATUS_CARD_TYPES 4
#define SLIDER_CARD_TYPES 4

#if defined(ESP8266)
    #define BUTTON_CARD_LIMIT 20
    #define TOGGLE_BUTTON_CARD_LIMIT 20
    #define NUMBER_CARD_LIMIT 20
    #define TEMPERATURE_CARD_LIMIT 20
    #define HUMIDITY_CARD_LIMIT 20
    #define STATUS_CARD_LIMIT 20
    #define LINE_CHART_LIMIT 5
    #define GAUGE_CHART_LIMIT 20
    #define SLIDER_CARD_LIMIT 10
#elif defined(ESP32)
    #define BUTTON_CARD_LIMIT 50
    #define TOGGLE_BUTTON_CARD_LIMIT 50
    #define NUMBER_CARD_LIMIT 50
    #define TEMPERATURE_CARD_LIMIT 50
    #define HUMIDITY_CARD_LIMIT 50
    #define STATUS_CARD_LIMIT 50
    #define LINE_CHART_LIMIT 10
    #define GAUGE_CHART_LIMIT 50
    #define SLIDER_CARD_LIMIT 20
#endif



class ESPDashClass{

    public:
        void init(AsyncWebServer& server);
        void disableStats();    // To Disable Stats and disable reboot

        void addNumberCard(const char* _id, const char* _name); // Add Number card with default value
        void addNumberCard(const char* _id, const char* _name, int _value); // Add Number card with custom value
        void updateNumberCard(const char* _id, int _value); // Update Number Card with custom value

        void addTemperatureCard(const char* _id, const char* _name, int _type); // Add Temperature Card with custom type and default value
        void addTemperatureCard(const char* _id, const char* _name, int _type, int _value); // Add Temperature Card with custom value
        void updateTemperatureCard(const char* _id, int _value); // Update Temperature Card with custom value

        void addHumidityCard(const char* _id, const char* _name);   // Add default Humidity card
        void addHumidityCard(const char* _id, const char* _name, int _value);  // Add Humidity Card with custom value
        void updateHumidityCard(const char* _id, int _value); // Update Humidity Card with custom value

        void addStatusCard(const char* _id, const char* _name); // Add Default Status Card
        void addStatusCard(const char* _id, const char* _name, int _type); // Add Status Card with more status types
        void addStatusCard(const char* _id, const char* _name, bool _type); // Add Status Card with true / false
        void updateStatusCard(const char* _id, int _type);
        void updateStatusCard(const char* _id, bool _type);

        void addButtonCard(const char* _id, const char* _name); // Add Button

        void addToggleButtonCard(const char* _id, const char* _name, bool _value); // Add Toggle Button with true / false
        void updateToggleButtonCard(const char* _id, bool _value); // Update Toggle Button with true / false

        
        // Add Slider Card 
        void addSliderCard(const char* _id, const char* _name, int _type); 
        void updateSliderCard(const char* _id, int _value); 
        
        //Initiate a Line Chart with Integer x axis and custom y axis
        void addLineChart(const char* _id, const char* _name, int _x_axis_value[], int _x_axis_size, const char* _y_axis_name, int _y_axis_value[], int _y_axis_size);
        // Initiate a Line Chart with String x axis and custom y axis
        void addLineChart(const char* _id, const char* _name, String _x_axis_value[], int _x_axis_size, const char* _y_axis_name, int _y_axis_value[], int _y_axis_size); 
        void updateLineChart(const char* _id, int _x_axis_value[], int _x_axis_size, int _y_axis_value[], int _y_axis_size); // Update a Line Chart with custom Int x axis and y axis
        void updateLineChart(const char* _id, String _x_axis_value[], int _x_axis_size, int _y_axis_value[], int _y_axis_size); // Update a Line Chart with custom String x axis and y axis

        void addGaugeChart(const char *_id, const char *_name); // Add Gauge card with default value
        void addGaugeChart(const char *_id, const char *_name, int _value); // Add Gauge card with default value
        void updateGaugeChart(const char* _id, int _value); // Update Gauge card with default value


        void attachButtonClick(DashButtonHandler handler){
            _buttonClickFunc = handler;
        }
        
        void attachSliderChanged(DashSliderHandler handler){
            _sliderChangedFunc = handler;
        }

        
    private:
        bool stats_enabled = true;
        DashButtonHandler _buttonClickFunc;
        DashSliderHandler _sliderChangedFunc;
        // Button Cards
        // Data Relation:
        // (Handle Incomming Websocket Requests via Card ID) Card ID -> Card Name
        String button_card_id[BUTTON_CARD_LIMIT] = {};
        String button_card_name[BUTTON_CARD_LIMIT] = {};

        // Number Cards
        // Card ID -> Card Name -> Integer Value
        String number_card_id[NUMBER_CARD_LIMIT] = {};
        String number_card_name[NUMBER_CARD_LIMIT] = {};
        uint16_t number_card_value[NUMBER_CARD_LIMIT] = {};

        // Temperature Cards
        // Data Relation:
        // Card ID -> Card Name ->>
        // Types 
        // 0 - °C [Celsius] 
        // 1 - °F [Fahrenheit]
        // 2 - K [Kelvin]
        // 3 - °R [Rakine] 
        // 4 - °De [Delisle]
        // 5 - °N [Newton]
        // ->> Integer Value
        String temperature_card_id[TEMPERATURE_CARD_LIMIT] = {};
        String temperature_card_name[TEMPERATURE_CARD_LIMIT] = {};
        int temperature_card_type[TEMPERATURE_CARD_LIMIT] = {};
        int temperature_card_value[TEMPERATURE_CARD_LIMIT] = {};

        // Humidity Cards
        // Data Relation:
        // Card ID -> Card Name -> Integer Value
        String humidity_card_id[HUMIDITY_CARD_LIMIT] = {};
        String humidity_card_name[HUMIDITY_CARD_LIMIT] = {};
        int humidity_card_value[HUMIDITY_CARD_LIMIT] = {};

        // Status Cards
        // Data Relation:
        // Card ID -> Card Name -> Card Type
        // 0 - false 
        // 1 - true
        // 2 - warning
        // 3 - paused
        String status_card_id[STATUS_CARD_LIMIT] = {};
        String status_card_name[STATUS_CARD_LIMIT] = {};
        int status_card_value[STATUS_CARD_LIMIT] = {};

        // Button Status Cards
        // Data Relation:
        // Card ID -> Card Name -> Card Type
        // 0 - false 
        // 1 - true
        String toggle_button_card_id[TOGGLE_BUTTON_CARD_LIMIT] = {};
        String toggle_button_card_name[TOGGLE_BUTTON_CARD_LIMIT] = {};
        bool toggle_button_card_value[TOGGLE_BUTTON_CARD_LIMIT] = {};

        // Graph Cards
        // Data Relation:
        // Card ID -> Card Name ->>
        // X Axis -> Bool Type -> String <- OR -> ( Array Length -> Integer Array )
        // Y Axis -> Y Axis Name -> Array Length -> Integer Array
        String line_chart_id[LINE_CHART_LIMIT] = {};
        String line_chart_name[LINE_CHART_LIMIT] = {};
        // X Axis // A Graph can either have a STRING Type X Axis or Integer Type
        bool line_chart_x_axis_type[LINE_CHART_LIMIT] = {}; // Boolean which indicates the type // true = String, false = Int
        String line_chart_x_axis_value_string[LINE_CHART_LIMIT][100] = {};   // String Type
        int line_chart_x_axis_size[LINE_CHART_LIMIT] = {};
        int line_chart_x_axis_value_int[LINE_CHART_LIMIT][100] = {};  // Integer Type
        // Y Axis
        String line_chart_y_axis_name[LINE_CHART_LIMIT] = {};
        int line_chart_y_axis_size[LINE_CHART_LIMIT] = {};
        int line_chart_y_axis_value[LINE_CHART_LIMIT][100] = {};

        // Gauge Charts
        // Card ID -> Card Name -> Integer Value
        String gauge_chart_id[GAUGE_CHART_LIMIT] = {};
        String gauge_chart_name[GAUGE_CHART_LIMIT] = {};
        uint16_t gauge_chart_value[GAUGE_CHART_LIMIT] = {};

        // Slider Card
        // Data Relation:
        // Card ID -> Card Name -> Card Type
        // 0 - vertical bottom to top
        // 1 - vertical top to bottom
        // 2 - horizontal left to right
        // 3 - horizontal right to left        
        String slider_card_id[SLIDER_CARD_LIMIT] = {};
        String slider_card_name[SLIDER_CARD_LIMIT] = {};
        int slider_card_type[SLIDER_CARD_LIMIT] = {}; 
        int slider_card_value[SLIDER_CARD_LIMIT] = {};       
        

        static void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);
        void generateLayoutResponse(String& result);
        void generateStatsResponse(String& result);
        void generateRebootResponse(String& result);
        size_t getTotalResponseCapacity();
        size_t getNumberCardsLen();
        size_t getTemperatureCardsLen();
        size_t getHumidityCardsLen();
        size_t getStatusCardsLen();
        size_t getButtonCardsLen();
        size_t getButtonStatusCardsLen();
        size_t getLineChartsLen();
        size_t getGaugeChartsLen();
        size_t getSliderCardsLen();
};

extern ESPDashClass ESPDash;
#endif
