<template>
  <div class="column is-12-mobile is-4-tablet is-4-desktop is-3-fullhd">
    <div class="card">
      <span class="dot" :class="{'active': activity && !waiting, 'waiting': waiting}"></span>
      <div class="card-content">
        <div class="columns is-mobile">
          <div class="column is-narrow">
            <div class="card-icon pb-3 pt-4 px-4 has-background-link-light has-text-link">
              <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
                xmlns:xlink="http://www.w3.org/1999/xlink">
                <g id="Stockholm-icons-/-Code-/-Commit" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                  <rect id="Rectangle-5" x="0" y="0" width="24" height="24"></rect>
                  <path
                    d="M20.5,11 L22.5,11 C23.3284271,11 24,11.6715729 24,12.5 C24,13.3284271 23.3284271,14 22.5,14 L20.5,14 C19.6715729,14 19,13.3284271 19,12.5 C19,11.6715729 19.6715729,11 20.5,11 Z M1.5,11 L3.5,11 C4.32842712,11 5,11.6715729 5,12.5 C5,13.3284271 4.32842712,14 3.5,14 L1.5,14 C0.671572875,14 1.01453063e-16,13.3284271 0,12.5 C-1.01453063e-16,11.6715729 0.671572875,11 1.5,11 Z"
                    id="Combined-Shape" fill="currentColor" opacity="0.3"></path>
                  <path
                    d="M12,16 C13.6568542,16 15,14.6568542 15,13 C15,11.3431458 13.6568542,10 12,10 C10.3431458,10 9,11.3431458 9,13 C9,14.6568542 10.3431458,16 12,16 Z M12,18 C9.23857625,18 7,15.7614237 7,13 C7,10.2385763 9.23857625,8 12,8 C14.7614237,8 17,10.2385763 17,13 C17,15.7614237 14.7614237,18 12,18 Z"
                    id="Oval-15" fill="currentColor"></path>
                </g>
              </svg>
            </div>
          </div>
          <div class="column">
            <h6 class="is-size-6 has-text-muted">{{card.name}} ( <span class="has-text-dark has-text-weight-semibold">{{ displayValue }} <small class="is-size-6 has-text-weight-semibold">{{card.symbol}}</small></span> )</h6>
            <input class="slider is-fullwidth"
              @change="sendValue"
              step="1" :min="card.min" :max="card.max" v-model="displayValue"
              type="range">
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import EventBus from '@/event-bus.js';

  export default {
    props: ['card'],

    data() {
      return {
        activity: true,
        displayValue: this.card.value
      }
    },

    watch: {
      'card.value': function () {
        this.displayValue = this.card.value;
        this.activity = true;
        setTimeout(() => {
          this.activity = false
        }, 100);
      }
    },

    methods: {
      sendValue() {
        this.msg = {
          "id": this.card.id,
          "value": this.displayValue
        };

        EventBus.$emit('sliderChanged', this.msg);
      }
    },

    computed:{
      waiting(){
        if(this.card.value != this.displayValue){
          return true;
        }else{
          return false;
        }
      }
    },

    mounted() {
      setTimeout(() => {
        this.activity = false
      }, 500);
    }
  }
</script>

<style>

</style>