<template>
  <div class="column is-12-mobile is-4-tablet is-4-desktop is-3-fullhd">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <div class="columns is-mobile">
          <div class="column is-narrow">
            <div class="card-icon pb-3 pt-4 px-4 has-background-grey-dark has-text-white">
              <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                <g id="Stockholm-icons-/-Home-/-Ruller" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                    <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                    <path d="M15,7 L15,8 C15,8.55228475 15.4477153,9 16,9 C16.5522847,9 17,8.55228475 17,8 L17,7 L19,7 L19,10 C19,10.5522847 19.4477153,11 20,11 C20.5522847,11 21,10.5522847 21,10 L21,7 C22.1045695,7 23,7.8954305 23,9 L23,15 C23,16.1045695 22.1045695,17 21,17 L3,17 C1.8954305,17 1,16.1045695 1,15 L1,9 C1,7.8954305 1.8954305,7 3,7 L3,10 C3,10.5522847 3.44771525,11 4,11 C4.55228475,11 5,10.5522847 5,10 L5,7 L7,7 L7,8 C7,8.55228475 7.44771525,9 8,9 C8.55228475,9 9,8.55228475 9,8 L9,7 L11,7 L11,10 C11,10.5522847 11.4477153,11 12,11 C12.5522847,11 13,10.5522847 13,10 L13,7 L15,7 Z" id="Combined-Shape" fill="currentColor" transform="translate(12.000000, 12.000000) rotate(-45.000000) translate(-12.000000, -12.000000) "></path>
                </g>
              </svg>
            </div>
          </div>
          <div class="column">
            <h6 class="is-size-6 has-text-muted">{{card.name}}</h6>
            <h2 class="is-size-4 has-text-dark has-text-weight-semibold">{{card.value}} <small class="is-size-6">{{card.symbol}}</small></h2>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  props:['card'],

  data(){
    return{
      activity: true
    }
  },

  watch:{
    'card.value':function() {
      this.activity = true;
      setTimeout(() => {this.activity = false}, 100);
    }
  },

  mounted(){
    setTimeout(() => { this.activity = false }, 500);
  }
}
</script>
