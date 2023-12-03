---
title: Push Button Card
sidebar_label: Push Button (Pro)
sidebar_position: 5
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is available in <a target="_blank" style={{ color: "red" }} href="https://espdash.pro">DASH Pro</a> only.
        </h4>
         
    </i>
</div>

#### Preview:

<img className="card-preview" src="/img/v4/push-button.png" width="280px" alt="Push Button Card Preview" />

<br/>
<br/>

Push button card adds a static button on your dashboard which has no state. Whenever a user clicks this button, it triggers a callback.

<br/>

#### Type:
`PUSH_BUTTON_CARD`

<br/>

#### Initializer:
```cpp
/* 
  Button Card
  Valid Arguments: (ESPDash dashboard, Card Type, const char* name)
*/
Card card1(&dashboard, PUSH_BUTTON_CARD, "Push Button");
```

<br/>

#### Callback:
Push button card will trigger a callback on every click by user, there is no need to update or `sendUpdates` to dashboard because there is no state.

```cpp
/*
  We provide our attachCallback with a lambda function to handle trigger
*/
card1.attachCallback([&](){
  Serial.println("[Card1] Push Button Triggered");
});
```
<br/>
<br/>
