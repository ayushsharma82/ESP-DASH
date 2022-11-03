---
title: User Authentication
sidebar_label: User Authentication
sidebar_position: 1
---


<img src="/img/v4/authentication.png" width="500px" alt="Energy Card Preview" />
<br/>
<br/>

ESP-DASH comes with basic HTTP authentication support. You can enable basic HTTP based user authentication to control who can view your dashboard using `setAuthentication` function.


#### Example:

```cpp
dashboard.setAuthentication("username", "password");
```