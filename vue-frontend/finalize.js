// Finalize Nodejs Script
// 1 - Append JS in HTML Document
// 2 - Gzip HTML
// 3 - Covert to Raw Bytes
// 4 - ( Save to File: wiswi_webpage.h ) in dist Folder

const fs = require('fs');
const zlib = require('zlib');
const Handlebars = require('handlebars');

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
    <title>WiSwi - WiFi Switcher</title>
  </head>
  <body>
    <noscript>
      <strong>We're sorry but WiSwi doesn't work properly without JavaScript enabled. Please enable it to continue.</strong>
    </noscript>
    <div id="app"></div>
    <script>${js.toString('utf8')}</script>
  </body>
</html>
`;
// Gzip the index.html file with JS Code.
const gzippedIndex = zlib.gzipSync(html);


// Create RAW Bytes File
Handlebars.registerHelper('ifCond', function(v1, v2, options) {
    if(v1 === v2) {
      return options.fn(this);
    }
    return options.inverse(this);
});


let source = 
`
const uint16_t DASH_HTML_SIZE = {{htmlSize}};
const uint8_t DASH_HTML[] PROGMEM = { {{#each htmlBytes}}{{this}},{{/each}} };
`;

let template = Handlebars.compile(source);




// Convert Gzipped HTML to Raw Bytes
let indexHTML = getByteArray(gzippedIndex);
let compiledTemplate = template({ htmlSize: indexHTML.length, htmlBytes: indexHTML });
fs.writeFileSync(__dirname+'/dist/webpage.h', compiledTemplate, 'utf8');