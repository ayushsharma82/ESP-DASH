---
{
  "title": "ESP-DASH Wiki: Pie Chart"
}
---
<h2>Pie Chart  - <small><span style="color: rgb(245, 75, 66)">Pro</span></small></h2>


#### Preview:
<br>

<img src="~@assets/pie-chart.png" width="380px" alt="Preview">

<br>
<br>

<blockquote style="color: #000">
<h4>This feature is included in ESPDASH <span style="color: rgb(245, 75, 66)">Pro</span></h4> <a href="https://espdash.pro" target="_blank">Know more</a>
</blockquote>

<br>

Pie chart is a circular chart used for displaying various data where you can represent your data in a circular form.


<br>

#### Type: 
`PIE_CHART`

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
  Pie Chart
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name )
*/
Chart chart1(&dashboard, PIE_CHART, "Chart Name");
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
String XAxis[] = {"Biscuits", "Cookies", "Milk", "Thing4", "Thing5"};

/*
  Update Function for Chart is as follows:
  --------
  (int array[], size_t array_size)
  or
  (float array[], size_t array_size)
  or
  (String array[], size_t array_size)
*/
chart1.updateX(XAxis, 5);
```

##### For Y-Axis:
Y-Axis updater uses `updateY` function.
```cpp
/*
  Data for Y Axis of our Chart
  This array can be of: `int` or `float`
*/
int YAxis[] = {0, 0, 0, 0, 0};

/*
  Update Function for Chart is as follows:
  --------
  (int array[], size_t array_size)
  or 
  (float array[], size_t array_size)
*/
chart1.updateY(YAxis, 5);
```