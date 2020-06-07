<template>
  <div class="column is-6-mobile is-4-tablet is-3-desktop">
      <div class="card">
        <span class="dot" :class="{'active': activity}"></span>
        <div class="card-content">
          <header class="columns is-gapless is-mobile">
            <h4 class="column" style="margin-left: 0.2rem; line-height: 1.2;">
              <button class="button is-primary is-small sicon sicon-xs has-text-white" @click="sendClickEvent">
                <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                    <g id="Stockholm-icons-/-Map-/-Location-arrow" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                        <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                        <path d="M4.88230018,17.2353996 L13.2844582,0.431083506 C13.4820496,0.0359007077 13.9625881,-0.12427877 14.3577709,0.0733126292 C14.5125928,0.15072359 14.6381308,0.276261584 14.7155418,0.431083506 L23.1176998,17.2353996 C23.3152912,17.6305824 23.1551117,18.1111209 22.7599289,18.3087123 C22.5664522,18.4054506 22.3420471,18.4197165 22.1378777,18.3482572 L14,15.5 L5.86212227,18.3482572 C5.44509941,18.4942152 4.98871325,18.2744737 4.84275525,17.8574509 C4.77129597,17.6532815 4.78556182,17.4288764 4.88230018,17.2353996 Z" id="Path-99" fill="#335EEA" transform="translate(14.000087, 9.191034) rotate(-315.000000) translate(-14.000087, -9.191034) "></path>
                    </g>
                </svg>
              </button>
            </h4>
          </header>
          <p class="card-name has-text-dark">{{card.name}}</p>
        </div>
      </div>
    </div>
</template>

<script>
import EventBus from '@/event-bus.js';

export default {
    props:['card'],

    data(){
      return{
        activity: true
      }
    },

    methods:{
      sendClickEvent(){
        EventBus.$emit('buttonClicked', this.card.id);
        this.activity = true;
        setTimeout(() => { this.activity = false }, 100);
      }
    },

    mounted(){
      setTimeout(() => { this.activity = false }, 500);
    }
}
</script>