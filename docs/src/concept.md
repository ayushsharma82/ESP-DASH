---
{
  "title": "ESP-DASH Wiki: Concept"
}
---
## Concept

The whole concept of ESP-DASH is around the idea of having 'Cards' and 'Charts' ( UI components ) on our dashboard. Therefore with V3, we divided the whole library into 3 separate classes:

1. **ESPDash** ( ESPDash.h )
2. **Card** ( Card.h )
3. **Chart** ( Chart.h )


<p align="center">
<img src="~@assets/concept-diagram.png" alt="Concept Diagram" width="400px">
</p>


All of these classes serve their very own purpose and work harmoniously with a low heap footprint. Let's know more about the function of each class:

#### 1. ESPDash Class ([Reference](/reference/espdash.html))
ESPDash class handles the networking part of our dashboard. It takes AsyncWebServer as a argument and connects itself to serve DASH V3 webpage from our MCU's program memory. This class is responsible for the transfer of card/chart data between webpage and your sketch.

#### 2. Card Class ([Reference](/reference/card.html))
Our dashboard comprises of 'Cards' & 'Charts' and in our library, these are primarly data handling classes. Their main purpose is just to store data in their relevant position.

Card comprises of many sub-types ( for example: generic, temperature, humidity etc. ) which provides you with a great diversity of data visiualization choices.

#### 3. Chart Class ([Reference](/reference/chart.html))
Similar to Card Class, Chart handles the data for creating charts on our dashboard.