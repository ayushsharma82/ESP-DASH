---
title: Temperature Card
sidebar_label: Temperature
sidebar_position: 2
---

#### Preview:

<img src="/img//temperature-card.png" width="280px" alt="Preview" />

<br/>
<br/>

This card adds a distinctive temperature icon, and just like generic card you can add a symbol which will be appended to your data.

<br/>

#### Type:
`TEMPERATURE_CARD`

<br/>

#### Valid Data Types:
- `int`
- `float`
- `String`

<br/>

#### Initializer:
```cpp
/* 
  Temperature Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional) )
*/
Card card1(&dashboard, TEMPERATURE_CARD, "Temperature1", "°C");
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
card1.update(value, "°F");
```

<br/>
<br/>
