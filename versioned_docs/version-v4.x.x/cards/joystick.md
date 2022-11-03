---
title: Joystick Card
sidebar_label: Joystick (Pro)
sidebar_position: 7
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is available in <a target="_blank" style={{ color: "red" }} href="https://espdash.pro">DASH Pro</a> only.
        </h4>
         
    </i>
</div>


#### Preview:

<img src="/img/v4/joystick-card.png" width="280px" alt="Preview" />

<br/>
<br/>

This card adds a joystick to your dashboard to control some stuff and provides you with easy to interpret directional data via callback. You can even lock direction of the joystick to X or Y axis.

<br/>

#### Type:
`JOYSTICK_CARD`

<br/>

#### Initializer:
```cpp
/* 
  Joystick Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* directionLock (optional) )
*/
Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1");
```

<br/>

#### Direction Lock:

You can lock joystick to X or Y Axis:

Supply it with `lockX` as 4th argument and it will lock to X axis.

```cpp
Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1", "lockX");
```
<br/>

Supply it with `lockY` as 4th argument and it will lock to Y axis.
```cpp
Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1", "lockY");
```

By default, joystick works on both axis.




#### Callback:
Joystick Card requires a callback function which will be called when we receive a input from our dashboard. In setup block, we will be calling our `attachCallback` function and provide a lambda (callback) function with a `const char*` (character array) argument.

Joystick card has 2 callbacks, `directional` and `coordinates`:

##### Directional Callback:

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


##### Coordinates Callback:

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

<br/>
<br/>
