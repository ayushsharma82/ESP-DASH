---
title: Dropdown Card
sidebar_label: Dropdown (Pro)
sidebar_position: 13
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::


#### Preview:
<img className="card-preview" src="/img/v4/dropdown-card.png" width="280px" alt="Preview" />
 &nbsp; 
<img className="card-preview" src="/img/v4/dropdown-card-2.png" width="280px" alt="Preview" />

<br/>


<br/>

This card adds a dropdown selectable list on your dashboard. You can pass "," comma separated list as it's secondary value with unlimited number of choices.

<br/>

#### Type:
`DROPDOWN_CARD`

<br/>

#### Valid Data Types:
- `String`

<br/>

#### Initializer:
```cpp
/* 
  Dropdown Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* choices )
*/
Card card1(&dashboard, DROPDOWN_CARD, "Test Dropdown", "Option1,Option2,Option3,Option4");
```

<br/>

#### Callback:

The Dropdown Card requires a callback function that will be invoked when input is received from the dashboard. This function should utilize the `attachCallback` method and provide a lambda function with a `const char*` parameter.

**Note:** It's essential to immediately invoke the `update` function and `sendUpdates` after receiving a value in the callback. Failure to do so will result in the user's input not being registered on the dashboard.

```cpp
/*
  Here, we use a lambda function within attachCallback to handle incoming data.
  `value` represents the const char value sent from your dashboard which is equal to selected value.
*/
card1.attachCallback([&](const char* value){
  Serial.println("[Card1] Dropdown Callback Triggered: "+String(value));
  card1.update(value);
  dashboard.sendUpdates();
});
```

<br/>

#### Updaters:

This will change the selected value of our dropdown:

```cpp
card1.update(const char* value);
```

Or you can also update the choices along with the value like this:

```cpp
// This will change the selected value and update the choices as well
card1.update(const char* value, const char* choices);
```

<br/>
<br/>
