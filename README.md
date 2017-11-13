# ESP-DASH

[![forthebadge](http://forthebadge.com/images/badges/uses-html.svg)](http://forthebadge.com)
[![forthebadge](http://forthebadge.com/images/badges/gluten-free.svg)](http://forthebadge.com)
[![forthebadge](http://forthebadge.com/images/badges/built-with-love.svg)](http://forthebadge.com)

![Dashboard](https://github.com/ayushsharma82/ESP-DASH/blob/master/docs/dashboard.PNG)

<br>
A Blazing Fast & Beautiful Library for creating a Functional Dashboard for your ESP8266.

<br>

ESP-DASH is a UI Library to create functional dashboards for your ESP8266. It provides essential functions like Wifi switcher, rebooting, and RAM usage. ESP-DASH uses ESP8266 arduino core for proper functioning and with dashboard page of size only 15Kb, It loads in just 1.30 seconds to your browser!. The best of all? it's a responsive design and adapts to your mobile screen size.

ESP-DASH is NOT dependent on Internet. All webpages are served from your ESP's SPIFFS Memory. Make Sure you have the Latest ESP8266 MKSPIFFS Installed : 
[Here](https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html#uploading-files-to-file-system)

## How to Install
###### Directly Through Arduino IDE ( Currently Submitted for Approval. Use Mannual Install till it gets Approved.)
Go to Sketch > Include Library > Library Manager > Search for "ESP-DASH" > Install

###### Mannual Install

For Windows: Download the [Repository](https://github.com/ayushsharma82/ESP-DASH/archive/master.zip) and extract the .zip in Documents>Arduino>Libraries>{Place "ESP-DASH" folder Here}

For Linux: Download the [Repository](https://github.com/ayushsharma82/ESP-DASH/archive/master.zip) and extract the .zip in Sketchbook>Libraries>{Place "ESP-DASH" folder Here}

###### Mannually through IDE

Download the [Repository](https://github.com/ayushsharma82/ESP-DASH/archive/master.zip), Go to Sketch>Include Library>Add .zip Library> Select the Downloaded .zip File.

## Dependancies
This Library is dependent on the following libraries to function properly.
  - [ESP8266 Core Library](https://github.com/esp8266/Arduino)
  - [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

Make Sure all dependencies are installed at their latest version to make this work.

## Getting Started

Step 1 and Step 2 only required for first time in each and every esp which uses ESP-DASH. Once UI is stored in SPIFFS you don't need to re-upload every time.

- Step1:  Download and install [ESP8266 SPIFFS Tool](http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html#uploading-files-to-file-system)
- Step2:  Now Connect your ESP8266 > Open Basic Example and then in Toolbar > Select Tools > ESP8266 Sketch Data Upload.

- Step3: Upload the Arduino Sketch to ESP8266.

- Step4: Restart ESP8266 and access your Dashboard at it's IP Address.

## User Tabs

ESP-DASH Gives users ability to add their own tabs on Dashboard! With a auto updating function which keeps your Dashboard Dynamically Updated at an Interval of 2 Seconds.

![UserTab](https://github.com/ayushsharma82/ESP-DASH/blob/master/docs/tab.gif)

Please give a glance at 'Basic' Example for understanding on how to frame code with ESP-DASH.

###### To Add a Tab on Dashboard:
```
EspDash.addTab("tabname", "tabvalue");
```

###### To Update a Tab on Dashboard:
```
EspDash.updateTab("tabname", "tabvalue");
```

Note: All 'Tab names' should be Unique! and updatetab function should have same tabname as specified in addtab for first time!


## API

###### EspDash.debug(true);
It will start printing out debug info for Wifi and Startup. For usage, Put this above EspDash.begin() in setup(). Default value is false for this function.

###### EspDash.begin(ssid, password);
Specify the Base Details for your ESP-DASH. On First Run, it will connect to this Access Point and after switching to someother wifi on dashboard, it will start connecting to that specific access point.

###### EspDash.addTab("tabname", "tabvalue");
This will add a user tab on your Dashboard. These tabs can be Updated! Remember: All tab names should be unique!

###### EspDash.updateTab("tabname", "tabvalue");
This will update the value in your Tab which you created earlier. In this case just use the Same name of Tab which you want to update.

###### EspDash.loop();
Drop this loop function in Sketch's void loop(); for proper functioning.

## A Special Thanks
[![forthebadge](http://forthebadge.com/images/badges/thats-how-they-get-you.svg)](http://forthebadge.com)
<br>
I would like to Thank the developers of the following Minimalistic Libraries which helped me in accomplishing a beautiful frontend for the ESP-DASH!

- [Framy CSS Framework](http://framycss.org/)
- [Zepto Javascript Framework](http://zeptojs.com/)
- [Notyf Notifications](http://carlosroso.com/notyf/)

## Contribute
Liked this Library? You can Contribute by adding your own Improvements in this Library or you may also share a :coffee:[Coffee](https://www.paypal.me/ayushsharma82/3) with me.
