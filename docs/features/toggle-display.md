---
title: Toggle Display
sidebar_label: Toggle Display (Pro)
sidebar_position: 2
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

<br/>

You can quickly show or hide widgets (cards, charts, tabs and statistics) using the `setDisplay` function. Use it to show or hide stuff on your dashboard when it's required. Possibilities are endless with this function and makes the dashboard truly customizable.

:::note
All widgets are displayed by default.
:::

#### Usage

You can put this function anywhere in your setup block:

##### To Hide Widget

```cpp
card1.setDisplay(false); // Hide your card

OR

chart1.setDisplay(false); // Hide your chart

OR

tab1.setDisplay(false); // Hide your tab

OR

stat1.setDisplay(false); // Hide your statistic
```

##### To Show Widget

```cpp
card1.setDisplay(true); // Show your card

OR

chart1.setDisplay(true); // Show your chart

OR

tab1.setDisplay(true); // Show your tab

OR

stat1.setDisplay(true); // Show your statistic
```
