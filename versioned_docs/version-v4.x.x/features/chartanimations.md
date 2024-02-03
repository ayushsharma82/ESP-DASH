---
title: Toggle Animation
sidebar_label: Toggle Animation (Pro)
sidebar_position: 3
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

<br/>

You can enable/disable chart animations with ease using the `setChartAnimations` function of ESPDash class. This is particularly helpful if you are updating your charts at an very fast pace.

*Note: Chart animations are enabled by default.*

#### Usage:

You can put this function anywhere in your setup block:

##### To Disble:
```cpp
dashboard.setChartAnimations(false); // Disable Chart Animations
```

##### To Enable:
```cpp
dashboard.setChartAnimations(true); // Enable Chart Animations
```