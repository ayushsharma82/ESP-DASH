---
title: Air Card
sidebar_label: Air (Pro)
sidebar_position: 8
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::


#### Preview:
<img className="card-preview" src="/img/v4/air-card.png" width="280px" alt="Preview" />

<br/>


<br/>

This card adds a distinctive air/wind icon, and just like generic card you can add a symbol which will be appended to your data. This card can be used to show something related to air pressure/wind speed etc.

<br/>

#### Type:
`AIR_CARD`

<br/>

#### Valid Data Types:
- `int`
- `float`
- `String`

<br/>

#### Initializer:
```cpp
/* 
  Air Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional) )
*/
Card card1(&dashboard, AIR_CARD, "Power Consumption", "kWh");
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
