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
*
*
* Core routines rewritten by Cassiano Martin <cassiano.martin@gmail.com>
* Not all functions implemented yet, missing button and slider routines.
* Next step is to reduce json library dependency, in fact we need only a
* parser, and not a full-blown library.
*
*/

#include "ESPDash.h"

// integral type to string pairs
// ID, type, json_method call
CardNames cNames[] = {
    {TYPE_NUMBER_CARD, "number", "updateNumberCard"},
    {TYPE_BUTTON_CARD, "button", ""},
    {TYPE_TEMPERATURE_CARD, "temperature", "updateTemperatureCard"},
    {TYPE_HUMIDITY_CARD, "humidity", "updateHumidityCard"},
    {TYPE_STATUS_CARD, "status", "updateStatusCard"},
    {TYPE_LINE_CARD, "line", "updateLineChart"},
    {TYPE_GAUGE_CARD, "gauge", "updateGaugeChart"},
    {TYPE_SLIDER_CARD, "slider", "updateSliderCard"}
};

// this is where websocket calls goes
AsyncWebSocket ws("/dashws");

void ESPDashV2::init(AsyncWebServer& server)
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        // respond with the compressed frontend
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", DASH_HTML, DASH_HTML_SIZE);
        response->addHeader("Content-Encoding","gzip");
        request->send(response);        
    });

    server.on("/debug", HTTP_GET, [&](AsyncWebServerRequest *request)
    {
        request->send(200, "application/json", UpdateLayout());
    });

    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.begin();
}

void ESPDashV2::onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    // json stuff remains on the stack
    StaticJsonDocument<200> json;
    String response;

    if(type == WS_EVT_DATA)
    {
        //data packet
        AwsFrameInfo * info = (AwsFrameInfo*)arg;
        if(info->final && info->index == 0 && info->len == len)
        {
            if(info->opcode == WS_TEXT)
            {
                data[len] = 0;
                deserializeJson(json, reinterpret_cast<const char *>(data));

                // client side commands parsing
                if(json["command"] == "getLayout")
                    response = ESPDash.UpdateLayout();
                else if(json["command"] == "ping")
                    response = "{\"response\":\"pong\"}";
                else if(json["command"] == "getStats")
                    response = ESPDash.UpdateLayout(true);
                else if(json["command"] == "buttonClicked")
                {
                }
                else if(json["command"] == "sliderChanged")
                {
                }
                else if(json["command"] == "reboot")
                {
                    response = "{\"response\":\"reboot\", \"done\":"+String(ESPDash.stats_enabled?"true":"false")+"}";
                    ws.text(client->id(), response);

                    // TODO: does it work on ESP32?
                    ESP.restart();
                    for(;;);
                }

                ws.text(client->id(), response);
            }
        }
    }
}

// add a new card to the collection
int ESPDashV2::AddCard(const int type, const char *name, int datatype)
{
    CardData card;

    card.id = cData.Size();
    card.type = type;
    card.datatype = datatype;
    card.value_i = 0;
    card.value_type = CardData::INTEGER;    // defaults to integer, but can be changed later

    strncpy(card.name, name, sizeof(card.name));

    // push the card into the array
    cData.PushBack(card);

    return cData.Size()-1;
}

// overload funtion for integer value update
void ESPDashV2::UpdateCard(const int cardID, int value)
{
    cData[cardID].value_type = CardData::INTEGER;
    cData[cardID].value_i = value;
}

// overload function for float value update
void ESPDashV2::UpdateCard(const int cardID, float value)
{
    cData[cardID].value_type = CardData::FLOAT;
    cData[cardID].value_f = value;
}

// push updates to all connected clients
void ESPDashV2::SendUpdates()
{
    String data;

    for(int i = 0; i < cData.Size(); i++)
    {
        // convert from ID to method
        const char *func = cNames[cData[i].type].json_method;

        data ="{\"id\":"+String(cData[i].id)+",";
        data+="\"response\":\""+String(func)+"\",";

        if(cData[i].value_type == CardData::INTEGER)
            data+="\"value\":\""+String(cData[i].value_i)+"\"}";
        else if(cData[i].value_type == CardData::FLOAT)
            data+="\"value\":\""+String(cData[i].value_f, 2)+"\"}";

        // no need to make buffer, just send it right away
        ws.textAll(data.c_str());
    }
}

// generates the layout JSON string to the frontend
String ESPDashV2::UpdateLayout(bool only_stats)
{
    String data;
    String stats;

    if(ESPDash.stats_enabled)
    {
        // No need to use json library to build response packet
        stats+="\"enabled\":\"true\",";
        stats+="\"hardware\":\""+ESP.getCoreVersion()+"\",";
        stats+="\"chipId\":\""+String(ESP.getChipId())+"\",";
        stats+="\"sketchHash\":\""+ESP.getSketchMD5()+"\",";
        stats+="\"macAddress\":\""+WiFi.macAddress()+"\",";
        stats+="\"freeHeap\":\""+String(ESP.getFreeHeap())+"\",";
        stats+="\"wifiMode\":"+String(WiFi.getMode());
    }
    else
        stats="\"enabled\":\"false\",";

    // only status has been requested
    if(only_stats)
    {
        return "{\"response\":\"getStats\", "
               "\"statistics\":{"+stats+"}}";
    }

    for(int i = 0; i < cData.Size(); i++)
    {
        // convert from ID to type
        const char *cardtype = cNames[cData[i].type].name;

        data+="{\"id\":\""+String(cData[i].id)+"\",";
        data+="\"card_type\":\""+String(cardtype)+"\",";
        data+="\"name\":\""+String(cData[i].name)+"\",";
        data+="\"datatype\":\""+String(cData[i].datatype)+"\",";
        data+="\"type\":\""+String(cData[i].type)+"\",";

        if(cData[i].value_type == CardData::INTEGER)
            data+="\"value\":\""+String(cData[i].value_i)+"\"}";
        else if(cData[i].value_type == CardData::FLOAT)
            data+="\"value\":\""+String(cData[i].value_f, 2)+"\"}";

        if(i<cData.Size()-1)
            data+=",";
    }

    return "{\"response\":\"getLayout\", "
           "\"version\": \"1\", "
           "\"statistics\":{"+stats+"}, "
           "\"cards\":["+data+"]}";
}

ESPDashV2 ESPDash;
