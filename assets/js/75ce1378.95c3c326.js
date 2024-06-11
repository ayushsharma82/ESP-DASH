"use strict";(self.webpackChunkesp_dash_docs=self.webpackChunkesp_dash_docs||[]).push([[4594],{5680:(e,a,n)=>{n.d(a,{xA:()=>d,yg:()=>g});var t=n(6540);function i(e,a,n){return a in e?Object.defineProperty(e,a,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[a]=n,e}function r(e,a){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var t=Object.getOwnPropertySymbols(e);a&&(t=t.filter((function(a){return Object.getOwnPropertyDescriptor(e,a).enumerable}))),n.push.apply(n,t)}return n}function o(e){for(var a=1;a<arguments.length;a++){var n=null!=arguments[a]?arguments[a]:{};a%2?r(Object(n),!0).forEach((function(a){i(e,a,n[a])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):r(Object(n)).forEach((function(a){Object.defineProperty(e,a,Object.getOwnPropertyDescriptor(n,a))}))}return e}function l(e,a){if(null==e)return{};var n,t,i=function(e,a){if(null==e)return{};var n,t,i={},r=Object.keys(e);for(t=0;t<r.length;t++)n=r[t],a.indexOf(n)>=0||(i[n]=e[n]);return i}(e,a);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);for(t=0;t<r.length;t++)n=r[t],a.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(i[n]=e[n])}return i}var c=t.createContext({}),s=function(e){var a=t.useContext(c),n=a;return e&&(n="function"==typeof e?e(a):o(o({},a),e)),n},d=function(e){var a=s(e.components);return t.createElement(c.Provider,{value:a},e.children)},p="mdxType",y={inlineCode:"code",wrapper:function(e){var a=e.children;return t.createElement(t.Fragment,{},a)}},u=t.forwardRef((function(e,a){var n=e.components,i=e.mdxType,r=e.originalType,c=e.parentName,d=l(e,["components","mdxType","originalType","parentName"]),p=s(n),u=i,g=p["".concat(c,".").concat(u)]||p[u]||y[u]||r;return n?t.createElement(g,o(o({ref:a},d),{},{components:n})):t.createElement(g,o({ref:a},d))}));function g(e,a){var n=arguments,i=a&&a.mdxType;if("string"==typeof e||i){var r=n.length,o=new Array(r);o[0]=u;var l={};for(var c in a)hasOwnProperty.call(a,c)&&(l[c]=a[c]);l.originalType=e,l[p]="string"==typeof e?e:i,o[1]=l;for(var s=2;s<r;s++)o[s]=n[s];return t.createElement.apply(null,o)}return t.createElement.apply(null,n)}u.displayName="MDXCreateElement"},6242:(e,a,n)=>{n.r(a),n.d(a,{assets:()=>c,contentTitle:()=>o,default:()=>y,frontMatter:()=>r,metadata:()=>l,toc:()=>s});var t=n(8168),i=(n(6540),n(5680));const r={title:"Joystick Card",sidebar_label:"Joystick (Pro)",sidebar_position:16},o=void 0,l={unversionedId:"widgets/cards/joystick",id:"version-v4.x.x/widgets/cards/joystick",title:"Joystick Card",description:"This is an exclusive feature of DASH Pro. Check it out here.",source:"@site/versioned_docs/version-v4.x.x/widgets/cards/joystick.md",sourceDirName:"widgets/cards",slug:"/widgets/cards/joystick",permalink:"/widgets/cards/joystick",draft:!1,tags:[],version:"v4.x.x",sidebarPosition:16,frontMatter:{title:"Joystick Card",sidebar_label:"Joystick (Pro)",sidebar_position:16},sidebar:"tutorialSidebar",previous:{title:"Color Picker (Pro)",permalink:"/widgets/cards/color-picker"},next:{title:"Link (Pro)",permalink:"/widgets/cards/link"}},c={},s=[{value:"Initializer",id:"initializer",level:3},{value:"Direction Lock",id:"direction-lock",level:4},{value:"Callback",id:"callback",level:3},{value:"Directional Callback",id:"directional-callback",level:4},{value:"Coordinates Callback",id:"coordinates-callback",level:5},{value:"Updater",id:"updater",level:3},{value:"Reference",id:"reference",level:3}],d={toc:s},p="wrapper";function y(e){let{components:a,...n}=e;return(0,i.yg)(p,(0,t.A)({},d,n,{components:a,mdxType:"MDXLayout"}),(0,i.yg)("admonition",{title:"Pro Feature",type:"danger"},(0,i.yg)("p",{parentName:"admonition"},"This is an exclusive feature of DASH Pro. Check it out ",(0,i.yg)("a",{parentName:"p",href:"https://espdash.pro"},"here"),".")),(0,i.yg)("img",{className:"card-preview",src:"/img/v4/joystick-card.png",width:"280px",alt:"Preview"}),(0,i.yg)("br",null),(0,i.yg)("br",null),(0,i.yg)("p",null,"This card adds a joystick to your dashboard to control some stuff and provides you with easy to interpret directional data via callback. You can even lock direction of the joystick to X or Y axis."),(0,i.yg)("h3",{id:"initializer"},"Initializer"),(0,i.yg)("pre",null,(0,i.yg)("code",{parentName:"pre",className:"language-cpp"},'/* \n  Joystick Card\n  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* directionLock (optional) )\n*/\nCard joystick(&dashboard, JOYSTICK_CARD, "Joystick 1");\n')),(0,i.yg)("h4",{id:"direction-lock"},"Direction Lock"),(0,i.yg)("p",null,"You can lock joystick to X or Y Axis:"),(0,i.yg)("p",null,"Supply it with ",(0,i.yg)("inlineCode",{parentName:"p"},"lockX")," as 4th argument and it will lock to X axis."),(0,i.yg)("pre",null,(0,i.yg)("code",{parentName:"pre",className:"language-cpp"},'Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1", "lockX");\n')),(0,i.yg)("p",null,"Supply it with ",(0,i.yg)("inlineCode",{parentName:"p"},"lockY")," as 4th argument and it will lock to Y axis."),(0,i.yg)("pre",null,(0,i.yg)("code",{parentName:"pre",className:"language-cpp"},'Card joystick(&dashboard, JOYSTICK_CARD, "Joystick 1", "lockY");\n')),(0,i.yg)("p",null,"By default, joystick works on both axis."),(0,i.yg)("h3",{id:"callback"},"Callback"),(0,i.yg)("p",null,"Joystick Card requires a callback function which will be called when we receive a input from our dashboard. In setup block, we will be calling our ",(0,i.yg)("inlineCode",{parentName:"p"},"attachCallback")," function and provide a lambda (callback) function with a ",(0,i.yg)("inlineCode",{parentName:"p"},"const char*")," (character array) argument."),(0,i.yg)("p",null,"Joystick card has 2 callbacks, ",(0,i.yg)("inlineCode",{parentName:"p"},"directional")," and ",(0,i.yg)("inlineCode",{parentName:"p"},"coordinates"),":"),(0,i.yg)("h4",{id:"directional-callback"},"Directional Callback"),(0,i.yg)("p",null,"This callback will return the active direction of your joystick when it's moved. It will be one of the following:"),(0,i.yg)("ul",null,(0,i.yg)("li",{parentName:"ul"},(0,i.yg)("inlineCode",{parentName:"li"},"up")),(0,i.yg)("li",{parentName:"ul"},(0,i.yg)("inlineCode",{parentName:"li"},"down")),(0,i.yg)("li",{parentName:"ul"},(0,i.yg)("inlineCode",{parentName:"li"},"left")),(0,i.yg)("li",{parentName:"ul"},(0,i.yg)("inlineCode",{parentName:"li"},"right")),(0,i.yg)("li",{parentName:"ul"},(0,i.yg)("inlineCode",{parentName:"li"},"idle"))),(0,i.yg)("pre",null,(0,i.yg)("code",{parentName:"pre",className:"language-cpp"},"/*\n  We provide our attachCallback with a lambda function to handle incomming data\n  `value` is the direction of joystick 'up', 'down', 'left', 'right' or 'idle'\n*/\njoystick.attachCallback([&](const char* direction){\n  Serial.println(\"[Joystick] Current Direction: \"+String(direction));\n});\n")),(0,i.yg)("h5",{id:"coordinates-callback"},"Coordinates Callback"),(0,i.yg)("p",null,"This callback will return the active coordinates of the thumb of your joystick when it's moved. It will provide x and y coordinates which ranges from ",(0,i.yg)("inlineCode",{parentName:"p"},"-60")," to ",(0,i.yg)("inlineCode",{parentName:"p"},"60")," on each axis."),(0,i.yg)("p",null,"In case of X axis: ",(0,i.yg)("inlineCode",{parentName:"p"},"-60")," is left, ",(0,i.yg)("inlineCode",{parentName:"p"},"60")," is right.\nFor Y axis: ",(0,i.yg)("inlineCode",{parentName:"p"},"-60")," is up, and ",(0,i.yg)("inlineCode",{parentName:"p"},"60")," is bottom."),(0,i.yg)("pre",null,(0,i.yg)("code",{parentName:"pre",className:"language-cpp"},'/*\n  We provide our attachCallback with a lambda function to handle incomming data.\n  In this case, we will be getting x and y axis coordinates in range of -60 to 60\n*/\njoystick.attachCallback([&](int8_t x, int8_t y){\n  Serial.printf("[Joystick] X Axis: %d, Y Axis: %d\\n", x, y);\n});\n')),(0,i.yg)("h3",{id:"updater"},"Updater"),(0,i.yg)("admonition",{type:"note"},(0,i.yg)("p",{parentName:"admonition"},(0,i.yg)("em",{parentName:"p"},"Joystick card doesn't require any updater as value is not passed back to dashboard."))),(0,i.yg)("h3",{id:"reference"},"Reference"),(0,i.yg)("p",null,"This is a reference sketch showing positions for intializer and callback."),(0,i.yg)("pre",null,(0,i.yg)("code",{parentName:"pre",className:"language-cpp"},'\n...\n\n/* Joystick card initializer */\nCard joystick(&dashboard, JOYSTICK_CARD, "Joystick 1");\n\n\nvoid setup() {\n  ...\n\n  /* Joystick card directional callback */\n  joystick.attachCallback([&](const char* direction){\n    Serial.println("[Joystick] Current Direction: "+String(direction));\n  });\n\n  /* Joystick card coordinates callback */\n  joystick.attachCallback([&](int8_t x, int8_t y){\n    Serial.printf("[Joystick] X Axis: %d, Y Axis: %d\\n", x, y);\n  });\n}\n\nvoid loop() {\n  ...\n}\n\n')))}y.isMDXComponent=!0}}]);