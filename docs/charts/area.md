---
title: Area Chart
sidebar_label: Area (Pro)
sidebar_position: 3
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
            This feature is included only in DASH <span style={{ color: "#f54b42" }}>Pro</span>
        </h4>
        <a href="https://espdash.pro" target="_blank">Know more</a>
    </i>
</div>

#### Preview:

<img src="/img/v4/placeholder.png" width="380px" alt="Preview" />

<br/>
<br/>

Similar to line chart, area chart fills the space below it with a color. You can aggregate large amount of data in form of arrays and display them in a area chart.


<br/>

#### Type: 
`AREA_CHART`

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
  Area Chart
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name )
*/
Chart chart1(&dashboard, AREA_CHART, "Chart Name");
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