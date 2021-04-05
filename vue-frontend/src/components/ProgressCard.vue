<template>
  <div class="column is-12-mobile is-4-tablet is-4-desktop is-3-fullhd">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <div class="columns is-mobile">
          <div class="column is-narrow">
            <div class="card-icon pb-3 pt-4 px-4 has-background-primary-light has-text-primary">
              <svg width="24" height="24" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><g fill="none" fill-rule="evenodd"><path d="M0 0h24v24H0z"></path><rect fill="currentColor" x="4" y="5" width="16" height="3" rx="1.5"></rect><path d="M5.5 15h13a1.5 1.5 0 010 3h-13a1.5 1.5 0 010-3zm0-5h7a1.5 1.5 0 010 3h-7a1.5 1.5 0 010-3z" fill="currentColor" opacity=".3"></path></g></svg>
            </div>
          </div>
          <div class="column">
            <h6 class="is-size-6 has-text-muted">{{card.name}} ( <span class="has-text-dark has-text-weight-semibold">{{card.value}} <small class="is-size-6">{{card.symbol}}</small></span> )</h6>
            <progress class="progress is-small is-primary mt-3" :value="card.value" :max="card.max" :min="card.min">{{card.value}}%</progress>
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
