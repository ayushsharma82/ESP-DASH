---
title: Disable Statistics
sidebar_label: Disable Statistics
sidebar_position: 2
---


You can disable system statistics by using setting `false` in ESPDash class constructor.

#### Example:

#### If no custom URI is defined (second parameter):
```cpp
ESPDash dashboard(&server, false);
```

#### If using a using custom URI (third parameter):
```cpp
ESPDash dashbord(&server, "/", false);
```


If you would like to completely disable and hide the statistics tab from the sidebar, please use the above example and make sure you don't have any <i>custom statistics</i>. By doing so, it will automatically hide the "statistics" tab from sidebar.

