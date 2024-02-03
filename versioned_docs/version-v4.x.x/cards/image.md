---
title: Image Card
sidebar_label: Image (Pro)
sidebar_position: 10
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::


#### Preview:
<img className="card-preview" src="/img/v4/image-card.png" width="280px" alt="Preview" />

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
