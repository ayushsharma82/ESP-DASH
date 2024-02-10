---
title: Status Card
sidebar_label: Status
sidebar_position: 5
---

<img className="card-preview" src="/img/v4/status-card-idle.png" width="280px" alt="Preview" />
<img className="card-preview" src="/img/v4/status-card-warning.png" width="280px" alt="Preview" />
<img className="card-preview" src="/img/v4/status-card-success.png" width="280px" alt="Preview" />
<img className="card-preview" src="/img/v4/status-card-danger.png" width="280px" alt="Preview" />

<br/>
<br/>

As it's name suggests, status card is used to display some kind of status on your dashboard. It can show 4 different kinds of status along with a short message.

### Valid Statuses

- `s` - Success (Green)
- `d` - Danger (Red)
- `w` - Warning (Yellow)
- `i` - Idle (Grey)

### Initializer

```cpp
/* 
  Status Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* status (optional) )
*/
Card card1(&dashboard, STATUS_CARD, "Test Status", "s");
```

### Callback

:::note
*Status card doesn't require any callback.*
:::

### Updater

Status card updater allows you to set a message:

```cpp
card1.update("message");
```

Or, message + status at the same time:

```cpp
card1.update("Message", "s");
```

### Reference

This is a reference sketch showing positions for intializer and updater.

<!-- A complete dummy sketch showing positions for intializer and updater -->
```cpp

...

/* Status card initializer */
Card status(&dashboard, STATUS_CARD, "Test Status", "s");


void setup() {
  ...

  /* Status card updater - can be used anywhere (apart from global scope) */
  status.update("Warning message", "w");
}

void loop() {
  ...
}

```
