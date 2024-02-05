---
title: Energy Card
sidebar_label: Energy (Pro)
sidebar_position: 9
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

<img className="card-preview" src="/img/v4/energy-card.png" width="280px" alt="Energy Card Preview" />

<br/>
<br/>

This card adds a distinctive energy/power icon, and just like generic card you can add a symbol which will be appended to your data. This card can be used to show something related to power consumption and usage etc.

### Initializer

```cpp
/* 
  Energy Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional) )
*/
Card card1(&dashboard, ENERGY_CARD, "Power Consumption", "kWh");
```

### Callback

:::note
*Energy card doesn't require any callback.*
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
card1.update(value, "kWh");
```

### Reference

This is a reference sketch showing positions for intializer and updater.

<!-- A complete dummy sketch showing positions for intializer and updater -->
```cpp

...

/* Energy card initializer */
Card energy(&dashboard, ENERGY_CARD, "Power Consumption", "kWh");


void setup() {
  ...

  /* Energy card updater - can be used anywhere (apart from global scope) */
  energy.update(100);
}

void loop() {
  ...
}

```
