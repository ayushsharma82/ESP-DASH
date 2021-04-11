---
{
  "title": "ESP-DASH Wiki: Line Chart"
}
---
<h2>Line Chart  - <small><span style="color: rgb(245, 75, 66)">Pro</span></small></h2>


#### Preview:
<br>

<img src="~@assets/line-chart.png" width="380px" alt="Preview">

<br>
<br>

<blockquote style="color: #000">
<h4>This feature is included in ESPDASH <span style="color: rgb(245, 75, 66)">Pro</span></h4> <a href="https://espdash.pro" target="_blank">Know more</a>
</blockquote>

<br>

Second form of chart in ESP-DASH is the line chart. It lets you have linear data displayed in form of a connected line istead of bars. You can aggregate large amount of data in form of arrays and display them in a line chart.


<br>

#### Type: 
`LINE_CHART`

<br>

#### Valid Data Types for X-Axis:
- `int`
- `float`
- `String`

<br>

#### Valid Data Types for Y-Axis:
- `int`
- `float`

<br>

#### Initializer:
```cpp
/* 
  Line Chart
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name )
*/
Chart chart1(&dashboard, LINE_CHART, "Chart Name");
```

<br>

#### Updaters:

##### For X-Axis:
X-Axis updater uses `updateX` function.
```cpp
/*
  Data for X Axis of our Chart
  This array can be of: `int` / `float` or `String`
*/
String XAxis[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

/*
  Update Function for Chart is as follows:
  --------
  (int array[], size_t array_size)
  or
  (float array[], size_t array_size)
  or
  (String array[], size_t array_size)
*/
chart1.updateX(XAxis, 7);
```

##### For Y-Axis:
Y-Axis updater uses `updateY` function.
```cpp
/*
  Data for Y Axis of our Chart
  This array can be of: `int` or `float`
*/
int YAxis[] = {0, 0, 0, 0, 0, 0, 0};

/*
  Update Function for Chart is as follows:
  --------
  (int array[], size_t array_size)
  or 
  (float array[], size_t array_size)
*/
chart1.updateY(YAxis, 7);
```