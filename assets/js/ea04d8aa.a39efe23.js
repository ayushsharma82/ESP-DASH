"use strict";(self.webpackChunkesp_dash_docs=self.webpackChunkesp_dash_docs||[]).push([[2223],{5680:(e,t,a)=>{a.d(t,{xA:()=>c,yg:()=>m});var r=a(6540);function n(e,t,a){return t in e?Object.defineProperty(e,t,{value:a,enumerable:!0,configurable:!0,writable:!0}):e[t]=a,e}function s(e,t){var a=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),a.push.apply(a,r)}return a}function i(e){for(var t=1;t<arguments.length;t++){var a=null!=arguments[t]?arguments[t]:{};t%2?s(Object(a),!0).forEach((function(t){n(e,t,a[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(a)):s(Object(a)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(a,t))}))}return e}function l(e,t){if(null==e)return{};var a,r,n=function(e,t){if(null==e)return{};var a,r,n={},s=Object.keys(e);for(r=0;r<s.length;r++)a=s[r],t.indexOf(a)>=0||(n[a]=e[a]);return n}(e,t);if(Object.getOwnPropertySymbols){var s=Object.getOwnPropertySymbols(e);for(r=0;r<s.length;r++)a=s[r],t.indexOf(a)>=0||Object.prototype.propertyIsEnumerable.call(e,a)&&(n[a]=e[a])}return n}var o=r.createContext({}),d=function(e){var t=r.useContext(o),a=t;return e&&(a="function"==typeof e?e(t):i(i({},t),e)),a},c=function(e){var t=d(e.components);return r.createElement(o.Provider,{value:t},e.children)},u="mdxType",p={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},g=r.forwardRef((function(e,t){var a=e.components,n=e.mdxType,s=e.originalType,o=e.parentName,c=l(e,["components","mdxType","originalType","parentName"]),u=d(a),g=n,m=u["".concat(o,".").concat(g)]||u[g]||p[g]||s;return a?r.createElement(m,i(i({ref:t},c),{},{components:a})):r.createElement(m,i({ref:t},c))}));function m(e,t){var a=arguments,n=t&&t.mdxType;if("string"==typeof e||n){var s=a.length,i=new Array(s);i[0]=g;var l={};for(var o in t)hasOwnProperty.call(t,o)&&(l[o]=t[o]);l.originalType=e,l[u]="string"==typeof e?e:n,i[1]=l;for(var d=2;d<s;d++)i[d]=a[d];return r.createElement.apply(null,i)}return r.createElement.apply(null,a)}g.displayName="MDXCreateElement"},426:(e,t,a)=>{a.r(t),a.d(t,{assets:()=>o,contentTitle:()=>i,default:()=>p,frontMatter:()=>s,metadata:()=>l,toc:()=>d});var r=a(8168),n=(a(6540),a(5680));const s={title:"Status Card",sidebar_label:"Status",sidebar_position:5},i=void 0,l={unversionedId:"widgets/cards/status",id:"version-v4.x.x/widgets/cards/status",title:"Status Card",description:"As it's name suggests, status card is used to display some kind of status on your dashboard. It can show 4 different kinds of status along with a short message.",source:"@site/versioned_docs/version-v4.x.x/widgets/cards/status.md",sourceDirName:"widgets/cards",slug:"/widgets/cards/status",permalink:"/widgets/cards/status",draft:!1,tags:[],version:"v4.x.x",sidebarPosition:5,frontMatter:{title:"Status Card",sidebar_label:"Status",sidebar_position:5},sidebar:"tutorialSidebar",previous:{title:"Progress Bar",permalink:"/widgets/cards/progress"},next:{title:"Toggle Button",permalink:"/widgets/cards/button"}},o={},d=[{value:"Valid Statuses",id:"valid-statuses",level:3},{value:"Initializer",id:"initializer",level:3},{value:"Callback",id:"callback",level:3},{value:"Updater",id:"updater",level:3},{value:"Reference",id:"reference",level:3}],c={toc:d},u="wrapper";function p(e){let{components:t,...a}=e;return(0,n.yg)(u,(0,r.A)({},c,a,{components:t,mdxType:"MDXLayout"}),(0,n.yg)("img",{className:"card-preview",src:"/img/v4/status-card-idle.png",width:"280px",alt:"Preview"}),(0,n.yg)("img",{className:"card-preview",src:"/img/v4/status-card-warning.png",width:"280px",alt:"Preview"}),(0,n.yg)("img",{className:"card-preview",src:"/img/v4/status-card-success.png",width:"280px",alt:"Preview"}),(0,n.yg)("img",{className:"card-preview",src:"/img/v4/status-card-danger.png",width:"280px",alt:"Preview"}),(0,n.yg)("br",null),(0,n.yg)("br",null),(0,n.yg)("p",null,"As it's name suggests, status card is used to display some kind of status on your dashboard. It can show 4 different kinds of status along with a short message."),(0,n.yg)("h3",{id:"valid-statuses"},"Valid Statuses"),(0,n.yg)("ul",null,(0,n.yg)("li",{parentName:"ul"},(0,n.yg)("inlineCode",{parentName:"li"},"s")," - Success (Green)"),(0,n.yg)("li",{parentName:"ul"},(0,n.yg)("inlineCode",{parentName:"li"},"d")," - Danger (Red)"),(0,n.yg)("li",{parentName:"ul"},(0,n.yg)("inlineCode",{parentName:"li"},"w")," - Warning (Yellow)"),(0,n.yg)("li",{parentName:"ul"},(0,n.yg)("inlineCode",{parentName:"li"},"i")," - Idle (Grey)")),(0,n.yg)("h3",{id:"initializer"},"Initializer"),(0,n.yg)("pre",null,(0,n.yg)("code",{parentName:"pre",className:"language-cpp"},'/* \n  Status Card\n  Valid Arguments: (ESPDash dashboard, Card Type, const char* name, const char* status (optional) )\n*/\nCard card1(&dashboard, STATUS_CARD, "Test Status", "s");\n')),(0,n.yg)("h3",{id:"callback"},"Callback"),(0,n.yg)("admonition",{type:"note"},(0,n.yg)("p",{parentName:"admonition"},(0,n.yg)("em",{parentName:"p"},"Status card doesn't require any callback."))),(0,n.yg)("h3",{id:"updater"},"Updater"),(0,n.yg)("p",null,"Status card updater allows you to set a message:"),(0,n.yg)("pre",null,(0,n.yg)("code",{parentName:"pre",className:"language-cpp"},'card1.update("message");\n')),(0,n.yg)("p",null,"Or, message + status at the same time:"),(0,n.yg)("pre",null,(0,n.yg)("code",{parentName:"pre",className:"language-cpp"},'card1.update("Message", "s");\n')),(0,n.yg)("h3",{id:"reference"},"Reference"),(0,n.yg)("p",null,"This is a reference sketch showing positions for intializer and updater."),(0,n.yg)("pre",null,(0,n.yg)("code",{parentName:"pre",className:"language-cpp"},'\n...\n\n/* Status card initializer */\nCard status(&dashboard, STATUS_CARD, "Test Status", "s");\n\n\nvoid setup() {\n  ...\n\n  /* Status card updater - can be used anywhere (apart from global scope) */\n  status.update("Warning message", "w");\n}\n\nvoid loop() {\n  ...\n}\n\n')))}p.isMDXComponent=!0}}]);