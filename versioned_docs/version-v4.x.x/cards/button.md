---
title: Toggle Button
sidebar_label: Toggle Button
sidebar_position: 5
---

#### Preview:

<img className="card-preview" src="/img/v4/button-card-false.png" width="280px" alt="Button Card Preview" />
 &nbsp; 
<img className="card-preview" src="/img/v4/button-card-true.png" width="280px" alt="Button Card Preview" />

<br/>
<br/>

Button card adds a interactive toggle button to your dashboard. This provides you with a simple `1` or `0` input from your dashboard.

<br/>

#### Type:
`BUTTON_CARD`

<br/>

#### Valid Data Types:
- `int`

<br/>

#### Initializer:
```cpp
/* 
  Button Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name)
*/
Card card1(&dashboard, BUTTON_CARD, "Test Button");
```

<br/>

#### Callback:
Button card requires a callback function which will be executed when we receive a input from our dashboard. In this example, we will use the `attachCallback` function and provide a lambda function with a boolean argument.

In the case of button card, the value sent by your dashboard will be opposite of your current value. For Example: If your button is set to `0`, then clicking that button on dashboard will trigger this callback with `1`.

**Note:** You need to call the `update` function and `sendUpdates` immediately once you receive the value in callback. Otherwise user input will not be registered on dashboard.

```cpp
/*
  We provide our attachCallback with a lambda function to handle incomming data
  `value` is the boolean sent from your dashboard
*/
card1.attachCallback([&](int value){
  Serial.println("[Card1] Button Callback Triggered: "+String((value == 1)?"true":"false"));
  card1.update(value);
  dashboard.sendUpdates();
});
```

<br/>

#### Updaters:

```cpp
card1.update(1);
```

```cpp
card1.update(0);
```
<br/>
<br/>
