const WebpackShellPlugin = require('webpack-shell-plugin');
const BundleAnalyzerPlugin = require('webpack-bundle-analyzer').BundleAnalyzerPlugin;

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
        new BundleAnalyzerPlugin({ analyzerMode: (process.env.NODE_ENV !== "production")?'disabled':'static'}),
        new WebpackShellPlugin({
            onBuildEnd: (process.env.NODE_ENV == 'production')?['node finalize.js && echo Finalized Webpage for Production Mode']:['echo Skipping Finalizing Vuejs Webpage in Development Mode']
        })
      ],
      resolve:{
        alias:{
          moment: 'moment/src/moment'
        }
      }
    }
}
