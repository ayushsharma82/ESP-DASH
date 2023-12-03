---
title: Generic Card
sidebar_label: Generic
sidebar_position: 1
---

#### Preview:

<img className="card-preview" src="/img/v4/generic-card.png" width="280px" alt="Preview" />

<br/>
<br/>

Generic card is the 'fits-all-types' card, which you can use to display any kind of value. It's mostly used when you want to display numbers, strings etc which don't relate to any other card in the list.

<small>
<b>Note:</b> If you can't find the card which you are looking for, you can always raise request for more cards on the repository by creating an issue.
</small>

<br/>

#### Type: 
`GENERIC_CARD`

<br/>

#### Valid Data Types:
- `int`
- `bool`
- `float`
- `String`

<br/>

#### Initializer:
```cpp
/* 
  Generic Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional) )
*/
Card card1(&dashboard, GENERIC_CARD, "Generic1");
```

<br/>

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

<br/>

<br/>
