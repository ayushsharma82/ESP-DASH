---
title: Toggle Animation
sidebar_label: Toggle Animation (Pro)
sidebar_position: 3
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is available in <a target="_blank" style={{ color: "red" }} href="https://espdash.pro">DASH Pro</a> only.
        </h4>
         
    </i>
</div>

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