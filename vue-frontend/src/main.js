import Vue from 'vue'

import App from './App.vue'
import router from './router'

Vue.config.productionTip = false

router.beforeEach((to, from, next) => {
  let title = to.name;
  document.title = title+" - ESP-DASH";
  next();
});

new Vue({
  router,
  render: h => h(App)
}).$mount('#app')
