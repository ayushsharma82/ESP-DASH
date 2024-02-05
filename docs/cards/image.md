---
title: Image Card
sidebar_label: Image (Pro)
sidebar_position: 10
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::


<img className="card-preview" src="/img/v4/image-card.png" width="280px" alt="Preview" />

<br/>
<br/>

This card adds a image on your dashboard. You can pass a absolute URL to this card and it will load that image within this card on the dashboard. If the size is a bit small for you, then you can even make the card bigger by using the size value together with `setSize` function.

### Initializer

```cpp
/* 
  Image Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* size )
*/
Card card1(&dashboard, IMAGE_CARD, "Test Image", "lg");
```

### Callback

:::note
*Image card doesn't require any callback.*
:::

### Updater

After initialization, you will have to provide the URL of the image which you want to display.

```cpp
card1.update(const char* url);
```

Or you can also update the size of image using the second parameter. Supported sizes: "lg" and "xl"

```cpp
// This will change the selected value and update the choices as well
card1.update(const char* url, const char* size);
```

### Reference

This is a reference sketch showing positions for intializer and updater.

<!-- A complete dummy sketch showing positions for intializer and updater -->
```cpp

...

/* Image card initializer */
Card image(&dashboard, IMAGE_CARD, "Test Image", "lg");


void setup() {
  ...

  /* Image card updater - can be used anywhere (apart from global scope) */
  image.update("https://fastly.picsum.photos/id/598/800/600.jpg?grayscale&hmac=SQ5T_OGiPMX4r1fb-gA2fU6pourJEfxmTz7g1HfXOSk");
}

void loop() {
  ...
}

```
