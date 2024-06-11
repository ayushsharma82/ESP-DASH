"use strict";(self.webpackChunkesp_dash_docs=self.webpackChunkesp_dash_docs||[]).push([[62],{5680:(e,t,a)=>{a.d(t,{xA:()=>p,yg:()=>g});var r=a(6540);function i(e,t,a){return t in e?Object.defineProperty(e,t,{value:a,enumerable:!0,configurable:!0,writable:!0}):e[t]=a,e}function n(e,t){var a=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),a.push.apply(a,r)}return a}function s(e){for(var t=1;t<arguments.length;t++){var a=null!=arguments[t]?arguments[t]:{};t%2?n(Object(a),!0).forEach((function(t){i(e,t,a[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(a)):n(Object(a)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(a,t))}))}return e}function o(e,t){if(null==e)return{};var a,r,i=function(e,t){if(null==e)return{};var a,r,i={},n=Object.keys(e);for(r=0;r<n.length;r++)a=n[r],t.indexOf(a)>=0||(i[a]=e[a]);return i}(e,t);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);for(r=0;r<n.length;r++)a=n[r],t.indexOf(a)>=0||Object.prototype.propertyIsEnumerable.call(e,a)&&(i[a]=e[a])}return i}var l=r.createContext({}),c=function(e){var t=r.useContext(l),a=t;return e&&(a="function"==typeof e?e(t):s(s({},t),e)),a},p=function(e){var t=c(e.components);return r.createElement(l.Provider,{value:t},e.children)},u="mdxType",d={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},y=r.forwardRef((function(e,t){var a=e.components,i=e.mdxType,n=e.originalType,l=e.parentName,p=o(e,["components","mdxType","originalType","parentName"]),u=c(a),y=i,g=u["".concat(l,".").concat(y)]||u[y]||d[y]||n;return a?r.createElement(g,s(s({ref:t},p),{},{components:a})):r.createElement(g,s({ref:t},p))}));function g(e,t){var a=arguments,i=t&&t.mdxType;if("string"==typeof e||i){var n=a.length,s=new Array(n);s[0]=y;var o={};for(var l in t)hasOwnProperty.call(t,l)&&(o[l]=t[l]);o.originalType=e,o[u]="string"==typeof e?e:i,s[1]=o;for(var c=2;c<n;c++)s[c]=a[c];return r.createElement.apply(null,s)}return r.createElement.apply(null,a)}y.displayName="MDXCreateElement"},3603:(e,t,a)=>{a.r(t),a.d(t,{assets:()=>l,contentTitle:()=>s,default:()=>d,frontMatter:()=>n,metadata:()=>o,toc:()=>c});var r=a(8168),i=(a(6540),a(5680));const n={title:"Statistics",sidebar_label:"Statistics",sidebar_position:3},s=void 0,o={unversionedId:"widgets/custom-statistics",id:"version-v4.x.x/widgets/custom-statistics",title:"Statistics",description:'ESP-DASH has a dedicated page called "Statistics" on the dashboard which contain key-value pairs of system statistics ( heap, flash usage etc. ) by default. With the launch of ESP-DASH V4, user defined statistics are now also part of the library! You can now add your own statitics to this page. \ud83c\udf89',source:"@site/versioned_docs/version-v4.x.x/widgets/custom-statistics.md",sourceDirName:"widgets",slug:"/widgets/custom-statistics",permalink:"/widgets/custom-statistics",draft:!1,tags:[],version:"v4.x.x",sidebarPosition:3,frontMatter:{title:"Statistics",sidebar_label:"Statistics",sidebar_position:3},sidebar:"tutorialSidebar",previous:{title:"Pie (Pro)",permalink:"/widgets/charts/pie"},next:{title:"Tabs (Pro)",permalink:"/widgets/tabs"}},l={},c=[{value:"Example",id:"example",level:3},{value:"Initializer:",id:"initializer",level:5},{value:"Update Value:",id:"update-value",level:5},{value:"Update both Key &amp; Value:",id:"update-both-key--value",level:5}],p={toc:c},u="wrapper";function d(e){let{components:t,...a}=e;return(0,i.yg)(u,(0,r.A)({},p,a,{components:t,mdxType:"MDXLayout"}),(0,i.yg)("img",{src:"/img/v4/statistics.png",alt:"Concept Diagram",width:"940px"}),(0,i.yg)("br",null),(0,i.yg)("br",null),(0,i.yg)("p",null,'ESP-DASH has a dedicated page called "Statistics" on the dashboard which contain key-value pairs of system statistics ( heap, flash usage etc. ) by default. With the launch of ESP-DASH V4, user defined statistics are now also part of the library! You can now add your own statitics to this page. \ud83c\udf89'),(0,i.yg)("p",null,(0,i.yg)("em",{parentName:"p"},"Note: System statistics can be turned off any time, you may look at ",(0,i.yg)("a",{parentName:"em",href:"./features/disable-stats.md"},"Disable Statistics")," page.")),(0,i.yg)("h3",{id:"example"},"Example"),(0,i.yg)("h5",{id:"initializer"},"Initializer:"),(0,i.yg)("pre",null,(0,i.yg)("code",{parentName:"pre",className:"language-cpp"},'Statistic stat1(&dashboard, "Key", "Value");\n')),(0,i.yg)("h5",{id:"update-value"},"Update Value:"),(0,i.yg)("pre",null,(0,i.yg)("code",{parentName:"pre",className:"language-cpp"},'stat1.set("New Value");\n')),(0,i.yg)("h5",{id:"update-both-key--value"},"Update both Key & Value:"),(0,i.yg)("pre",null,(0,i.yg)("code",{parentName:"pre",className:"language-cpp"},'stat1.set("New Key", "New Value");\n')))}d.isMDXComponent=!0}}]);