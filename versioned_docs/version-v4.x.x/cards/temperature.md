---
title: Temperature Card
sidebar_label: Temperature
sidebar_position: 2
---

<img className="card-preview" src="/img/v4/temperature-card.png" width="280px" alt="Preview" />

<br/>
<br/>

This card adds a distinctive temperature icon, and just like generic card you can add a symbol which will be appended to your data.


### Type
`TEMPERATURE_CARD`

### Data Types
- `int`
- `float`
- `String`

### Initializer
```cpp
/* 
  Temperature Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional) )
*/
Card card1(&dashboard, TEMPERATURE_CARD, "Temperature1", "°C");
```

### Callback

:::note
*Temperature card doesn't require any callback.*
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
card1.update(value, "°F");
```

### Reference
This is a reference sketch showing positions for intializer, callback and updater.


<!-- A complete dummy sketch showing positions for intializer and updater -->
```cpp

...

/* Temperature Card Initializer */
Card temperature(&dashboard, TEMPERATURE_CARD, "Temperature1");


void setup() {
  ...

  /* Temperature card updater - can be used anywhere (apart from global scope) */
  temperature.update(100);
}

void loop() {
  ...
}

```