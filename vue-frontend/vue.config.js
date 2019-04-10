const WebpackShellPlugin = require('webpack-shell-plugin');

module.exports = {
  pluginOptions: {
    'style-resources-loader': {
      preProcessor: 'scss',
      patterns: []
    }
  },

  baseUrl: undefined,
  outputDir: undefined,
  assetsDir: undefined,
  runtimeCompiler: undefined,
  productionSourceMap: undefined,
  parallel: undefined,
  css: { extract: false },
  filenameHashing: false,
  chainWebpack: config => {
    config.optimization.delete('splitChunks')
  },
  configureWebpack: {
      plugins: [
        new WebpackShellPlugin({
            onBuildEnd: (process.env.NODE_ENV == 'production')?['node finalize.js']:['echo Skipping Finalizing Vuejs Webpage']
        })
      ]
    }
}
