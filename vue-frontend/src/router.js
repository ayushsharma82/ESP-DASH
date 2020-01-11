import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router);

import Home from './views/Home.vue';
import About from './views/About.vue';
import Stats from './views/Stats.vue';
import Contributing from './views/Contributing.vue';
import Licensing from './views/Licensing.vue';
// import Lock from './views/Lock.vue';

export default new Router({
  linkActiveClass: 'is-active',
  routes: [
    /*
    {
      path: '/locked',
      name: 'Locked',
      component: Lock
    },
    */
    {
      path: '/',
      name: 'Home',
      component: Home
    },
    {
      path: '/about',
      name: 'About',
      component: About
    },
    {
      path: '/statistics',
      name: 'Statistics',
      component: Stats
    },
    {
      path: '/contribute',
      name: 'Contribute',
      component: Contributing
    },
    {
      path: '/licensing',
      name: 'Licensing',
      component: Licensing
    }
  ]
})

