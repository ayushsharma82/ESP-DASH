---
title: Card Indexing
sidebar_label: Card Indexing (Pro)
sidebar_position: 6
---

<div style={{ border: '1px solid rgba(255,0,0, 0.03)', padding: 20, borderRadius: 14, backgroundColor: 'rgba(255,0,0, 0.03)', maxWidth: 600 }}>
  <h4 style={{ fontWeight: '500', marginBottom: 5 }}>This feature is included only in DASH <span style={{ color: "#f54b42" }}>Pro</span></h4> <a href="https://espdash.pro" target="_blank">Know more</a>
</div>

<br/>


<img src="/img//index.png" width="300px" alt="Energy Card Preview" />
<br/>
<br/>

ESP-DASH <span style={{color: 'rgb(245, 75, 66)' }}>Pro</span> provides you with a `setIndex` function in both cards and charts to modify the position of them on the dashboard. 


#### Example:

```cpp
card1.setIndex(0);
```


Indexing works in ascending format. The lowest card index will be placed in the front of the list and the highest index will be put in the end. It allows you to set the layout according to your wish.
