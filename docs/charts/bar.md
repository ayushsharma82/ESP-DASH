---
title: Bar Chart
sidebar_label: Bar
sidebar_position: 1
---


#### Preview:

<img class="card-preview" src="/img/v4/bar-chart.png" width="500px" alt="Preview" />

<br/>
<br/>

#### Type: 
`BAR_CHART`

<br/>

#### Valid Data Types for X-Axis:
- `int`
- `float`
- `String`
- `const char*`

<br/>

#### Valid Data Types for Y-Axis:
- `int`
- `float`

<br/>

#### Initializer:
```cpp
/* 
  Bar Chart
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name )
*/
Chart chart1(&dashboard, BAR_CHART, "Chart Name");
```

<br/>

#### Updaters:

##### For X-Axis:
X-Axis updater uses `updateX` function.
```cpp
/*
  Data for X Axis of our Chart
  This array can be of: `int` / `float` or `String`
    
  Note: this array should be kept in global scope. i.e. it should never be deleted from memory.
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
  or
  (const char* array[], size_t array_size)
*/
chart1.updateX(XAxis, 7);
```

##### For Y-Axis:
Y-Axis updater uses `updateY` function.
```cpp
/*
  Data for Y Axis of our Chart
  This array can be of: `int` or `float`
    
  Note: this array should be kept in global scope. i.e. it should never be deleted from memory.
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