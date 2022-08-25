---
title: Custom Logo
sidebar_label: Custom Logo (Pro)
sidebar_position: 4
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


<img src="/img/v4/placeholder.png" width="400px" alt="Energy Card Preview" />
&nbsp;
<img src="/img/v4/placeholder.png" width="400px" alt="Energy Card Preview" />
<br/>
<br/>

If you are not familiar with the interface yet, the dashboard has an sidebar which can be expanded and collapsed by the user, in that case the logo switches between a "mini" version and a "full" version.

Both these logos can be changed by the user using a combination for compiler flags and class functions.


### Neccessary Compiler Flags

To set custom logos, first you need to add the following line at top of your sketch before you `#include` anything:

```cpp
#define USE_DASH_CUSTOM_LOGO 1
```

#### Optional Gzipped Flag:

By default ESP-DASH treats all logos to be gzipped. If you are supplying a logo which is not gzipped, you need to add another flag: <i>( by the way, it's not recommended to use a logo without gzipping it )</i>

```cpp
#define USE_DASH_LOGO_GZIPPED 0
```

This flag will disable the gzip header which is being sent along the response by default.



### Setting Custom Logo

After you have setup the neccessary compiler flags, it's time to add your custom logo to your code. The logo used in DASH is image file converted to byte array. We'll go through this below:

#### What you'll need
- You'll need a compatible logo image <i>( jpeg / png / gif / tif etc. )</i> or an SVG file ( recommended due to small file size ). <i><b>Important: Please make sure your image is optimized and small in file size.</b></i>
- Know the MIME file type of your image. You can use [HTTPStrip's mime utility](https://www.htmlstrip.com/mime-file-type-checker).

#### Procedure to convert logo into byte array
1. Go to [File2Raw utility](https://ayushsharma82.github.io/file2raw/) ( which I created a few years back for the purpose of converting files into byte array for C++ applications ).
2. Select your logo.
3. Select "Gzip Compress" & "Use PROGMEM (Arduino)".
4. Click "Convert".
5. Copy the generated response in your sketch & make sure this data is kept in global scope ( ie. outside setup or loop functions incase of Arduino IDE ).
6. Replace the `DATA` variable name with something else of your choice (ie. `LOGO`).

#### Setting custom logo in sketch

Now once your custom logo has been prepared, let's set it in our ESP-DASH dashboard instance. To do so, the dashboard provides you with 2 functions in which you will provide all the data which we prepared above.

```cpp
  void setLogo(uint8_t* logo, size_t logo_size, const char* mime, uint16_t width, uint16_t height);

  void setMiniLogo(uint8_t* logo, size_t logo_size, const char* mime, uint16_t width, uint16_t height);
```

- `logo` = byte array
- `logo_size` = size of your byte array
- `mime` = MIME file type of your logo
- `width` = width in pixels ( width of logo in the dashboard )
- `height` = height in pixels ( height of logo in the dashboard )

Examples:

```cpp
  dashboard.setLogo(LOGO, sizeof(LOGO), "image/png", 200, 40);
```

```cpp
  dashboard.setMiniLogo(MINI_LOGO, sizeof(MINI_LOGO), "image/png", 80, 40);
```