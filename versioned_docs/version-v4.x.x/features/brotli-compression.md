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

Please note that Brotli compression is only supported by Safari browser with unencrpyted HTTP protocol. Due to constraints set by other browsers ( Chrome, Edge, Firefox etc. ) you need to use HTTPS for brotli compression to work properly.

*Note: Broti compression is disabled by default. It's up to user to enable brotli if the above conditions are fine for your use-case.*

#### How to enable:

You can switch to brotli compression by setting `DASH_USE_BROTLI_COMPRESSION` to `1` in `dash_webpage.h`.

1. Open `dash_webpage.h` in src directory of ESP-DASH Pro library.
2. Locate `DASH_USE_BROTLI_COMPRESSION`
3. Set it to `1`
4. That's it. Save, compile and upload again to your microcontroller.