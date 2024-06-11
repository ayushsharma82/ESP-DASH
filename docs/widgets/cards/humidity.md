---
title: Humidity Card
sidebar_label: Humidity
sidebar_position: 3
---

<img className="card-preview" src="/img/v4/humidity-card.png" width="280px" alt="Preview" />

<br/>
<br/>

This card adds a distinctive humidity icon, and just like generic card you can add a symbol which will be appended to your data.

### Initializer

```cpp
/* 
  Humidity Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional) )
*/
Card card1(&dashboard, HUMIDITY_CARD, "Humidity1", "%");
```

### Callback

:::note
*Humidity card doesn't require any callback.*
:::

### Updater

```cpp
card1.update(int value);
```

```cpp
card1.update(float value);
```

```cpp
card1.update(String value);
```

Or you can also update the symbol along with the value like this:

```cpp
card1.update(value, "RH");
```

### Reference

This is a reference sketch showing positions for intializer and updater.

<!-- A complete dummy sketch showing positions for intializer and updater -->
```cpp

...

/* Humidity card initializer */
Card humidity(&dashboard, HUMIDITY_CARD, "Humidity1");


void setup() {
  ...

  /* Humidity card updater - can be used anywhere (apart from global scope) */
  humidity.update(100);
}

void loop() {
  ...
}

```
