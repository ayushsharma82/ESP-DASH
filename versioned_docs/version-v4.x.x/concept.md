---
title: Concept of DASH
sidebar_label: Concept
sidebar_position: 2
---

In this article, we are going to look at how the internals of ESP-DASH are stacked up, as well as understand the how everything works with eachother inside the library.

<i>Note: If you looking to get started with ESP-DASH quickly, you can skip this article.</i>

<br/>
<br/>

<img src="/img/v4/concept.svg" alt="Concept Diagram" width="800px" />

<br/>
<br/>

DASH contains the following classes which you will use in your application:

- <b>Networking Class</b> (ESPDash.h)
- <b>Card Class</b> (Card.h)
- <b>Chart Class</b> (Chart.h)
- <b>Statistic Class</b> (Statistic.h)
- <b>Tab Class</b> (Tab.h) ( Pro Version Only )

The whole idea of ESP-DASH is to make a complete dashboard by using data classes ( as shown in figure above ). The data classes connect with ESP-DASH main class using pointers which handles all the networking and relays realtime updates to the open dashboards.


Let's understand the purpose of each class:

#### 1. Networking Class (ESPDash.h)
The networking class handles all the networking stuff including serving the DASH webpage from program memory of the microcontroller and also to maintain the WebSocket connection with every connected client. Apart from networking, with the release of V4, you can now also configure the webpage according to your application. This includes changing page title, logo etc. ( Go to "Extra Features" to know more ).


#### 2. Card Class (Card.h)

The card class is a data storage class in ESP-DASH which is used to create various types of cards on the dashboard. The only purpose of this class is to store the data + configuration in stack or heap depending on your use case and to keep track of the changes in data for realtime updates.

#### 3. Chart Class (Chart.h)
The chart class is an data storage class which is used to store the X & Y axis arrays to create various types of charts on the dashboard. This class is a bit different from "card" class as to keep the memory footprint low, it doesn't stores the data in the class itself. Instead it smartly stores the pointer to arrays so that data can be read on demand without actually copying all the array in the memory.

<small>
<i>Note: If you are migrating from V3, Please look at the migration guide to know more.</i>
</small>

#### 4. Statistic Class (Statistic.h)
The statistic class is used to create custom user defined statistics which will be displayed in the statistics page. Statistics in ESP-DASH's sense are simple key-value pairs which you can send to dashboard to report small but useful data.


#### 5. Tab Class (Tab.h) ( Pro )
The tab class in <a href="https://espdash.pro/" target="_blank">DASH Pro</a> is also an data class which is used to create multiple pages. Therefore, you are now not limited to the "Overview" page and can create multiple pages to host different cards & charts.