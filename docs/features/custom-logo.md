---
title: Custom Logo
sidebar_label: Custom Logo (Pro)
sidebar_position: 4
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is available in <a target="_blank" style={{ color: "red" }} href="https://espdash.pro">DASH Pro</a> only.
        </h4>
         
    </i>
</div>

<br/>


<img src="/img/v4/custom-logo-mini.png" width="305px" alt="Energy Card Preview" />
&nbsp;
<img src="/img/v4/custom-logo-large.png" width="400px" alt="Energy Card Preview" />
<br/>
<br/>

If you are not familiar with the interface yet, the dashboard has an sidebar which can be expanded and collapsed, in that case the logo switches between "mini" and "large" scale version.

Both these logos can be changed by the user by modifying the `logo.h` & `logo.cpp` file in the library source directory.


### Setting Custom Logo

The logo used in DASH is image file converted to byte array. We'll go through the process below:

#### What you'll need
- You'll need a compatible logo image <i>( jpeg / png / gif / tif etc. )</i> or an SVG file ( recommended due to small file size ). <i><b>Important: Please make sure your image is optimized and small in file size.</b></i>
- Know the MIME file type of your image. You can use [HTTPStrip's mime utility](https://www.htmlstrip.com/mime-file-type-checker).

#### Step 1: Procedure to convert logo into byte array
1. Go to [File2Raw Utility](https://file2raw.labrat.one/) ( I created this utility a few years back for the purpose of converting files into byte array for C++ applications ).
2. Select your logo.
3. Select "Gzip Compress" & "Use PROGMEM (Arduino)".
4. Click "Convert".

#### Step 2: Setting custom logo in sketch

Now once your custom logo has been prepared, let's set it in our ESP-DASH Pro library. To do so, the library contains 2 files which contain the variable that govern 'mini' and 'large' logos used by our webpage.

1. Go to `logo.h`
2. Set `DASH_MINI_LOGO_MIME` to your image file type. To find your file's mime type, use this utility: https://www.htmlstrip.com/mime-file-type-checker
3. Set `DASH_MINI_LOGO_WIDTH` & `DASH_MINI_LOGO_HEIGHT` according to your desired size which will be displayed on the webpage.
4. Replace the array length of `DASH_MINI_LOGO` with the newly generated array length.
5. Now open `logo.cpp`
6. Replace the data inside `DASH_MINI_LOGO` with new data generated just before using File2Raw.

Once done, you may repeat the same steps as above for `DASH_LARGE_LOGO`.
