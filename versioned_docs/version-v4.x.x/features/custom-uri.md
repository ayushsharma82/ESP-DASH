---
title: Custom URI
sidebar_label: Custom URI
sidebar_position: 0
---


If you want to serve ESPDash at a path other than 'root' (ie. `http://<Your IP>/`) then you can use the constructor to supply the path of your choice.

#### Example:

```cpp
ESPDash dashboard(&server, "/dash");
```
This will result in ESPDash being served at `http://<Your IP>/dash`.