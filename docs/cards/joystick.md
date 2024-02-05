---
title: Joystick Card
sidebar_label: Joystick (Pro)
sidebar_position: 16
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

<img className="card-preview" src="/img/v4/joystick-card.png" width="280px" alt="Preview" />

<br/>
<br/>

This card adds a joystick to your dashboard to control some stuff and provides you with easy to interpret directional data via callback. You can even lock direction of the joystick to X or Y axis.

### Initializer

```cpp
/* 
  Joystick Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* directionLock (optional) )
*/
Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1");
```

#### Direction Lock

You can lock joystick to X or Y Axis:

Supply it with `lockX` as 4th argument and it will lock to X axis.

```cpp
Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1", "lockX");
```

Supply it with `lockY` as 4th argument and it will lock to Y axis.
```cpp
Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1", "lockY");
```

By default, joystick works on both axis.

### Callback

Joystick Card requires a callback function which will be called when we receive a input from our dashboard. In setup block, we will be calling our `attachCallback` function and provide a lambda (callback) function with a `const char*` (character array) argument.

Joystick card has 2 callbacks, `directional` and `coordinates`:

#### Directional Callback

This callback will return the active direction of your joystick when it's moved. It will be one of the following:

- `up`
- `down`
- `left`
- `right`
- `idle`

```cpp
/*
  We provide our attachCallback with a lambda function to handle incomming data
  `value` is the direction of joystick 'up', 'down', 'left', 'right' or 'idle'
*/
joystick.attachCallback([&](const char* direction){
  Serial.println("[Joystick] Current Direction: "+String(direction));
});
```

##### Coordinates Callback

This callback will return the active coordinates of the thumb of your joystick when it's moved. It will provide x and y coordinates which ranges from `-60` to `60` on each axis.

In case of X axis: `-60` is left, `60` is right.
For Y axis: `-60` is up, and `60` is bottom.

```cpp
/*
  We provide our attachCallback with a lambda function to handle incomming data.
  In this case, we will be getting x and y axis coordinates in range of -60 to 60
*/
joystick.attachCallback([&](int8_t x, int8_t y){
  Serial.printf("[Joystick] X Axis: %d, Y Axis: %d\n", x, y);
});
```

### Updater

:::note
*Joystick card doesn't require any updater as value is not passed back to dashboard.*
:::

### Reference

This is a reference sketch showing positions for intializer and callback.

<!-- A complete dummy sketch showing positions for intializer and updater -->
```cpp

...

/* Joystick card initializer */
Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1");


void setup() {
  ...

  /* Joystick card directional callback */
  joystick.attachCallback([&](const char* direction){
    Serial.println("[Joystick] Current Direction: "+String(direction));
  });

  /* Joystick card coordinates callback */
  joystick.attachCallback([&](int8_t x, int8_t y){
    Serial.printf("[Joystick] X Axis: %d, Y Axis: %d\n", x, y);
  });
}

void loop() {
  ...
}

```
