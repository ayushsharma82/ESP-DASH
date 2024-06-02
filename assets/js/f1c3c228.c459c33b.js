"use strict";(self.webpackChunkesp_dash_docs=self.webpackChunkesp_dash_docs||[]).push([[1199],{5680:(e,r,a)=>{a.d(r,{xA:()=>p,yg:()=>m});var t=a(6540);function n(e,r,a){return r in e?Object.defineProperty(e,r,{value:a,enumerable:!0,configurable:!0,writable:!0}):e[r]=a,e}function i(e,r){var a=Object.keys(e);if(Object.getOwnPropertySymbols){var t=Object.getOwnPropertySymbols(e);r&&(t=t.filter((function(r){return Object.getOwnPropertyDescriptor(e,r).enumerable}))),a.push.apply(a,t)}return a}function l(e){for(var r=1;r<arguments.length;r++){var a=null!=arguments[r]?arguments[r]:{};r%2?i(Object(a),!0).forEach((function(r){n(e,r,a[r])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(a)):i(Object(a)).forEach((function(r){Object.defineProperty(e,r,Object.getOwnPropertyDescriptor(a,r))}))}return e}function d(e,r){if(null==e)return{};var a,t,n=function(e,r){if(null==e)return{};var a,t,n={},i=Object.keys(e);for(t=0;t<i.length;t++)a=i[t],r.indexOf(a)>=0||(n[a]=e[a]);return n}(e,r);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(t=0;t<i.length;t++)a=i[t],r.indexOf(a)>=0||Object.prototype.propertyIsEnumerable.call(e,a)&&(n[a]=e[a])}return n}var c=t.createContext({}),o=function(e){var r=t.useContext(c),a=r;return e&&(a="function"==typeof e?e(r):l(l({},r),e)),a},p=function(e){var r=o(e.components);return t.createElement(c.Provider,{value:r},e.children)},u="mdxType",s={inlineCode:"code",wrapper:function(e){var r=e.children;return t.createElement(t.Fragment,{},r)}},y=t.forwardRef((function(e,r){var a=e.components,n=e.mdxType,i=e.originalType,c=e.parentName,p=d(e,["components","mdxType","originalType","parentName"]),u=o(a),y=n,m=u["".concat(c,".").concat(y)]||u[y]||s[y]||i;return a?t.createElement(m,l(l({ref:r},p),{},{components:a})):t.createElement(m,l({ref:r},p))}));function m(e,r){var a=arguments,n=r&&r.mdxType;if("string"==typeof e||n){var i=a.length,l=new Array(i);l[0]=y;var d={};for(var c in r)hasOwnProperty.call(r,c)&&(d[c]=r[c]);d.originalType=e,d[u]="string"==typeof e?e:n,l[1]=d;for(var o=2;o<i;o++)l[o]=a[o];return t.createElement.apply(null,l)}return t.createElement.apply(null,a)}y.displayName="MDXCreateElement"},4565:(e,r,a)=>{a.r(r),a.d(r,{assets:()=>c,contentTitle:()=>l,default:()=>s,frontMatter:()=>i,metadata:()=>d,toc:()=>o});var t=a(8168),n=(a(6540),a(5680));const i={title:"Humidity Card",sidebar_label:"Humidity",sidebar_position:3},l=void 0,d={unversionedId:"cards/humidity",id:"cards/humidity",title:"Humidity Card",description:"This card adds a distinctive humidity icon, and just like generic card you can add a symbol which will be appended to your data.",source:"@site/docs/cards/humidity.md",sourceDirName:"cards",slug:"/cards/humidity",permalink:"/next/cards/humidity",draft:!1,tags:[],version:"current",sidebarPosition:3,frontMatter:{title:"Humidity Card",sidebar_label:"Humidity",sidebar_position:3},sidebar:"tutorialSidebar",previous:{title:"Temperature",permalink:"/next/cards/temperature"},next:{title:"Progress Bar",permalink:"/next/cards/progress"}},c={},o=[{value:"Initializer",id:"initializer",level:3},{value:"Callback",id:"callback",level:3},{value:"Updater",id:"updater",level:3},{value:"Reference",id:"reference",level:3}],p={toc:o},u="wrapper";function s(e){let{components:r,...a}=e;return(0,n.yg)(u,(0,t.A)({},p,a,{components:r,mdxType:"MDXLayout"}),(0,n.yg)("img",{className:"card-preview",src:"/img/v4/humidity-card.png",width:"280px",alt:"Preview"}),(0,n.yg)("br",null),(0,n.yg)("br",null),(0,n.yg)("p",null,"This card adds a distinctive humidity icon, and just like generic card you can add a symbol which will be appended to your data."),(0,n.yg)("h3",{id:"initializer"},"Initializer"),(0,n.yg)("pre",null,(0,n.yg)("code",{parentName:"pre",className:"language-cpp"},'/* \n  Humidity Card\n  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* symbol (optional) )\n*/\nCard card1(&dashboard, HUMIDITY_CARD, "Humidity1", "%");\n')),(0,n.yg)("h3",{id:"callback"},"Callback"),(0,n.yg)("admonition",{type:"note"},(0,n.yg)("p",{parentName:"admonition"},(0,n.yg)("em",{parentName:"p"},"Humidity card doesn't require any callback."))),(0,n.yg)("h3",{id:"updater"},"Updater"),(0,n.yg)("pre",null,(0,n.yg)("code",{parentName:"pre",className:"language-cpp"},"card1.update(int value);\n")),(0,n.yg)("pre",null,(0,n.yg)("code",{parentName:"pre",className:"language-cpp"},"card1.update(float value);\n")),(0,n.yg)("pre",null,(0,n.yg)("code",{parentName:"pre",className:"language-cpp"},"card1.update(String value);\n")),(0,n.yg)("p",null,"Or you can also update the symbol along with the value like this:"),(0,n.yg)("pre",null,(0,n.yg)("code",{parentName:"pre",className:"language-cpp"},'card1.update(value, "RH");\n')),(0,n.yg)("h3",{id:"reference"},"Reference"),(0,n.yg)("p",null,"This is a reference sketch showing positions for intializer and updater."),(0,n.yg)("pre",null,(0,n.yg)("code",{parentName:"pre",className:"language-cpp"},'\n...\n\n/* Humidity card initializer */\nCard humidity(&dashboard, HUMIDITY_CARD, "Humidity1");\n\n\nvoid setup() {\n  ...\n\n  /* Humidity card updater - can be used anywhere (apart from global scope) */\n  humidity.update(100);\n}\n\nvoid loop() {\n  ...\n}\n\n')))}s.isMDXComponent=!0}}]);