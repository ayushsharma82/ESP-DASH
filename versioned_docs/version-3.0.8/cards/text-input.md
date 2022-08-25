---
title: Text Input Card
sidebar_label: Text Input (Pro)
sidebar_position: 6
---

<div style={{ border: '1px solid rgba(255,0,0, 0.03)', padding: 20, borderRadius: 14, backgroundColor: 'rgba(255,0,0, 0.03)', maxWidth: 600 }}>
  <h4 style={{ fontWeight: '500', marginBottom: 5 }}>This feature is included only in DASH <span style={{ color: "#f54b42" }}>Pro</span></h4> <a href="https://espdash.pro" target="_blank">Know more</a>
</div>

#### Preview:

<img src="/img//text-input-card.png" width="280px" alt="Energy Card Preview" />

<br/>
<br/>

Text Input Card gives you the ability to take String input from user and save them in your application. It provides you with a input box on the dashboard where user can send back text to your application. 

This card is very useful for saving WiFi credentials, passwords and general information.

<br/>

#### Type:
`TEXT_INPUT_CARD`

<br/>

#### Valid Data Types:
- `String`

<br/>

#### Initializer:
```cpp
/* 
  Energy Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name)
*/
Card card1(&dashboard, TEXT_INPUT_CARD, "User Email");
```

<br/>


#### Callback:
Text Input Card requires a callback function which will be called when we receive a input from our dashboard. In setup block, we will be calling our `attachCallback` function and provide a lambda (callback) function with a `const char*` (character array) argument.

**Note:** You need to call the `update` function and `sendUpdates` immediately once you receive the value in callback. Otherwise user input will not be registered on dashboard and it will keep the card stuck in 'waiting' phase.

```cpp
/*
  We provide our attachCallback with a lambda function to handle incomming data
  `value` is the boolean sent from your dashboard
*/
card1.attachCallback([&](const char* value){
  Serial.println("[Card1] Text Input Callback Triggered: "+String(value));
  card1.update(value);
  dashboard.sendUpdates();
});
```

<br/>

#### Updaters:

```cpp
card1.update(const char* value);
```

```cpp
card1.update(String value);
```
