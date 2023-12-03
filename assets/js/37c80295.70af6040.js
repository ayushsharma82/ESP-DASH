"use strict";(self.webpackChunkesp_dash_docs=self.webpackChunkesp_dash_docs||[]).push([[9530],{3905:(e,r,t)=>{t.d(r,{Zo:()=>u,kt:()=>y});var a=t(7294);function n(e,r,t){return r in e?Object.defineProperty(e,r,{value:t,enumerable:!0,configurable:!0,writable:!0}):e[r]=t,e}function i(e,r){var t=Object.keys(e);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);r&&(a=a.filter((function(r){return Object.getOwnPropertyDescriptor(e,r).enumerable}))),t.push.apply(t,a)}return t}function l(e){for(var r=1;r<arguments.length;r++){var t=null!=arguments[r]?arguments[r]:{};r%2?i(Object(t),!0).forEach((function(r){n(e,r,t[r])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(t)):i(Object(t)).forEach((function(r){Object.defineProperty(e,r,Object.getOwnPropertyDescriptor(t,r))}))}return e}function o(e,r){if(null==e)return{};var t,a,n=function(e,r){if(null==e)return{};var t,a,n={},i=Object.keys(e);for(a=0;a<i.length;a++)t=i[a],r.indexOf(t)>=0||(n[t]=e[t]);return n}(e,r);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(a=0;a<i.length;a++)t=i[a],r.indexOf(t)>=0||Object.prototype.propertyIsEnumerable.call(e,t)&&(n[t]=e[t])}return n}var s=a.createContext({}),p=function(e){var r=a.useContext(s),t=r;return e&&(t="function"==typeof e?e(r):l(l({},r),e)),t},u=function(e){var r=p(e.components);return a.createElement(s.Provider,{value:r},e.children)},c="mdxType",d={inlineCode:"code",wrapper:function(e){var r=e.children;return a.createElement(a.Fragment,{},r)}},f=a.forwardRef((function(e,r){var t=e.components,n=e.mdxType,i=e.originalType,s=e.parentName,u=o(e,["components","mdxType","originalType","parentName"]),c=p(t),f=n,y=c["".concat(s,".").concat(f)]||c[f]||d[f]||i;return t?a.createElement(y,l(l({ref:r},u),{},{components:t})):a.createElement(y,l({ref:r},u))}));function y(e,r){var t=arguments,n=r&&r.mdxType;if("string"==typeof e||n){var i=t.length,l=new Array(i);l[0]=f;var o={};for(var s in r)hasOwnProperty.call(r,s)&&(o[s]=r[s]);o.originalType=e,o[c]="string"==typeof e?e:n,l[1]=o;for(var p=2;p<i;p++)l[p]=t[p];return a.createElement.apply(null,l)}return a.createElement.apply(null,t)}f.displayName="MDXCreateElement"},732:(e,r,t)=>{t.r(r),t.d(r,{assets:()=>s,contentTitle:()=>l,default:()=>d,frontMatter:()=>i,metadata:()=>o,toc:()=>p});var a=t(7462),n=(t(7294),t(3905));const i={title:"Bar Chart",sidebar_label:"Bar",sidebar_position:1},l=void 0,o={unversionedId:"charts/bar",id:"version-v3.x.x/charts/bar",title:"Bar Chart",description:"Preview:",source:"@site/versioned_docs/version-v3.x.x/charts/bar.md",sourceDirName:"charts",slug:"/charts/bar",permalink:"/v3.x.x/charts/bar",draft:!1,tags:[],version:"v3.x.x",sidebarPosition:1,frontMatter:{title:"Bar Chart",sidebar_label:"Bar",sidebar_position:1},sidebar:"tutorialSidebar",previous:{title:"Charts",permalink:"/v3.x.x/category/charts"},next:{title:"Line (Pro)",permalink:"/v3.x.x/charts/line"}},s={},p=[{value:"Preview:",id:"preview",level:4},{value:"Type:",id:"type",level:4},{value:"Valid Data Types for X-Axis:",id:"valid-data-types-for-x-axis",level:4},{value:"Valid Data Types for Y-Axis:",id:"valid-data-types-for-y-axis",level:4},{value:"Initializer:",id:"initializer",level:4},{value:"Updaters:",id:"updaters",level:4},{value:"For X-Axis:",id:"for-x-axis",level:5},{value:"For Y-Axis:",id:"for-y-axis",level:5}],u={toc:p},c="wrapper";function d(e){let{components:r,...t}=e;return(0,n.kt)(c,(0,a.Z)({},u,t,{components:r,mdxType:"MDXLayout"}),(0,n.kt)("h4",{id:"preview"},"Preview:"),(0,n.kt)("img",{src:"/img//bar-chart.png",width:"380px",alt:"Preview"}),(0,n.kt)("br",null),(0,n.kt)("br",null),(0,n.kt)("p",null,"It's a bar chart. period."),(0,n.kt)("p",null,"You can aggregate large amount of data in form of arrays and display them in a bar chart."),(0,n.kt)("br",null),(0,n.kt)("h4",{id:"type"},"Type:"),(0,n.kt)("p",null,(0,n.kt)("inlineCode",{parentName:"p"},"BAR_CHART")),(0,n.kt)("br",null),(0,n.kt)("h4",{id:"valid-data-types-for-x-axis"},"Valid Data Types for X-Axis:"),(0,n.kt)("ul",null,(0,n.kt)("li",{parentName:"ul"},(0,n.kt)("inlineCode",{parentName:"li"},"int")),(0,n.kt)("li",{parentName:"ul"},(0,n.kt)("inlineCode",{parentName:"li"},"float")),(0,n.kt)("li",{parentName:"ul"},(0,n.kt)("inlineCode",{parentName:"li"},"String"))),(0,n.kt)("br",null),(0,n.kt)("h4",{id:"valid-data-types-for-y-axis"},"Valid Data Types for Y-Axis:"),(0,n.kt)("ul",null,(0,n.kt)("li",{parentName:"ul"},(0,n.kt)("inlineCode",{parentName:"li"},"int")),(0,n.kt)("li",{parentName:"ul"},(0,n.kt)("inlineCode",{parentName:"li"},"float"))),(0,n.kt)("br",null),(0,n.kt)("h4",{id:"initializer"},"Initializer:"),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-cpp"},'/* \n  Bar Chart\n  Valid Arguments: (ESPDash dashboard, Card Type, const char* name )\n*/\nChart chart1(&dashboard, BAR_CHART, "Chart Name");\n')),(0,n.kt)("br",null),(0,n.kt)("h4",{id:"updaters"},"Updaters:"),(0,n.kt)("h5",{id:"for-x-axis"},"For X-Axis:"),(0,n.kt)("p",null,"X-Axis updater uses ",(0,n.kt)("inlineCode",{parentName:"p"},"updateX")," function."),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-cpp"},'/*\n  Data for X Axis of our Chart\n  This array can be of: `int` / `float` or `String`\n*/\nString XAxis[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};\n\n/*\n  Update Function for Chart is as follows:\n  --------\n  (int array[], size_t array_size)\n  or\n  (float array[], size_t array_size)\n  or\n  (String array[], size_t array_size)\n*/\nchart1.updateX(XAxis, 7);\n')),(0,n.kt)("h5",{id:"for-y-axis"},"For Y-Axis:"),(0,n.kt)("p",null,"Y-Axis updater uses ",(0,n.kt)("inlineCode",{parentName:"p"},"updateY")," function."),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-cpp"},"/*\n  Data for Y Axis of our Chart\n  This array can be of: `int` or `float`\n*/\nint YAxis[] = {0, 0, 0, 0, 0, 0, 0};\n\n/*\n  Update Function for Chart is as follows:\n  --------\n  (int array[], size_t array_size)\n  or \n  (float array[], size_t array_size)\n*/\nchart1.updateY(YAxis, 7);\n")))}d.isMDXComponent=!0}}]);