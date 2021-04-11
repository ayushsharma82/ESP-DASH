---
{
  "title": "ESP-DASH Wiki: Button Card"
}
---
## Button Card


#### Preview:
<br>

<img src="~@assets/toggle-button-inactive.png" width="280px" alt="Button Card Preview">
<img src="~@assets/toggle-button-active.png" width="280px" alt="Button Card Preview">

<br>
<br>

This card adds a interactive toggle button to your dashboard. This provides you with a simple `true` or `false` input from your dashboard.

<br>

#### Type:
`BUTTON_CARD`

<br>

#### Valid Data Types:
- `bool`

<br>

#### Initializer:
```cpp
/* 
  Button Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name)
*/
Card card1(&dashboard, BUTTON_CARD, "Test Button");
```

<br>

#### Callback:
Button Card requires a callback function which will be called when we receive a input from our dashboard. We will be calling our `attachCallback` function and provide a lambda function with a boolean argument.

In the case of button card, the value sent by your dashboard will be opposite of your current value. For Example: If your button is set to `false`, then clicking that button on dashboard will trigger this callback with `true`.

**Note:** You need to call the `update` function and `sendUpdates` immediately once you receive the value in callback. Otherwise user input will not be registered on dashboard.

```cpp
/*
  We provide our attachCallback with a lambda function to handle incomming data
  `value` is the boolean sent from your dashboard
*/
card1.attachCallback([&](bool value){
  Serial.println("[Card1] Button Callback Triggered: "+String((value)?"true":"false"));
  card1.update(value);
  dashboard.sendUpdates();
});
```

<br>

#### Updaters:

```cpp
card1.update(true);
```

```cpp
card1.update(false);
```