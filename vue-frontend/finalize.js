// Finalize Nodejs Script
// 1 - Append JS in HTML Document
// 2 - Gzip HTML
// 3 - Covert to Raw Bytes
// 4 - ( Save to File: webpage.h ) in dist Folder

const fs = require('fs');
const zlib = require('zlib');

function getByteArray(file){
    let fileData = file.toString('hex');
    let result = []
    for (var i = 0; i < fileData.length; i+=2)
      result.push('0x'+fileData[i]+''+fileData[i+1])
    return result;
}

let js = fs.readFileSync(__dirname+'/dist/js/app.js');
let html = `
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width,initial-scale=1.0">
    <title>ESP-DASH</title>
  </head>
  <body>
    <noscript>
      <strong>We're sorry but ESP-DASH doesn't work properly without JavaScript enabled. Please enable it to continue.</strong>
    </noscript>
    <div id="app"></div>
    <script>${js}</script>
  </body>
</html>
`;
// Gzip the index.html file with JS Code.
const gzippedIndex = zlib.gzipSync(html);
let indexHTML = getByteArray(gzippedIndex);

let source = 
`
const uint32_t DASH_HTML_SIZE = ${indexHTML.length};
const uint8_t DASH_HTML[] PROGMEM = { ${indexHTML} };
`;


fs.writeFileSync(__dirname+'/dist/webpage.h', source, 'utf8');