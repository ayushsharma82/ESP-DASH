import Vue from 'vue'

import App from './App.vue'
import router from './router'

Vue.config.productionTip = false

router.beforeEach((to, from, next) => {
  let name = to.params.goto ? to.params.goto : to.name;
  document.title = name+" - ESP-DASH";
  next();
});

new Vue({
  router,
  render: h => h(App)
}).$mount('#app')
