---
title: Text Input Card
sidebar_label: Text Input (Pro)
sidebar_position: 11
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

<img className="card-preview" src="/img/v4/text-input-card.png" width="280px" alt="Text Input Card Preview" />

<br/>
<br/>

Text Input Card gives you the ability to take String input from user and save them in your application. It provides you with a input box on the dashboard where user can send back text to your application. 

This card is very useful for saving WiFi credentials, user ID and general information.

### Initializer

```cpp
/* 
  Text Input Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name)
*/
Card card1(&dashboard, TEXT_INPUT_CARD, "User Email");
```

### Callback

Text Input Card requires a callback function which will be called when we receive a input from our dashboard. In setup block, we will be calling our `attachCallback` function and provide a lambda (callback) function with a `const char*` (character array) argument.

**Note:** You need to call the `update` function and `sendUpdates` immediately once you receive the value in callback. Otherwise user input will not be registered on dashboard and it will keep the card stuck in 'waiting' phase.

```cpp
/*
  We provide our attachCallback with a lambda function to handle incomming data
*/
card1.attachCallback([&](const char* value){
  Serial.println("[Card1] Text Input Callback Triggered: "+String(value));
  card1.update(value);
  dashboard.sendUpdates();
});
```

### Updater

```cpp
card1.update(const char* value);
```

```cpp
card1.update(String value);
```

### Reference

This is a reference sketch showing positions for intializer, callback and updater.

<!-- A complete dummy sketch showing positions for intializer and updater -->
```cpp

...

/* Week selector card initializer */
Card text(&dashboard, TEXT_INPUT_CARD, "Test Email");


void setup() {
  ...

  /* Week selector card callback */
  text.attachCallback([&](const char* value){
    Serial.println("Text Input Callback Triggered: "+String(value));
    /* Week selector card updater - you need to update the button with latest value upon firing of callback */
    text.update(value);
    /* Send update to dashboard */
    dashboard.sendUpdates();
  });
}

void loop() {
  ...
}

```
