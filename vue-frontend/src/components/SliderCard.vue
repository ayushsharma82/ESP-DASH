<!-- 
Credits:
# Made by Malcolm Brook
# Github: https://github.com/malbrook
# Email: malcolm.brook@toddesigns.com
# Created On: 12-4-2019
-->

<template>
    <!-- Slider Card -->
    <div class="column" :class="[generateCardSize]">
        <div class="card">
          <span class="card-loader" v-if="value != displayValue && valueSent == true"><loader-icon class="spinner"></loader-icon></span>
          <span class="dot" :class="{'active': activity}"></span>
          <div class="card-content has-text-centered">
            <header><h5>{{name}}</h5></header>
            <vue-slider
                ref="slider"
                :clickable="false"
                v-model="displayValue"
                style="display: inline-block; margin: 30px;"
                v-bind="getSliderOpts"
                @drag-end="sendValue"
            ></vue-slider>
            <h2>{{displayValue}}</h2>
          </div>
        </div>
    </div>
</template>

<script>
    import VueSlider from 'vue-slider-component'
    import { LoaderIcon } from 'vue-feather-icons'
    import EventBus from '@/event-bus.js';
    import { setTimeout } from 'timers';
    
    export default {
        props:['id', 'name' , 'type', 'value'],
        
       components: {
            VueSlider,
            LoaderIcon
        },

        data () {
          return {
            activity: true,
            msg:"",
            displayValue: this.value,
            valueSent: false
          }
        },

        watch: {
          value:function() {
              this.displayValue = this.value;
              this.valueSent = false;
              this.activity = true;
              setTimeout(() => {this.activity = false}, 100);
          } 
        },

        methods: {
          sendValue() {
              this.msg = {
                "id": this.id,
                "value": this.displayValue
              };
              
              EventBus.$emit('sliderChanged', this.msg);
              this.valueSent = true;
              this.activity = true;
              setTimeout(() => { this.activity = false }, 100);                
          }
       },

       computed:{
        generateCardSize:function(){
          if (this.type == 2) {
            return "is-4";
          }else if (this.type == 3) {
            return "is-4";
          }else{
            return "is-2";
          }
        },

        getSliderOpts:function(){
          let opts = {
            dotSize: 30,
            width: 15,
            height: 0,
            contained: false,
            data: null,
            direction:"ltr",
            height:20,
            min: 0,
            max: 100,
            interval: 1,
            disabled: false,
            clickable: true,
            duration: 0.5,
            adsorb: false,
            lazy: false,
            tooltip: 'focus',
            tooltipPlacement: 'top',
            useKeyboard: false,
            enableCross: true,
            fixed: false,
            minRange: 0,
            maxRange: 100,
            order: true,
            marks: false,
            dotOptions: void 0,
            process: true,
            dotStyle: void 0,
            railStyle: void 0,
            processStyle: void 0,
            tooltipStyle: void 0,
            stepStyle: void 0,
            stepActiveStyle: void 0,
            labelStyle: void 0,
            labelActiveStyle: void 0
          };

          if(this.type == 0 ) {
              opts.direction = "btt";
              opts.height = 180;
              opts.width = 15;
          } else if (this.type == 1) {
              opts.direction = "ttb";
              opts.height = 180;
              opts.width = 15;
          } else if (this.type == 2) {
              opts.direction = "ltr";
              opts.height = 15;
              opts.width = 200;
          } else if (this.type == 3) {
              opts.direction = "rtl";
              opts.height = 15;
              opts.width = 200;
          }

          return opts;
        }
       },

       mounted(){
          setTimeout(() => { this.activity = false }, 500);
       }
    }
</script>

<style>

</style>