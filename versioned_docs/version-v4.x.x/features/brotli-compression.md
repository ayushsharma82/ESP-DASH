---
title: Brotli Compression
sidebar_label: Brotli Compression (Pro)
sidebar_position: 6
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is available in <a target="_blank" style={{ color: "red" }} href="https://espdash.pro">DASH Pro</a> only.
        </h4>
         
    </i>
</div>

<br/>

<img className="card-preview" src="/img/v4/brotli-compression.png" width="280px" alt="Preview" />

<br/>
<br/>

With ESP-DASH Pro v4.3.0 or more, there is an option to enable Brotli compression to further reduce the size of webpage (dashboard) and provide you more space for your code. We've noticed 40% extra reduction in size over gzip compression (default).

The drawback *might be* that brotli is not supported by legacy browsers; If you know for sure that you will be using ESP-DASH on the latest browsers, then don't think twice on enabling brotli compression.  

*Note: Broti compression is disabled by default. You will have to manually edit a library file and enable it.*

#### How to enable:

You can switch to brotli compression by setting `DASH_USE_BROTLI_COMPRESSION` to `1` in `dash_webpage.h`.

1. Open `dash_webpage.h` in src directory of ESP-DASH Pro library.
2. Locate `DASH_USE_BROTLI_COMPRESSION`
3. Set it to `1`
4. That's it. Save, compile and upload again to your microcontroller.