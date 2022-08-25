---
title: Slider Card
sidebar_label: Slider
sidebar_position: 6
---

#### Preview:

<img src="/img/v4/placeholder.png" width="280px" alt="Preview" />

<br/>
<br/>

This card adds a interactive horizontal slider to your dashboard. Slider card is useful when you require a integer input within a certain range. ( Example use case: LED brightness control )

<br/>

#### Type: 
`SLIDER_CARD`

<br/>

#### Valid Data Types:
- `int`

<br/>

#### Initializer:
With slider card, Initializer requires `min` & `max` range.
```cpp
/* 
  Slider Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional), int min, int max)
*/
Card card1(&dashboard, SLIDER_CARD, "Test Slider", "", 0, 255);
```

<br/>

#### Callback:
Slider Card requires a callback function which will be called when we receive a input from our dashboard. We will be calling our `attachCallback` function and provide a lambda function with a `int` argument.

**Note:** You need to call the `update` function and `sendUpdates` immediately once you receive the value in callback. Otherwise user input will not be registered on dashboard.

```cpp
/*
  We provide our attachCallback with a lambda function to handle incomming data
  `value` is the boolean sent from your dashboard
*/
card1.attachCallback([&](int value){
  Serial.println("[Card1] Slider Callback Triggered: "+String(value));
  card1.update(value);
  dashboard.sendUpdates();
});
```

<br/>

#### Updaters:

```cpp
card1.update(int value);
```

Or, update symbol along your value:
```cpp
card1.update(244, "%");
```