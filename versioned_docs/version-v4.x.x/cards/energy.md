---
title: Energy Card
sidebar_label: Energy (Pro)
sidebar_position: 4
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is available in <a target="_blank" style={{ color: "red" }} href="https://espdash.pro">DASH Pro</a> only.
        </h4>
         
    </i>
</div>

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
