<template>
  <!-- Temperature Card -->
  <div class="column is-2">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <header><h5>{{name}}</h5></header>
        <Br/>
        <p><target-icon @click="sendClickEvent"></target-icon></p>
      </div>
    </div>
  </div>
</template>

<script>
import EventBus from '@/event-bus.js';
import { TargetIcon } from 'vue-feather-icons';
import { setTimeout } from 'timers';

export default {
    props:['id', 'name'],

    data(){
      return{
        activity: true
      }
    },

    components:{
        TargetIcon
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

.card svg:active{
  color:dodgerblue;
}
</style>
