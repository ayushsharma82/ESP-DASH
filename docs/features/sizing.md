---
title: Custom Card Size
sidebar_label: Custom Card Size (Pro)
sidebar_position: 5
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
            This feature is included only in DASH <span style={{ color: "#f54b42" }}>Pro</span>
        </h4>
        <a href="https://espdash.pro" target="_blank">Know more</a>
    </i>
</div>

<br/>


<img src="/img/v4/placeholder.png" width="500px" alt="Energy Card Preview" />
<br/>
<br/>

ESP-DASH Pro allows you to change the size of your cards & charts by providing you the `setSize` function. This function allows you to set a responsive width for your widgets without actually modifying the whole webpage.



### Reference

Card sizing consists of breakpoints for an responsive layout that scales up or down to every screen size. The valid value for each breakpoint is `1` to `12`.

To understand better, the breakpoints are as follows:
- `xs` - Small Smartphone
- `sm` - Normal Smartphone
- `md` - Tablet
- `lg` - HD laptop
- `xl` - Full HD laptop
- `xxl` - 2K display and above

##### Option 1:
```cpp
  // This reference can be found in Card.h
  void setSize(const uint8_t xs, const uint8_t sm, const uint8_t md, const uint8_t lg, const uint8_t xl, const uint8_t xxl);
```

##### Option 2:
```cpp
  // These references can be found in Card.h
  struct CardSize {
    uint8_t xs;
    uint8_t sm;
    uint8_t md;
    uint8_t lg;
    uint8_t xl;
    uint8_t xxl;
  };

  void setSize(const CardSize &size);
```

### Example

##### Option 1:
```cpp
card1.setSize(12, 12, 6, 4, 3, 2);
```

##### Option 2:
```cpp
card1.setSize({
  .xs = 12,
  .sm = 12,
  .md = 6,
  .lg = 4,
  .xl = 3,
  .xxl = 2
});
```
