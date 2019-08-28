// Finalize Nodejs Script
// 1 - Append JS in HTML Document
// 2 - Gzip HTML
// 3 - Covert to Raw Bytes
// 4 - ( Save to File: webpage.h ) in dist Folder

const fs = require('fs');
const zlib = require('zlib');
const { gzip } = require('@gfx/zopfli');

function getByteArray(file){
    let fileData = file.toString('hex');
    let result = [];
    for (let i = 0; i < fileData.length; i+=2)
      result.push('0x'+fileData[i]+''+fileData[i+1]);
    return result;
}

// Set external path like https://localhost.localdomain/iot to serve JS files or leave blank to store files in ESP
let path = ``;
let js = fs.readFileSync(__dirname+'/dist/js/app.js');
let html = `
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width,initial-scale=1.0">
    <meta name="referrer" content="no-referrer">
    <title>ESP-DASH</title>
    ${path ? `<link rel=icon href=${path}/favicon.ico>` : ``}
    ${path ? `<link href=${path}/js/app.js rel=preload as=script>` : ``}
  </head>
  <body>
    <noscript>
      <strong>We're sorry but ESP-DASH doesn't work properly without JavaScript enabled. Please enable it to continue.</strong>
    </noscript>
    <div id="app"></div>
    <script${path ? ` src=${path}/js/app.js>` : `>${js}`}</script>
  </body>
</html>
`;
// Gzip the index.html file with JS Code.
const gzippedIndex = zlib.gzipSync(html, {'level': zlib.constants.Z_BEST_COMPRESSION});
let indexHTML = getByteArray(gzippedIndex);

let source = 
`
const uint32_t DASH_HTML_SIZE = ${indexHTML.length};
const uint8_t DASH_HTML[] PROGMEM = { ${indexHTML} };
`;


fs.writeFileSync(__dirname+'/dist/webpage.h', source, 'utf8');

// Produce a second variant with zopfli
// Zopfli is a improved zip algorithm by google
// Takes much more time and maybe is not available on every machine
const input =  html;
gzip(input, {numiterations: 15}, (err, output) => {
    indexHTML = output;
    let source =
`
const uint32_t DASH_HTML_SIZE = ${indexHTML.length};
const uint8_t DASH_HTML[] PROGMEM = { ${indexHTML} };
`;

    fs.writeFileSync(__dirname + '/dist/webpage_zopfli.h', source, 'utf8');
});
