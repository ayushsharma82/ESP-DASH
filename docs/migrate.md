---
title: Migration Guide
sidebar_label: Migration Guide
sidebar_position: 12
---

**Note: If you are currently using ESP-DASH V3 or ESP-DASH Pro ( previous releases <= v4.0.8 ), then this article is for you.**

This article will cover all the minor and breaking changing which come as part of switching your existing codebase to ESP-DASH V4. DASH V4 was made with backwards compatibility in mind therefore there are not many changes to the existing functionality, which means you can get started using it in a few minutes!:



## Minor Changes:


- The second argument of ESPDash Class constructor now only disables system statistics. `ESPDash(AsyncWebServer* server, bool enable_default_stats = true);`. The statistics tab now gets automatically hidden when there are no custom stats added by user and when default (system) statistics are disabled as well.

- The `sendUpdates(bool force);` function now has a `force` argument which can be used to force refresh the whole layout on connected dashboards.


## Breaking Changes:

### Button Callback:
The button callback now gets called with a `int` rather than `bool` which lead to issues. The value returned by callback will be `1` or `0`.

```cpp
// New Button Callback
button.attachCallback([&](int value){
  button.update(value);
  dashboard.sendUpdates();
});
```


### Charts:

There is a major overhaul inside the library for the charts functionality to improve reliability of host microcontroller.

*Previously, ESP-DASH would copy the whole X & Y axis array into SRAM of your ESP8266/ESP32 microcontroller, which was fine for smaller arrays but quickly led to crashes whenever somebody tried to use a large dataset.*

With V4, the library only keeps the pointer to the dataset which will be used for the charts. This in return lets you use a large array for charts without memory hogging the microcontroller! :D

As part of this critical fix, now you need to keep the dataset ( X & Y axis ) arrays into the global scope all the time and then provide a reference of these array to the library along with it's size. The only thing which you need to change is that if you were creating a array into heap, ( i.e inside a function ) now you need to shift it into global scope. Carefully study the following reference: [Benchmark Example](https://github.com/ayushsharma82/ESP-DASH/blob/master/examples/Benchmark/Benchmark.ino#L56)



