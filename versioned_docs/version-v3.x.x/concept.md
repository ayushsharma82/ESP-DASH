---
title: Concept of DASH
sidebar_label: Concept
sidebar_position: 2
---

The whole concept of ESP-DASH is around the idea of having 'Cards' and 'Charts' ( UI components ) on our dashboard. Therefore with V3, we divided the whole library into 3 separate classes:

1. **ESPDash** ( ESPDash.h )
2. **Card** ( Card.h )
3. **Chart** ( Chart.h )


<p align="center">
<img src="/img//concept-diagram.png" alt="Concept Diagram" width="400px" />
</p>


All of these classes serve their very own purpose and work harmoniously with a low heap footprint. Let's know more about the function of each class:

#### 1. ESPDash Class
ESPDash class handles the networking part of our dashboard. It takes AsyncWebServer as a argument and connects itself to serve DASH V3 webpage from our MCU's program memory. This class is responsible for the transfer of card/chart data between webpage and your sketch.

#### 2. Card Class
Our dashboard comprises of 'Cards' & 'Charts' and in our library, these are primarly data handling classes. Their main purpose is just to store data in their relevant position.

Card comprises of many sub-types ( for example: generic, temperature, humidity etc. ) which provides you great data visiualization choices.

#### 3. Chart Class
Similar to Card Class, Chart handles the data for creating charts on our dashboard.