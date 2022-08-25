---
title: Disable Statistics
sidebar_label: Disable Statistics
sidebar_position: 2
---


You can disable system statistics by using `false` as the second argument of ESPDash class constructor.

#### Example:

```cpp
ESPDash dashboard(&server, false);
```


If you would like to completely disable and hide the statistics tab from the sidebar, please use the above example and make sure you don't have any <i>custom statistics (pro)</i>. By doing so, it will automatically hide the "statistics" tab from sidebar.

