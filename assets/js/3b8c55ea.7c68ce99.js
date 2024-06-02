"use strict";(self.webpackChunkesp_dash_docs=self.webpackChunkesp_dash_docs||[]).push([[6803],{5680:(e,t,r)=>{r.d(t,{xA:()=>p,yg:()=>d});var n=r(6540);function a(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function i(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function o(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?i(Object(r),!0).forEach((function(t){a(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):i(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function l(e,t){if(null==e)return{};var r,n,a=function(e,t){if(null==e)return{};var r,n,a={},i=Object.keys(e);for(n=0;n<i.length;n++)r=i[n],t.indexOf(r)>=0||(a[r]=e[r]);return a}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(n=0;n<i.length;n++)r=i[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(a[r]=e[r])}return a}var s=n.createContext({}),u=function(e){var t=n.useContext(s),r=t;return e&&(r="function"==typeof e?e(t):o(o({},t),e)),r},p=function(e){var t=u(e.components);return n.createElement(s.Provider,{value:t},e.children)},c="mdxType",g={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},y=n.forwardRef((function(e,t){var r=e.components,a=e.mdxType,i=e.originalType,s=e.parentName,p=l(e,["components","mdxType","originalType","parentName"]),c=u(r),y=a,d=c["".concat(s,".").concat(y)]||c[y]||g[y]||i;return r?n.createElement(d,o(o({ref:t},p),{},{components:r})):n.createElement(d,o({ref:t},p))}));function d(e,t){var r=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var i=r.length,o=new Array(i);o[0]=y;var l={};for(var s in t)hasOwnProperty.call(t,s)&&(l[s]=t[s]);l.originalType=e,l[c]="string"==typeof e?e:a,o[1]=l;for(var u=2;u<i;u++)o[u]=r[u];return n.createElement.apply(null,o)}return n.createElement.apply(null,r)}y.displayName="MDXCreateElement"},9824:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>s,contentTitle:()=>o,default:()=>g,frontMatter:()=>i,metadata:()=>l,toc:()=>u});var n=r(8168),a=(r(6540),r(5680));const i={title:"Installation",sidebar_label:"Installation",sidebar_position:3},o=void 0,l={unversionedId:"installation",id:"installation",title:"Installation",description:"This document explains the installation procedure for getting started with ESP-DASH.",source:"@site/docs/installation.md",sourceDirName:".",slug:"/installation",permalink:"/next/installation",draft:!1,tags:[],version:"current",sidebarPosition:3,frontMatter:{title:"Installation",sidebar_label:"Installation",sidebar_position:3},sidebar:"tutorialSidebar",previous:{title:"Concept",permalink:"/next/concept"},next:{title:"Getting Started",permalink:"/next/getting-started"}},s={},u=[{value:"Dependencies",id:"dependencies",level:3},{value:"For ESP8266",id:"for-esp8266",level:4},{value:"For ESP32",id:"for-esp32",level:4},{value:"Installing ESP-DASH",id:"installing-esp-dash",level:3},{value:"1. Directly Through Arduino IDE - Library Manager",id:"1-directly-through-arduino-ide---library-manager",level:4},{value:"2. Manual Install",id:"2-manual-install",level:4},{value:"For Windows:",id:"for-windows",level:5},{value:"For Linux:",id:"for-linux",level:5},{value:"3. Import through Arduino IDE",id:"3-import-through-arduino-ide",level:4}],p={toc:u},c="wrapper";function g(e){let{components:t,...r}=e;return(0,a.yg)(c,(0,n.A)({},p,r,{components:t,mdxType:"MDXLayout"}),(0,a.yg)("p",null,"This document explains the installation procedure for getting started with ESP-DASH."),(0,a.yg)("h3",{id:"dependencies"},"Dependencies"),(0,a.yg)("p",null,(0,a.yg)("em",{parentName:"p"},"ESP-DASH depends on the following libraries present in your libraries folder. Please stricly install the compatible versions of these dependencies only! Using any other version might break ESP-DASH or may cause ESP-DASH to work partially.")),(0,a.yg)("admonition",{title:"Note on Dependencies",type:"important"},(0,a.yg)("p",{parentName:"admonition"},"As of v2, ESP-DASH has officially switched to using fork of ESPAsyncWebServer and its dependencies from ",(0,a.yg)("a",{parentName:"p",href:"https://github.com/mathieucarbou"},"@mathieucarbou"),". This fork of ESPAsyncWebServer is being maintained regularly and contains many bug fixes along with arduino-esp32 core v3 support."),(0,a.yg)("p",{parentName:"admonition"},"It's suggested to migrate all your projects to using this fork as the original me-no-dev/ESPAsyncWebServer repo is not being maintained  ",(0,a.yg)("em",{parentName:"p"},"since years"),".")),(0,a.yg)("h4",{id:"for-esp8266"},"For ESP8266"),(0,a.yg)("ul",null,(0,a.yg)("li",{parentName:"ul"},(0,a.yg)("a",{parentName:"li",href:"https://github.com/esp8266/Arduino"},"ESP8266 Arduino Core")," - ",(0,a.yg)("strong",{parentName:"li"},"latest")),(0,a.yg)("li",{parentName:"ul"},"(mathieucarbou) ",(0,a.yg)("a",{parentName:"li",href:"https://github.com/mathieucarbou/esphome-ESPAsyncTCP#v2.0.0"},"esphome-ESPAsyncTCP")," - ",(0,a.yg)("strong",{parentName:"li"},"v2.0.0")),(0,a.yg)("li",{parentName:"ul"},"(mathieucarbou) ",(0,a.yg)("a",{parentName:"li",href:"https://github.com/mathieucarbou/ESPAsyncWebServer#v2.10.4"},"ESPAsyncWebServer")," - ",(0,a.yg)("strong",{parentName:"li"},"v2.10.4")),(0,a.yg)("li",{parentName:"ul"},(0,a.yg)("a",{parentName:"li",href:"https://github.com/bblanchon/ArduinoJson"},"ArduinoJson")," - ",(0,a.yg)("strong",{parentName:"li"},"v7.0.2"))),(0,a.yg)("h4",{id:"for-esp32"},"For ESP32"),(0,a.yg)("ul",null,(0,a.yg)("li",{parentName:"ul"},(0,a.yg)("a",{parentName:"li",href:"https://github.com/espressif/arduino-esp32"},"ESP32 Arduino Core")," @ ",(0,a.yg)("strong",{parentName:"li"},"latest")),(0,a.yg)("li",{parentName:"ul"},"(mathieucarbou) ",(0,a.yg)("a",{parentName:"li",href:"https://github.com/mathieucarbou/AsyncTCP#v3.1.4"},"AsyncTCP")," @ ",(0,a.yg)("strong",{parentName:"li"},"v3.1.4")),(0,a.yg)("li",{parentName:"ul"},"(mathieucarbou) ",(0,a.yg)("a",{parentName:"li",href:"https://github.com/mathieucarbou/ESPAsyncWebServer#v2.10.4"},"ESPAsyncWebServer")," - ",(0,a.yg)("strong",{parentName:"li"},"v2.10.4")),(0,a.yg)("li",{parentName:"ul"},(0,a.yg)("a",{parentName:"li",href:"https://github.com/bblanchon/ArduinoJson"},"ArduinoJson")," - ",(0,a.yg)("strong",{parentName:"li"},"v7.0.2"))),(0,a.yg)("h3",{id:"installing-esp-dash"},"Installing ESP-DASH"),(0,a.yg)("h4",{id:"1-directly-through-arduino-ide---library-manager"},"1. Directly Through Arduino IDE - Library Manager"),(0,a.yg)("p",null,'Go to Sketch > Include Library > Library Manager > Search for "ESP-DASH" > Install'),(0,a.yg)("h4",{id:"2-manual-install"},"2. Manual Install"),(0,a.yg)("h5",{id:"for-windows"},"For Windows:"),(0,a.yg)("ul",null,(0,a.yg)("li",{parentName:"ul"},"Download the ",(0,a.yg)("a",{parentName:"li",href:"https://github.com/ayushsharma82/ESP-DASH/archive/master.zip"},"Repository")),(0,a.yg)("li",{parentName:"ul"},"Extract the .zip in ",(0,a.yg)("inlineCode",{parentName:"li"},'Documents > Arduino > Libraries > {Place "ESP-DASH" folder Here}'))),(0,a.yg)("h5",{id:"for-linux"},"For Linux:"),(0,a.yg)("ul",null,(0,a.yg)("li",{parentName:"ul"},"Download the ",(0,a.yg)("a",{parentName:"li",href:"https://github.com/ayushsharma82/ESP-DASH/archive/master.zip"},"Repository")," "),(0,a.yg)("li",{parentName:"ul"},"Extract the .zip in ",(0,a.yg)("inlineCode",{parentName:"li"},'Sketchbook > Libraries > {Place "ESP-DASH" folder Here}'))),(0,a.yg)("h4",{id:"3-import-through-arduino-ide"},"3. Import through Arduino IDE"),(0,a.yg)("ul",null,(0,a.yg)("li",{parentName:"ul"},"Download the ",(0,a.yg)("a",{parentName:"li",href:"https://github.com/ayushsharma82/ESP-DASH/archive/master.zip"},"Repository")),(0,a.yg)("li",{parentName:"ul"},"Go to ",(0,a.yg)("inlineCode",{parentName:"li"},"Sketch > Include Library > Add .zip Library > Select the Downloaded .zip File."))))}g.isMDXComponent=!0}}]);