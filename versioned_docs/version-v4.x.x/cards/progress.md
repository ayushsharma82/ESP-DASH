---
title: Progress Bar Card
sidebar_label: Progress Bar
sidebar_position: 4
---

#### Preview:
<img className="card-preview" src="/img/v4/progress-card.png" width="280px" alt="Preview" />

<br/>
<br/>

This card displays a horizontal progress bar based on a `integer` or a `float` value.

### Initializer

Initializer requires `min`, `max` of range you want to display.

```cpp
/* 
  Progress Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional), int min, int max)
*/
Card card1(&dashboard, PROGRESS_CARD, "Progress1", "", 0, 255);
```

### Callback

:::note
*Progress bar card doesn't require any callback.*
:::

### Updater

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

### Reference

This is a reference sketch showing positions for intializer and updater.

<!-- A complete dummy sketch showing positions for intializer and updater -->
```cpp

...

/* Progress card initializer */
Card progress(&dashboard, PROGRESS_CARD, "Progress1", "", 0, 255);


void setup() {
  ...

  /* Progress card updater - can be used anywhere (apart from global scope) */
  progress.update(100);
}

void loop() {
  ...
}

```
