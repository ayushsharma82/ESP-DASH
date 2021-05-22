const { description } = require('../../package')
const path = require('path')

module.exports = {
  base: '/ESP-DASH/',
  dest: './docs',
  theme: "book",
  /**
   * Ref：https://v1.vuepress.vuejs.org/config/#title
   */
  title: '',
  /**
   * Ref：https://v1.vuepress.vuejs.org/config/#description
   */
  description: description,

  /**
   * Extra tags to be injected to the page HTML `<head>`
   *
   * ref：https://v1.vuepress.vuejs.org/config/#head
   */
  head: [
    ['meta', { name: 'theme-color', content: '#3eaf7c' }],
    ['meta', { name: 'apple-mobile-web-app-capable', content: 'yes' }],
    ['meta', { name: 'apple-mobile-web-app-status-bar-style', content: 'black' }],
    ['script', {
      "src": "https://cdnjs.buymeacoffee.com/1.0.0/widget.prod.min.js",
      "data-name": "BMC-Widget",
      "data-id": "6QGVpSj",
      "data-description": "Support me on Buy me a coffee!",
      "data-message": "Thank you for visiting. A cup of coffee keeps my eyes open for creating stuff like this. If you love my work then this is the button to click on.",
      "data-color": "#FFDD00",
      "data-position": "Right",
      "data-x_margin": "18",
      "data-y_margin": "18"
    }]
  ],

  /**
   * Theme configuration, here is the default theme configuration for VuePress.
   *
   * ref：https://v1.vuepress.vuejs.org/theme/default-theme-config.html
   */
  themeConfig: {
    logo: '/logo.png',
    search: false,
    repo: 'ayushsharma82/ESP-DASH/',
    editLinks: true,
    docsDir: 'src',
    docsBranch: 'gh-pages',
    editLinkText: 'Help us improve this page!',
    lastUpdated: true,
    nav: [
      { text: "Home", link: "/" },
    ],
    sidebar: {
      '/': [
        {
          title: 'Home',
          collapsable: false,
          sidebarDepth: 0,
          children: [["/", "Introduction"], ['/installation', 'Installation 🔧'], ['/concept', 'Concept 💭']]
        },
        {
          title: 'Guide',
          sidebarDepth: 0,
          collapsable: false,
          children: [
            ["/guide/getting-started", "Getting Started 😃"],
            ["/guide/card-indexing", "Changing Order of Cards (Pro)"],
            ["/guide/more-examples", "More Examples"]
          ]
        },
        {
          title: 'Cards',
          sidebarDepth: 0,
          collapsable: false,
          children: [
            ["/cards/generic", "Generic"],
            ["/cards/temperature", "Temperature"],
            ["/cards/humidity", "Humidity"],
            ["/cards/air", "Air (Pro)"],
            ["/cards/energy", "Energy (Pro)"],
            ["/cards/status", "Status"],
            ["/cards/progress", "Progress"],
            ["/cards/slider", "Slider"],
            ["/cards/button", "Button"],
            ["/cards/text-input", "Text Input (Pro)"],
            ["/cards/joystick", "Joystick (Pro)"],
          ]
        },
        {
          title: 'Charts',
          sidebarDepth: 0,
          collapsable: false,
          children: [
            ["/charts/bar", "Bar"],
            ["/charts/line", "Line (Pro)"],
            ["/charts/area", "Area (Pro)"],
            ["/charts/pie", "Pie (Pro)"],
          ]
        },
      ],
    }
  },

  /**
   * Apply plugins，ref：https://v1.vuepress.vuejs.org/zh/plugin/
   */
  plugins: [
    '@vuepress/plugin-back-to-top',
    '@vuepress/plugin-medium-zoom',
    [
      '@vuepress/google-analytics',
      {
        'ga': 'UA-180577790-1'
      }
    ]
  ],
  configureWebpack: {
    resolve: {
      alias: {
        "@assets": path.resolve(__dirname, "../assets")
      }
    }
  }
}
