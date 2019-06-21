<template>
  <!-- Button Status Card -->
  <div class="column is-2">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <header><h5>{{name}}</h5></header>
        <Br/>
        <p>
          <toggle-right-icon @click="sendClickEvent" class="is_on" v-if="value == 1"></toggle-right-icon>
          <toggle-left-icon @click="sendClickEvent" v-else></toggle-left-icon>
        </p>
      </div>
    </div>
  </div>
</template>

<script>
import EventBus from '@/event-bus.js';
import { setTimeout } from 'timers';
import { ToggleLeftIcon, ToggleRightIcon } from 'vue-feather-icons';

export default {
    props:['id', 'name', 'value'],

    data(){
      return{
        activity: true
      }
    },

    components:{
        ToggleLeftIcon,
        ToggleRightIcon,
    },

    watch: {
      value: function() {
        this.activity = true;
        setTimeout(() => {this.activity = false}, 100);
      }
    },

    methods:{
      sendClickEvent(){
        EventBus.$emit('buttonClicked', this.id);
        this.activity = true;
        setTimeout(() => { this.activity = false }, 100);
      }
    },

    mounted(){
      setTimeout(() => { this.activity = false }, 500);
    }
}
</script>

<style scoped>
.card svg{
  width: 64px;
  height: 64px;
  cursor: pointer;
}

.card svg.is_on{
  color:rgb(24, 187, 73);
}

</style>
