---
{
  "title": "ESP-DASH Wiki: Generic Card"
}
---
## Generic Card

If you can't find the type of card you are looking for, then generic card is what you should use in your project. It's a type of card which can be used in any scenario.

<br>

#### Type: 
`GENERIC_CARD`

<br>

#### Valid Data Types:
- `int`
- `bool`
- `float`
- `String`

<br>

#### Initializer:
```cpp
/* 
  Generic Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional) )
*/
Card card1(&dashboard, GENERIC_CARD, "Generic1");
```

<br>

#### Updaters:

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