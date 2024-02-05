---
title: Area Chart
sidebar_label: Area (Pro)
sidebar_position: 3
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

<img className="card-preview" src="/img/v4/area-chart.png" width="500px" alt="Preview" />

<br/>
<br/>

### Initializer

```cpp
/* 
  Area Chart
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name )
*/
Chart chart1(&dashboard, AREA_CHART, "Chart Name");
```

### Updater

Use the following functions to update the chart:

#### For X-Axis

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

#### X-Axis Data Types

- `int`
- `float`
- `String`
- `const char*`

---

#### For Y-Axis

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

#### Y-Axis Data Types

- `int`
- `float`

### Reference

This is a reference sketch showing positions for intializer and updater.

<!-- A complete dummy sketch showing positions for intializer and updater -->
```cpp

...

/* Area Chart initializer */
Chart area(&dashboard, AREA_CHART, "Chart Name");

/* XAxis & YAxis data in global scope */
int YAxis[] = {0, 0, 0, 0, 0, 0, 0};
String XAxis[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void setup() {
  ...

  /* Area chart x-axis updater - can be used anywhere (apart from global scope) */
  area.updateX(XAxis, 7); // Ideally only once in setup block

  /* Area chart y-axis updater - can be used anywhere (apart from global scope) */
  area.updateY(YAxis, 7);
}

void loop() {
  ...
}

```
