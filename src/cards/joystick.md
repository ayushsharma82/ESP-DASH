---
{
  "title": "ESP-DASH Wiki: Joystick Card"
}
---
<h2>Joystick - <small><span style="color: rgb(245, 75, 66)">Pro</span></small></h2>


#### Preview:
<br>

<img src="~@assets/joystick.gif" width="320px" alt="Preview">

<br>
<br>

<blockquote style="color: #000">
<h4>This feature is included in ESPDASH <span style="color: rgb(245, 75, 66)">Pro</span></h4> <a href="https://espdash.pro" target="_blank">Know more</a>
</blockquote>

<br>

This card adds a joystick to your dashboard to control some stuff and provides you with easy to interpret directional data via callback. You can even lock direction of the joystick to X or Y axis.

<br>

#### Type:
`JOYSTICK_CARD`

<br>

#### Initializer:
```cpp
/* 
  Joystick Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* directionLock (optional) )
*/
Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1");
```

<br>

#### Direction Lock:

You can lock joystick to X or Y Axis:

Supply it with `lockX` as 4th argument and it will lock to X axis.

```cpp
Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1", "lockX");
```
<br>

Supply it with `lockY` as 4th argument and it will lock to Y axis.
```cpp
Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1", "lockY");
```

By default, joystick works on both axis.




#### Callback:
Joystick Card requires a callback function which will be called when we receive a input from our dashboard. In setup block, we will be calling our `attachCallback` function and provide a lambda (callback) function with a `const char*` (character array) argument.

The callback will return the active direction of your joystick when it's moved. It will be one of the following:
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
