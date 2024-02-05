---
title: Password Card
sidebar_label: Password (Pro)
sidebar_position: 12
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

#### Preview:

<img className="card-preview" src="/img/v4/text-input-card.png" width="280px" alt="Text Input Card Preview" />

<br/>
<br/>

Just like `Text Input` card, Password card gives you the ability to take String input from user in a *inconspicuous* way and save them in your application. 

This card is very useful for saving any kind of secret or password that requires the input value to be **not** visible on dashboard in plain text.

<br/>

#### Type:
`PASSWORD_CARD`

<br/>

#### Valid Data Types:
- `String`
- `char`

<br/>

#### Initializer:
```cpp
/* 
  Password Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name)
*/
Card card1(&dashboard, PASSWORD_CARD, "Test Pass");
```

<br/>


#### Callback:
Password card requires a callback function which will be called when we receive a input from our dashboard. In setup block, we will be calling our `attachCallback` function and provide a lambda (callback) function with a `const char*` (character array) argument.
```cpp
/*
  We provide our attachCallback with a lambda function to handle incomming data
*/
card1.attachCallback([&](const char* value){
  Serial.println("[Card1] Password Card Callback: "+String(value));
});
```

<br/>

#### Updaters:

*Password card doesn't require its value to be updated.*