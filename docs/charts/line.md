---
title: Line Chart
sidebar_label: Line (Pro)
sidebar_position: 2
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is available in <a target="_blank" style={{ color: "red" }} href="https://espdash.pro">DASH Pro</a> only.
        </h4>
         
    </i>
</div>

#### Preview:

<img class="card-preview" src="/img/v4/line-chart.png" width="500px" alt="Preview" />

<br/>
<br/>
<br/>

#### Type: 
`LINE_CHART`

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
  Line Chart
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name )
*/
Chart chart1(&dashboard, LINE_CHART, "Chart Name");
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