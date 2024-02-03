---
title: Card Indexing
sidebar_label: Card Indexing (Pro)
sidebar_position: 5
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

<br/>


<img src="/img/index.png" width="300px" alt="Energy Card Preview" />
<br/>
<br/>

ESP-DASH <span style={{color: 'rgb(245, 75, 66)' }}>Pro</span> provides you with a `setIndex` function in both cards and charts to modify the position of them on the dashboard. 


#### Example:

```cpp
card1.setIndex(0);
```


Indexing works in ascending format. The lowest card index will be placed in the front of the list and the highest index will be put in the end. It allows you to set the layout according to your wish.
