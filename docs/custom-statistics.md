---
title: Statistics
sidebar_label: Statistics
sidebar_position: 8
---

<img src="/img/v4/placeholder.png" alt="Concept Diagram" width="600px" />

<br/>
<br/>

ESP-DASH has a dedicated page called "Statistics" on the dashboard which contain key-value pairs of system statistics ( heap, flash usage etc. ) by default. With the launch of ESP-DASH V4, user defined statistics are now also part of the library! You can now add your own statitics to this page. 🎉

*Note: System statistics can be turned off any time, please look in [Disable Statistics](./features/disable-stats.md) tab for that.*


### Example

##### Initializer:
```cpp
Statistic stat1(&dashboard, "Statistic 1", "Value 1");
```

##### Update Value:
```cpp
stat1.set("Value 123");
```