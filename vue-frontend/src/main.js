import Vue from 'vue'
import VueApexCharts from 'vue-apexcharts';
import vueTopprogress from 'vue-top-progress';

Vue.use(vueTopprogress)
Vue.use(VueApexCharts)
Vue.component('apexchart', VueApexCharts)

import './styles/custom.scss';

import App from './App.vue'
import router from './router'

Vue.config.productionTip = false

router.beforeEach((to, from, next) => {
  let title = to.name;
  document.title = title+" Page - DASH";
  next();
});

new Vue({
  router,
  render: h => h(App)
}).$mount('#app')
