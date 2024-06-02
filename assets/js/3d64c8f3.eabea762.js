"use strict";(self.webpackChunkesp_dash_docs=self.webpackChunkesp_dash_docs||[]).push([[6852],{5680:(e,r,n)=>{n.d(r,{xA:()=>p,yg:()=>f});var t=n(6540);function a(e,r,n){return r in e?Object.defineProperty(e,r,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[r]=n,e}function i(e,r){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var t=Object.getOwnPropertySymbols(e);r&&(t=t.filter((function(r){return Object.getOwnPropertyDescriptor(e,r).enumerable}))),n.push.apply(n,t)}return n}function o(e){for(var r=1;r<arguments.length;r++){var n=null!=arguments[r]?arguments[r]:{};r%2?i(Object(n),!0).forEach((function(r){a(e,r,n[r])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):i(Object(n)).forEach((function(r){Object.defineProperty(e,r,Object.getOwnPropertyDescriptor(n,r))}))}return e}function l(e,r){if(null==e)return{};var n,t,a=function(e,r){if(null==e)return{};var n,t,a={},i=Object.keys(e);for(t=0;t<i.length;t++)n=i[t],r.indexOf(n)>=0||(a[n]=e[n]);return a}(e,r);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(t=0;t<i.length;t++)n=i[t],r.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var c=t.createContext({}),s=function(e){var r=t.useContext(c),n=r;return e&&(n="function"==typeof e?e(r):o(o({},r),e)),n},p=function(e){var r=s(e.components);return t.createElement(c.Provider,{value:r},e.children)},d="mdxType",u={inlineCode:"code",wrapper:function(e){var r=e.children;return t.createElement(t.Fragment,{},r)}},y=t.forwardRef((function(e,r){var n=e.components,a=e.mdxType,i=e.originalType,c=e.parentName,p=l(e,["components","mdxType","originalType","parentName"]),d=s(n),y=a,f=d["".concat(c,".").concat(y)]||d[y]||u[y]||i;return n?t.createElement(f,o(o({ref:r},p),{},{components:n})):t.createElement(f,o({ref:r},p))}));function f(e,r){var n=arguments,a=r&&r.mdxType;if("string"==typeof e||a){var i=n.length,o=new Array(i);o[0]=y;var l={};for(var c in r)hasOwnProperty.call(r,c)&&(l[c]=r[c]);l.originalType=e,l[d]="string"==typeof e?e:a,o[1]=l;for(var s=2;s<i;s++)o[s]=n[s];return t.createElement.apply(null,o)}return t.createElement.apply(null,n)}y.displayName="MDXCreateElement"},5898:(e,r,n)=>{n.r(r),n.d(r,{assets:()=>c,contentTitle:()=>o,default:()=>u,frontMatter:()=>i,metadata:()=>l,toc:()=>s});var t=n(8168),a=(n(6540),n(5680));const i={title:"Link Card",sidebar_label:"Link (Pro)",sidebar_position:17},o=void 0,l={unversionedId:"cards/link",id:"version-v4.x.x/cards/link",title:"Link Card",description:"This is an exclusive feature of DASH Pro. Check it out here.",source:"@site/versioned_docs/version-v4.x.x/cards/link.md",sourceDirName:"cards",slug:"/cards/link",permalink:"/cards/link",draft:!1,tags:[],version:"v4.x.x",sidebarPosition:17,frontMatter:{title:"Link Card",sidebar_label:"Link (Pro)",sidebar_position:17},sidebar:"tutorialSidebar",previous:{title:"Joystick (Pro)",permalink:"/cards/joystick"},next:{title:"Time Sync (Pro)",permalink:"/cards/time-sync"}},c={},s=[{value:"Initializer",id:"initializer",level:3},{value:"Callback",id:"callback",level:3},{value:"Updater",id:"updater",level:3},{value:"Reference",id:"reference",level:3}],p={toc:s},d="wrapper";function u(e){let{components:r,...n}=e;return(0,a.yg)(d,(0,t.A)({},p,n,{components:r,mdxType:"MDXLayout"}),(0,a.yg)("admonition",{title:"Pro Feature",type:"danger"},(0,a.yg)("p",{parentName:"admonition"},"This is an exclusive feature of DASH Pro. Check it out ",(0,a.yg)("a",{parentName:"p",href:"https://espdash.pro"},"here"),".")),(0,a.yg)("img",{className:"card-preview",src:"/img/v4/link-card.png",width:"280px",alt:"Text Input Card Preview"}),(0,a.yg)("br",null),(0,a.yg)("br",null),(0,a.yg)("p",null,"Link card is particularly useful when you want to redirect user to a new page. This card accepts valid URL schemes as string which will be passed on to dashboard for user action."),(0,a.yg)("h3",{id:"initializer"},"Initializer"),(0,a.yg)("pre",null,(0,a.yg)("code",{parentName:"pre",className:"language-cpp"},'/* \n  Link Card\n  Valid Arguments: (ESPDash dashboard, Card Type, const char* name)\n*/\nCard linkcard(&dashboard, LINK_CARD, "Test Link");\n')),(0,a.yg)("h3",{id:"callback"},"Callback"),(0,a.yg)("admonition",{type:"note"},(0,a.yg)("p",{parentName:"admonition"},(0,a.yg)("em",{parentName:"p"},"Link card doesn't require any callback."))),(0,a.yg)("h3",{id:"updater"},"Updater"),(0,a.yg)("p",null,"After initialization, you will have to provide the URL which has to be opened when user clicks on the card. You can do this by calling the ",(0,a.yg)("inlineCode",{parentName:"p"},"update")," function."),(0,a.yg)("pre",null,(0,a.yg)("code",{parentName:"pre",className:"language-cpp"},"linkcard.update(const char* url);\n")),(0,a.yg)("h3",{id:"reference"},"Reference"),(0,a.yg)("p",null,"This is a reference sketch showing positions for intializer and updater."),(0,a.yg)("pre",null,(0,a.yg)("code",{parentName:"pre",className:"language-cpp"},'\n...\n\n/* Link card initializer */\nCard linkcard(&dashboard, LINK_CARD, "Test Link");\n\n\nvoid setup() {\n  ...\n\n  /* Link card updater - can be used anywhere (apart from global scope) */\n  linkcard.update("https://espdash.pro");\n}\n\nvoid loop() {\n  ...\n}\n\n')))}u.isMDXComponent=!0}}]);