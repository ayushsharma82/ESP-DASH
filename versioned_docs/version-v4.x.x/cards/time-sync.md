---
title: Time Sync Card
sidebar_label: Time Sync (Pro)
sidebar_position: 18
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

<img className="card-preview" src="/img/v4/text-input-card.png" width="280px" alt="Text Input Card Preview" />

<br/>
<br/>

Use the time sync card to syncronize the time of your device with your MCU. This has various applications which require precise time keeping etc. 

:::tip
Time sync card grabs the time from your browser, so only use it when your device and MCU are known to be in the same geographical location/timezone.
:::

### Initializer

```cpp
/* 
  Time Sync Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name)
*/
Card timesync(&dashboard, TIME_SYNC_CARD, "Time Sync");
```

### Callback

```cpp
timesync.attachCallback([&](const char* value){
  Serial.println("Time Sync Triggered: "+String(value));
});
```

### Updater

:::note
*Time sync card doesn't require any updater.*
:::

### Reference

This is a reference sketch showing positions for intializer and callback.


<!-- A complete dummy sketch showing positions for intializer, callback and updater -->
```cpp

...

/* Time sync card initializer */
Card timesync(&dashboard, TIME_SYNC_CARD, "Time Sync");


void setup() {
  ...

  /* Time sync card callback */
  timesync.attachCallback([&](const char* value){
    Serial.println("Time Sync Triggered: "+String(value));
  });
}

void loop() {
  ...
}

```
