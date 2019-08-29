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

// integral type to string pairs events
// ID, type, json_method call
CardNames cNames[] = {
    {TYPE_NUMBER_CARD, "number", "updateNumberCard"},
    {TYPE_BUTTON_CARD, "button", NULL},
    {TYPE_TEMPERATURE_CARD, "temperature", "updateTemperatureCard"},
    {TYPE_HUMIDITY_CARD, "humidity", "updateHumidityCard"},
    {TYPE_STATUS_CARD, "status", "updateStatusCard"},
    {TYPE_LINE_CARD, "lineChart", "updateLineChart"},
    {TYPE_GAUGE_CARD, "gaugeChart", "updateGaugeChart"},
    {TYPE_SLIDER_CARD, "slider", "updateSliderCard"}
};

// this is where websocket calls goes
AsyncWebSocket ws("/dashws");

ESPDashV3::ESPDashV3()
{

}

ESPDashV3::~ESPDashV3()
{
    // free heap memory before destructor
    for(int i=0; i<cData.Size(); i++)
        delete[] cData[i].name;
}

void ESPDashV3::webauth(const char *user, const char *pass)
{
    username = user;
    password = pass;
    basic_auth = true;
}

void ESPDashV3::init(AsyncWebServer& server)
{
    // lambda function to respond on http request
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request)
    {
        if(basic_auth)
        {
            if(!request->authenticate(username, password))
                return request->requestAuthentication("ESP-Dash V3");
        }

        // respond with the compressed frontend
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", DASH_HTML, DASH_HTML_SIZE);
        response->addHeader("Content-Encoding","gzip");
        request->send(response);        
    });

    ws.onEvent(onWsEvent);

    // setup websocket basic auth
    if(ESPDash.basic_auth)
       ws.setAuthentication(ESPDash.username, ESPDash.password);

    server.addHandler(&ws);
    server.begin();
}

void ESPDashV3::onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    // json stuff remains on the stack
    StaticJsonDocument<200> json;
    String response;

    if(type == WS_EVT_DATA)
    {
        //data packet
        AwsFrameInfo *info = (AwsFrameInfo*)arg;
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
                    // execute and reference card data struct to funtion
                    int id = json["id"];
                    if(id >= 0 && ESPDash.cData[id].value_ptr != NULL)
                        ESPDash.cData[id].value_ptr(&ESPDash.cData[id]);

                    return;
                }
                else if(json["command"] == "sliderChanged")
                {
                    // execute and reference card data struct to funtion
                    int id = json["id"];
                    int value = json["value"];
                    ESPDash.UpdateCard(id, value);                    
                    if(id >= 0 && ESPDash.cData[id].value_ptr != NULL)
                        ESPDash.cData[id].value_ptr(&ESPDash.cData[id]);

                    response = ESPDash.RefreshCards();
                }
                else if(json["command"] == "reboot")
                {
                    response = "{\"response\":\"reboot\", \"done\":"+String(ESPDash.stats_enabled?"true":"false")+"}";
                    ws.text(client->id(), response);

                    // Force a board reboot
                    WiFi.forceSleepBegin();
                    wdt_reset();
                    ESP.reset();
                    while(1)
                        wdt_reset();
                }

                // update only requested socket
                ws.text(client->id(), response);
            }
        }
    }
}

// add a new card to the collection
int ESPDashV3::AddCard(const int type, const char *name, int datatype)
{
    CardData card;
    int size;

    card.id = cData.Size();
    card.type = type;
    card.changed = true;
    card.datatype = datatype;
    card.value_s = NULL;
    card.value_type = CardData::STRING;    // defaults to STRING type, but changed later
    card.value_ptr = NULL;  // default to null function

    size = strlen(name)+1;
    card.name = new char[size];
    strncpy(card.name, name, size);

    // push the card into the array
    cData.PushBack(card);

    return cData.Size()-1;
}

// overload funtion for integer value update
void ESPDashV3::UpdateCard(const int cardID, int value)
{
    cData[cardID].value_type = CardData::INTEGER;
    if(cData[cardID].value_i != value)
        cData[cardID].changed = true;
    cData[cardID].value_i = value;
}

// overload function for float value update
void ESPDashV3::UpdateCard(const int cardID, float value)
{
    cData[cardID].value_type = CardData::FLOAT;
    if(cData[cardID].value_f != value)
        cData[cardID].changed = true;
    cData[cardID].value_f = value;
}

// overload function for string value update
void ESPDashV3::UpdateCard(const int cardID, String &value)
{
    int size = value.length();

    // only free old value if type not changed
    if(cData[cardID].value_type == CardData::STRING)
    {
        if(cData[cardID].value_s != NULL)
            delete[] cData[cardID].value_s;
    }

    // TODO: Make a check
    cData[cardID].changed = true;

    cData[cardID].value_type = CardData::STRING;
    cData[cardID].value_s = new char[size+1];

    strncpy(cData[cardID].value_s, value.c_str(), size);
}

void ESPDashV3::UpdateCard(const int cardID, void (*funptr)(CardData *))
{
    // card has a function attached to it
    cData[cardID].value_type = CardData::INTEGER;
    if(cData[cardID].value_ptr != funptr)
        cData[cardID].changed = true;
    cData[cardID].value_ptr = funptr;
}

// push updates to all connected clients
String ESPDashV3::RefreshCards(bool toAll)
{
    String data;
    bool insertComma = false;

    for(int i = 0; i < cData.Size(); i++)
    {
        // convert from ID to method
        const char *func = cNames[cData[i].type].json_method;

        // discard cards without event or no changes since last refresh
        if(func == NULL || !cData[i].changed)
            continue;

        // Insert comma if necessary
        if(insertComma)
            data+=",";
        insertComma = false;

        data+="{\"id\":"+String(cData[i].id)+",";
        data+="\"response\":\""+String(func)+"\",";
        data+="\"value\":\"";

        // only value
        switch(cData[i].value_type)
        {
            case CardData::INTEGER:
                data+=String(cData[i].value_i);
                break;
            case CardData::FLOAT:
                data+=String(cData[i].value_f, 2);
                break;
            case CardData::STRING:
                data+=cData[i].value_s;
                break;
            default:
                // blank value
                break;
        }

        data+="\"}";

        if(toAll)
            cData[i].changed = false;

        // Insert comma or schedule for next card
        if(i<cData.Size()-1 && cNames[cData[i+1].type].json_method && cData[i+1].changed)
            data+=",";
        else
            insertComma = true;
    }

    return "{\"response\":\"updateCards\", "
           "\"cards\":["+data+"]}";
}

// generates the layout JSON string to the frontend
String ESPDashV3::UpdateLayout(bool only_stats)
{
    String data;
    String stats;

    if(stats_enabled)
    {
        // No need to use json library to build response packet
        stats+="\"enabled\":true,";
        stats+="\"hardware\":\""+ESP.getCoreVersion()+"\",";
        stats+="\"chipId\":\""+String(ESP.getChipId())+"\",";
        stats+="\"sketchHash\":\""+ESP.getSketchMD5()+"\",";
        stats+="\"macAddress\":\""+WiFi.macAddress()+"\",";
        stats+="\"freeHeap\":\""+String(ESP.getFreeHeap())+"\",";
        stats+="\"wifiMode\":"+String(WiFi.getMode())+",";
        stats+="\"wifiSignal\":"+String(WiFi.RSSI());
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
        data+="\"value\":\"";

        switch(cData[i].value_type)
        {
            case CardData::INTEGER:
                data+=String(cData[i].value_i);
                break;
            case CardData::FLOAT:
                data+=String(cData[i].value_f, 2);
                break;
            case CardData::STRING:
                data+=cData[i].value_s;
                break;
            default:
                // blank value
                break;
        }

        data+="\"}";

        if(i<cData.Size()-1)
            data+=",";
    }

    return "{\"response\":\"getLayout\", "
           "\"version\": \"1\", "
           "\"statistics\":{"+stats+"}, "
           "\"cards\":["+data+"]}";
}

void ESPDashV3::SendUpdates()
{
    ws.textAll(RefreshCards(true));
}

ESPDashV3 ESPDash;
