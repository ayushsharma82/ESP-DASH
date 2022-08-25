---
title: Progress Card
sidebar_label: Progress
sidebar_position: 4
---

#### Preview:
<img src="/img/v4/placeholder.png" width="280px" alt="Preview" />

<br/>
<br/>

This card displays a horizontal range based on a `integer` or a `float` value. It makes data visualization user friendly.

<br/>

#### Type:
`PROGRESS_CARD`

<br/>

#### Valid Data Types:
- `int`
- `float`

<br/>

#### Initializer:
With progress card, Initializer requires `min` & `max` range.
```cpp
/* 
  Progress Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional), int min, int max)
*/
Card card1(&dashboard, PROGRESS_CARD, "Progress1", "", 0, 255);
```

<br/>

#### Updaters:

```cpp
card1.update(int value);
```

```cpp
card1.update(float value);
```

Or, update symbol along your value:
```cpp
card1.update(244, "%");
```