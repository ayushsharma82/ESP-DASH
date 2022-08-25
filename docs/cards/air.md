---
title: Air Card
sidebar_label: Air (Pro)
sidebar_position: 4
---

<div style={{ border: '1px solid rgba(255,0,0, 0.03)', padding: 20, borderRadius: 14, backgroundColor: 'rgba(255,0,0, 0.03)', maxWidth: 600 }}>
  <h4 style={{ fontWeight: '500', marginBottom: 5 }}>This feature is included only in DASH <span style={{ color: "#f54b42" }}>Pro</span></h4> <a href="https://espdash.pro" target="_blank">Know more</a>
</div>


#### Preview:
<img src="/img/v4/placeholder.png" width="280px" alt="Preview" />
<br/>
<img src="/img/v4/placeholder.png" width="280px" alt="Preview" />

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
