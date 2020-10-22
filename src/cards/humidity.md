---
{
  "title": "ESP-DASH Wiki: Humidity Card"
}
---
## Temperature Card

This card adds a distinctive humidity icon, and just like generic card you can add a symbol which will be appended to your data.

<br>

**Type:** 
`HUMIDITY_CARD`

<br>

**Valid Data Types:**
- `int`
- `float`
- `String`

<br>

**Initializer:**
```cpp
/* 
  Humidity Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* symbol (optional) )
*/
Card card1(&dashboard, HUMIDITY_CARD, "%");
```

<br>

**Updaters:**

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
card1.update(value, "RH");
```