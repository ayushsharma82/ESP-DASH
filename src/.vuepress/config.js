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
    ['meta', { name: 'apple-mobile-web-app-status-bar-style', content: 'black' }]
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
    editLinks: false,
    docsDir: 'docs',
    editLinkText: '',
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
            ["/cards/status", "Status"],
            ["/cards/progress", "Progress"],
            ["/cards/slider", "Slider"],
            ["/cards/button", "Button"],
          ]
        },
        {
          title: 'Charts',
          sidebarDepth: 0,
          collapsable: false,
          children: [
            ["/charts/bar", "Bar"],
          ]
        },
        {
          title: 'Reference',
          sidebarDepth: 0,
          collapsable: false,
          children: [
            ["/reference/card", "Card Class"]
          ]
        }
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
