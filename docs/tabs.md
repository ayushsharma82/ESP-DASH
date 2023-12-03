---
title: Tabs
sidebar_label: Tabs (Pro)
sidebar_position: 7
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is available in <a target="_blank" style={{ color: "red" }} href="https://espdash.pro">DASH Pro</a> only.
        </h4>
         
    </i>
</div>

<br/>
<br/>

<img src="/img/v4/tabs.png" alt="Concept Diagram" width="300px" />

<br/>
<br/>

Tabs in ESP-DASH allow you to create multiple pages to organize and sort your various cards & charts. This feature comes particularly useful when there are all a lot of widgets.

By default, ESP-DASH puts everything into 'Overview' Tab. If every card or chart is assigned a custom tab, then the dashboard will automatically hide the overview tab from sidebar.


### Example

##### Initializer:
Initializer should be kept in global scope. ( ie. outside of any function in your sketch )

```cpp
Tab tab1(&dashboard, "Custom Tab 1");
```

##### Set Tab:
Once a tab has been created, you need to set the tab for relevant cards and charts using `setTab` function of Card or Chart class. `setTab` accepts a pointer to the tab which we just created.

```cpp
card1.setTab(&tab1);
```

```cpp
chart1.setTab(&tab1);
```