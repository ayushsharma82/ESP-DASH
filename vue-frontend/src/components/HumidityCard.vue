<template>
  <div class="column is-6-mobile is-4-tablet is-3-desktop">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <header class="columns is-gapless is-mobile">
          <div class="column is-narrow sicon sicon-xs is-inline has-text-primary align-middle">
            <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
              xmlns:xlink="http://www.w3.org/1999/xlink">
              <g id="Stockholm-icons-/-Design-/-Color" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                <path opacity="0.6"
                  d="M12,21 C15.8659932,21 19,17.8659932 19,14 C19,11.4226712 16.6666667,8.08933783 12,4 C7.33333333,8.08933783 5,11.4226712 5,14 C5,17.8659932 8.13400675,21 12,21 Z"
                  id="Oval-2" fill="#335EEA"></path>
              </g>
            </svg>
          </div>
          <h4 class="column" style="margin-left: 0.5rem; line-height: 1.2;">{{card.value}}%</h4>
        </header>
        <p class="has-text-dark"><b>{{card.name}}</b></p>
      </div>
    </div>
  </div>
</template>

<script>
  export default {
    props: ['card'],

    data() {
      return {
        activity: true
      }
    },

    watch:{
      'card.value':function() {
        this.activity = true;
        setTimeout(() => {this.activity = false}, 100);
      }
    },

    mounted() {
      setTimeout(() => {
        this.activity = false
      }, 500);
    }
  }
</script>