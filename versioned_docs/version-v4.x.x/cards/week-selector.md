---
title: Week Selector Card
sidebar_label: Week Selector (Pro)
sidebar_position: 15
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

#### Preview:

<img className="card-preview" src="/img/v4/week-selector.png" width="280px" alt="Week Selector Card Preview" />

<br/>
<br/>

Week selector card gives you a nice card in which days are selectable by users. This type of card is very useful in many scenarios. The output of the card is comma `,` separated string on days which were selected by the user.

<br/>

#### Type:
`WEEK_SELECTOR_CARD`

<br/>

#### Valid Data Types:
- `String`
- `char`

<br/>

#### Initializer:
```cpp
/* 
  Week Selector Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name)
*/
Card card1(&dashboard, WEEK_SELECTOR_CARD, "Select Days");
```

<br/>


#### Callback:
Week selector card requires a callback function which will be called when we receive a input from our dashboard. In our setup block, we will be calling our `attachCallback` function and provide a lambda (callback) function with a `const char*` (character array) argument. Whenever a user selects a day, this callback will be triggered with a comma `,` separated list of days which indicate what was selected by user.

**Note:** You need to call the `update` function and `sendUpdates` immediately once you receive the value in callback. Otherwise user input will not be registered on dashboard and it will keep the card stuck in 'waiting' phase.

```cpp
/*
  We provide our attachCallback with a lambda function to handle incomming data
  Example Value: mon,tue,wed,thu,fri,sat,sun
*/
card1.attachCallback([&](const char* days){
  Serial.println("[Card1] Week Selector Triggered: "+String(days));
  card1.update(value);
  dashboard.sendUpdates();
});
```

<br/>

#### Updaters:
You can also select or deselect values depending on your logic. You just need to supply the updater with a comma `,` separated list of days. Order of days in this string doesn't matter. Example: Supplying `tue,mon,thu` will show `Monday, Tuesday & Thursday` as selected on Week Selector Card.

```cpp
card1.update(const char* value);
```

```cpp
card1.update(String value);
```

