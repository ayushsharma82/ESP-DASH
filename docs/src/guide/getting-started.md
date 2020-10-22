---
{
  "title": "ESP-DASH Wiki: Getting Started"
}
---
## Getting Started

To get started with ESP-DASH, we will be creating our [basic](https://github.com/ayushsharma82/ESP-DASH/tree/master/examples/Basic) example step by step and learn what each setup does:

<br>

#### Part 1: Include Dependencies
We have used conditional compilation in this part therefore the code will work for both ESP8266 & ESP32.
```cpp
#include <Arduino.h>
#if defined(ESP8266)
  /* ESP8266 Dependencies */
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#elif defined(ESP32)
  /* ESP32 Dependencies */
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#endif
#include <ESPDash.h>
```

<br>
<hr>
<br>


#### Part 2: Create AsyncWebServer Instance
```cpp
/* Start Webserver */
AsyncWebServer server(80);
```

<br>
<hr>
<br>

#### Part 3: Attach ESP-DASH Instance
```cpp
/* Attach ESP-DASH to AsyncWebServer */
ESPDash dashboard(&server); 
```

<br>
<hr>
<br>

#### Part 4: Create Cards
In this step, we will creating ESP-DASH cards and passing our dasboard instance as a first argument so that they can add / remove themselves.

*After we are done with this guide, Please take a look at [Card Class](/reference/card.html) reference to know more about the types of cards available to us.*
```cpp
/* 
  Dashboard Cards 
  Format - (Dashboard Instance, Card Type, Card Name, Card Symbol(optional) )
*/
Card temperature(&dashboard, TEMPERATURE_CARD, "Temperature", "°C");
Card humidity(&dashboard, HUMIDITY_CARD, "Humidity", "%");
```

<br>
<hr>
<br>

#### Part 5: Setup Block
In our setup block, we will be adding the usual WiFi connectivity stuff and then start our AsyncWebServer with `server.begin();`.
```cpp
void setup() {
  Serial.begin(115200);

  /* Connect WiFi */
  WiFi.mode(WIFI_STA);
  WiFi.begin("ssid", "password");
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  /* Start AsyncWebServer */
  server.begin();
}
```

<br>
<hr>
<br>


#### Part 5: Loop Block
In our loop block, we will be doing 2 things:
1. Updating card values
2. Sending updates to our dashboard

##### 1. Updating Card Values
Remember the 'Cards' we created in 4th part? We will now access those cards by their variable and update them using the `update` function which is provided with our card's class:
```cpp
temperature.update((int)random(0, 50));
```

##### 2. Sending updates to our Dashboard
Once we have updated values of our card(s), we will call the `sendUpdates()` function of our dashboard instance and it will send new card values to every connected client in real time.
```cpp
dashboard.sendUpdates();
```

*Technically speaking, You can call these functions anywhere in your sketch, but for demonstration purposes we have called them in our loop block.*

##### Complete Loop Block:

```cpp
void loop() {
  /* Update Card Values */
  temperature.update((int)random(0, 50));
  humidity.update((int)random(0, 100));

  /* Send Updates to our Dashboard (realtime) */
  dashboard.sendUpdates();

  /* 
    Delay is just for demonstration purposes in this example,
    Replace this code with 'millis interval' in your final project.
  */
  delay(3000);
}
```

<br>
<hr>
<br>

### Final Code
That's it! Now we can just upload this sketch to our MCU and access the dashboard via it's IP address. ( Make sure to change the `ssid` and `password` in our sketch according to your Access Point )

```cpp
/*
  -----------------------
  ESPDASH - Basic Example
  -----------------------

  Skill Level: Intermediate

  In this example we will be creating a basic dashboard which consists 
  of some cards and then update them in realtime ( at 3s interval ).

  Github: https://github.com/ayushsharma82/ESP-DASH
  WiKi: https://ayushsharma82.github.io/ESP-DASH/

  Works with both ESP8266 & ESP32
*/

#include <Arduino.h>
#if defined(ESP8266)
  /* ESP8266 Dependencies */
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#elif defined(ESP32)
  /* ESP32 Dependencies */
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#endif
#include <ESPDash.h>


/* Your WiFi Credentials */
const char* ssid = ""; // SSID
const char* password = ""; // Password

/* Start Webserver */
AsyncWebServer server(80);

/* Attach ESP-DASH to AsyncWebServer */
ESPDash dashboard(&server); 

/* 
  Dashboard Cards 
  Format - (Dashboard Instance, Card Type, Card Name, Card Symbol(optional) )
*/
Card temperature(&dashboard, TEMPERATURE_CARD, "Temperature", "°C");
Card humidity(&dashboard, HUMIDITY_CARD, "Humidity", "%");


void setup() {
  Serial.begin(115200);

  /* Connect WiFi */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  /* Start AsyncWebServer */
  server.begin();
}

void loop() {
  /* Update Card Values */
  temperature.update((int)random(0, 50));
  humidity.update((int)random(0, 100));

  /* Send Updates to our Dashboard (realtime) */
  dashboard.sendUpdates();

  /* 
    Delay is just for demonstration purposes in this example,
    Replace this code with 'millis interval' in your final project.
  */
  delay(3000);
}
```