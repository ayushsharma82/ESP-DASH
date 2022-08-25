---
title: Custom Title
sidebar_label: Custom Title (Pro)
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

<br/>

<img src="/img/v4/placeholder.png" width="500px" alt="Energy Card Preview" />
<br/>
<br/>

<a href="https://espdash.pro/" target="_blank">ESP-DASH <span style={{color: 'rgb(245, 75, 66)' }}>Pro</span></a> provides you with a <code>setTitle</code> function in the main ESPDash class. You can use this function to change the default title of your dashboard.


#### Example:

```cpp
dashboard.setTitle("New Dashboard XYZ");
```