---
title: Energy Card
sidebar_label: Energy (Pro)
sidebar_position: 9
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

#### Preview:

<img className="card-preview" src="/img/v4/energy-card.png" width="280px" alt="Energy Card Preview" />

<br/>
<br/>

This card adds a distinctive energy/power icon, and just like generic card you can add a symbol which will be appended to your data. This card can be used to show something related to power consumption and usage etc.

<br/>

#### Type:
`ENERGY_CARD`

<br/>

#### Valid Data Types:
- `int`
- `float`
- `String`

<br/>

#### Initializer:
```cpp
/* 
  Energy Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional) )
*/
Card card1(&dashboard, ENERGY_CARD, "Power Consumption", "kWh");
```

<br/>

#### Updaters:

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

<br/>

<br/>
