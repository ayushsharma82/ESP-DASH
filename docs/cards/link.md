---
title: Link Card
sidebar_label: Link (Pro)
sidebar_position: 17
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

<img className="card-preview" src="/img/v4/text-input-card.png" width="280px" alt="Text Input Card Preview" />

<br/>
<br/>

Link card is particularly useful when you want to redirect user to a new page. This card accepts valid URL schemes as string which will be passed on to dashboard for user action.

### Initializer

```cpp
/* 
  Link Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name)
*/
Card linkcard(&dashboard, LINK_CARD, "Test Link");
```

### Callback

:::note
*Link card doesn't require any callback.*
:::

### Updater

After initialization, you will have to provide the URL which has to be opened when user clicks on the card. You can do this by calling the `update` function.

```cpp
linkcard.update(const char* url);
```

### Reference

This is a reference sketch showing positions for intializer and updater.


<!-- A complete dummy sketch showing positions for intializer, callback and updater -->
```cpp

...

/* Link card initializer */
Card linkcard(&dashboard, LINK_CARD, "Test Link");


void setup() {
  ...

  /* Link card updater - can be used anywhere (apart from global scope) */
  linkcard.update("https://espdash.pro");
}

void loop() {
  ...
}

```
