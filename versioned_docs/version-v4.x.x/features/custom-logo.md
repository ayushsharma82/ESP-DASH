---
title: Custom Logo
sidebar_label: Custom Logo (Pro)
sidebar_position: 4
---

:::danger Pro Feature
This is an exclusive feature of DASH Pro. Check it out [here](https://espdash.pro).
:::

<br/>

<img src="/img/v4/custom-logo.png" width="305px" alt="Logo Preview" />
<br/>
<br/>

Your ESP-DASH dashboard's sidebar contains the spot which can be updated to add your own company/product logo. This enables you with complete customization and maintains your brand value among customers.

### Setting Logo

The logo used in ESP-DASH is image file converted to byte array. We'll go through the process below:

#### What you'll need

- You'll need a compatible logo image <i>( jpeg / png / gif / tif etc. )</i> or an SVG file ( recommended due to small file size ). <i><b>Important: Please make sure your image is optimized and small in file size.</b></i>
- Know the MIME file type of your image. You can use [HTTPStrip's mime utility](https://www.htmlstrip.com/mime-file-type-checker).

#### Step 1: Procedure to convert logo into byte array

1. Go to [File2Raw Utility](https://file2raw.labrat.one/) ( I created this utility a few years back for the purpose of converting files into byte array for C++ applications ).
2. Select your logo.
3. Select "Gzip Compress" & "Use PROGMEM (Arduino)".
4. Click "Convert".

#### Step 2: Setting custom logo in sketch

Now once your custom logo has been prepared, let's set it in your ESP-DASH Pro library:

1. Go to `logo.h`
2. Set `DASH_LOGO_MIME` to your image file type. To find your file's mime type, use this utility: <https://www.htmlstrip.com/mime-file-type-checker>
3. Set `DASH_LOGO_WIDTH` & `DASH_LOGO_HEIGHT` according to your desired size which will be displayed on the webpage.
4. Replace the array length of `DASH_LOGO` with the newly generated array length.
5. Now open `logo.cpp`
6. Replace the data inside `DASH_LOGO` with new data generated just before using File2Raw.
