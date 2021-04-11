---
{
  "title": "ESP-DASH Wiki: Air Card"
}
---
<h2>Air Card - <small><span style="color: rgb(245, 75, 66)">Pro</span></small></h2>


#### Preview:
<br>

<img src="~@assets/air-card-1.png" width="280px" alt="Preview">
<img src="~@assets/air-card-2.png" width="280px" alt="Preview">

<br>
<br>

<blockquote style="color: #000">
<h4>This feature is included in ESPDASH <span style="color: rgb(245, 75, 66)">Pro</span></h4> <a href="https://espdash.pro" target="_blank">Know more</a>
</blockquote>

<br>

This card adds a distinctive air/wind icon, and just like generic card you can add a symbol which will be appended to your data. This card can be used to show something related to air pressure/wind speed etc.

<br>

#### Type:
`AIR_CARD`

<br>

#### Valid Data Types:
- `int`
- `float`
- `String`

<br>

#### Initializer:
```cpp
/* 
  Air Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional) )
*/
Card card1(&dashboard, AIR_CARD, "Power Consumption", "kWh");
```

<br>

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