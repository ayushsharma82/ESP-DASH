---
title: Generic Card
sidebar_label: Generic
sidebar_position: 1
---

<img className="card-preview" src="/img/v4/generic-card.png" width="280px" alt="Preview" />

<br/>
<br/>

Generic card is the 'fits-all-types' card, which you can use to display any kind of value. It's mostly used when you want to display numbers, strings etc which don't relate to any other card in the list.

### Type
`GENERIC_CARD`

### Data Types
- `int`
- `bool`
- `float`
- `String`

### Initializer
```cpp
/* 
  Generic Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional) )
*/
Card card1(&dashboard, GENERIC_CARD, "Generic1");
```

### Callback

:::note
*Generic card doesn't require any callback.*
:::

### Updater

```cpp
card1.update(int value);
```

```cpp
card1.update(bool value);
```

```cpp
card1.update(float value);
```

```cpp
card1.update(String value);
```

### Reference
This is a reference sketch showing positions for intializer, callback and updater.


<!-- A complete dummy sketch showing positions for intializer and updater -->
```cpp

...

/* Generic Card Initializer */
Card generic(&dashboard, GENERIC_CARD, "Generic1");


void setup() {
  ...

  /* Generic card updater - can be used anywhere (apart from global scope) */
  generic.update(100);
}

void loop() {
  ...
}

```
