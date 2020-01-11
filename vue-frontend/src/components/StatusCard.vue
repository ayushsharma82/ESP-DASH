<template>
  <!-- Temperature Card -->
  <div class="column is-6-mobile is-4-tablet is-3-desktop">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <header class="columns is-gapless is-mobile" v-if="card.value == 0 || card.value == 1">
          <div class="column is-narrow sicon sicon-xs is-inline align-middle" :class="{'has-text-primary': card.value === 1, 'has-text-grey': card.value === 0}">
            <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
              xmlns:xlink="http://www.w3.org/1999/xlink">
              <g id="Stockholm-icons-/-Code-/-Thunder-circle" stroke="none" stroke-width="1" fill="none"
                fill-rule="evenodd">
                <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                <circle id="Oval-5" fill="#335EEA" opacity="0.3" cx="12" cy="12" r="10"></circle>
                <path
                  d="M12.4208204,17.1583592 L15.4572949,11.0854102 C15.6425368,10.7149263 15.4923686,10.2644215 15.1218847,10.0791796 C15.0177431,10.0271088 14.9029083,10 14.7864745,10 L12,10 L12,7.17705098 C12,6.76283742 11.6642136,6.42705098 11.25,6.42705098 C10.965921,6.42705098 10.7062236,6.58755277 10.5791796,6.84164079 L7.5427051,12.9145898 C7.35746316,13.2850737 7.50763142,13.7355785 7.87811529,13.9208204 C7.98225687,13.9728912 8.09709167,14 8.21352549,14 L11,14 L11,16.822949 C11,17.2371626 11.3357864,17.572949 11.75,17.572949 C12.034079,17.572949 12.2937764,17.4124472 12.4208204,17.1583592 Z"
                  id="Path-3" fill="#335EEA"></path>
              </g>
            </svg>
          </div>
          <h4 class="column" style="margin-left: 0.5rem; line-height: 1.2;">{{ (card.value == 0)?'Off':'On' }}</h4>
        </header>
        <header class="columns is-gapless is-mobile" v-else-if="card.value == 2 || card.value == 3">
          <div class="column is-narrow sicon sicon-xs is-inline has-text-warning align-middle" v-if="card.value == 2">
            <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
              xmlns:xlink="http://www.w3.org/1999/xlink">
              <g id="Stockholm-icons-/-Code-/-Warning-2" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                <path
                  d="M11.1669899,4.49941818 L2.82535718,19.5143571 C2.557144,19.9971408 2.7310878,20.6059441 3.21387153,20.8741573 C3.36242953,20.9566895 3.52957021,21 3.69951446,21 L21.2169432,21 C21.7692279,21 22.2169432,20.5522847 22.2169432,20 C22.2169432,19.8159952 22.1661743,19.6355579 22.070225,19.47855 L12.894429,4.4636111 C12.6064401,3.99235656 11.9909517,3.84379039 11.5196972,4.13177928 C11.3723594,4.22181902 11.2508468,4.34847583 11.1669899,4.49941818 Z"
                  id="Path-117" fill="#335EEA" opacity="0.3"></path>
                <rect id="Rectangle-9" fill="#335EEA" x="11" y="9" width="2" height="7" rx="1"></rect>
                <rect id="Rectangle-9-Copy" fill="#335EEA" x="11" y="17" width="2" height="2" rx="1"></rect>
              </g>
            </svg>
          </div>
          <div class="column is-narrow sicon sicon-xs is-inline has-text-danger align-middle" v-if="card.value == 3">
            <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
              xmlns:xlink="http://www.w3.org/1999/xlink">
              <g id="Stockholm-icons-/-Code-/-Warning-1-circle" stroke="none" stroke-width="1" fill="none"
                fill-rule="evenodd">
                <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                <circle id="Oval-5" fill="#335EEA" opacity="0.3" cx="12" cy="12" r="10"></circle>
                <rect id="Rectangle-9" fill="#335EEA" x="11" y="7" width="2" height="8" rx="1"></rect>
                <rect id="Rectangle-9-Copy" fill="#335EEA" x="11" y="16" width="2" height="2" rx="1"></rect>
              </g>
            </svg>
          </div>
          <h4 class="column" style="margin-left: 0.5rem; line-height: 1.2;">{{ (card.value == 2)?'Warning':'Error' }}</h4>
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