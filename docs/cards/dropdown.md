---
title: Dropdown Card
sidebar_label: Dropdown (Pro)
sidebar_position: 8
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is available in <a target="_blank" style={{ color: "red" }} href="https://espdash.pro">DASH Pro</a> only.
        </h4>
         
    </i>
</div>


#### Preview:
<img src="/img/v4/dropdown-card.png" width="280px" alt="Preview" />

<br/>


<br/>

This card adds a dropdown selectable list on your dashboard. You can pass "," comma separated list as it's secondary value with unlimited number of choices.

<br/>

#### Type:
`DROPDOWN_CARD`

<br/>

#### Valid Data Types:
- `String`

<br/>

#### Initializer:
```cpp
/* 
  Dropdown Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* choices )
*/
Card card1(&dashboard, DROPDOWN_CARD, "Test Dropdown", "Option1,Option2,Option3,Option4");
```

<br/>

#### Updaters:

This will change the selected value of our dropdown:

```cpp
card1.update(const char* value);
```

Or you can also update the choices along with the value like this:

```cpp
// This will change the selected value and update the choices as well
card1.update(const char* value, const char* choices);
```

<br/>
<br/>
