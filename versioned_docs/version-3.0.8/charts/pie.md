---
title: Pie Chart
sidebar_label: Pie (Pro)
sidebar_position: 4
---

<div style={{ border: '1px solid rgba(255,0,0, 0.03)', padding: 20, borderRadius: 14, backgroundColor: 'rgba(255,0,0, 0.03)', maxWidth: 600 }}>
  <h4 style={{ fontWeight: '500', marginBottom: 5 }}> This feature is available in <a target="_blank" style={{ color: "red" }} href="https://espdash.pro">DASH Pro</a> only.</h4>  
</div>

#### Preview:

<img src="/img//pie-chart.png" width="380px" alt="Preview" />

<br/>
<br/>

Pie chart is a circular chart used for displaying various data where you can represent your data in a circular form.


<br/>

#### Type: 
`PIE_CHART`

<br/>

#### Valid Data Types for X-Axis:
- `int`
- `float`
- `String`

<br/>

#### Valid Data Types for Y-Axis:
- `int`
- `float`

<br/>

#### Initializer:
```cpp
/* 
  Pie Chart
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name )
*/
Chart chart1(&dashboard, PIE_CHART, "Chart Name");
```

<br/>

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