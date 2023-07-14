---
title: Image Card
sidebar_label: Image (Pro)
sidebar_position: 9
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is available in <a target="_blank" style={{ color: "red" }} href="https://espdash.pro">DASH Pro</a> only.
        </h4>
         
    </i>
</div>


#### Preview:
<img class="card-preview" src="/img/v4/image-card.png" width="280px" alt="Preview" />

<br/>


<br/>

This card adds a image on your dashboard. You can pass a absolute URL to this card and it will load that image within this card on the dashboard. If the size is a bit small for you, then you can even make the card bigger by using the size value together with `setSize` function.

<br/>

#### Type:
`IMAGE_CARD`

<br/>

#### Valid Data Types:
- `String`

<br/>

#### Initializer:
```cpp
/* 
  Image Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* size )
*/
Card card1(&dashboard, IMAGE_CARD, "Test Image", "lg");
```

<br/>

#### Updaters:

After initialization, you will have to provide the URL of the image which you want to display.

```cpp
card1.update(const char* url);
```

Or you can also update the size of image using the second parameter. Supported sizes: "lg" and "xl"

```cpp
// This will change the selected value and update the choices as well
card1.update(const char* url, const char* size);
```

<br/>
<br/>
