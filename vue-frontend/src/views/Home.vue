<template>
  <div>
    <div class="container" v-if="cards.length > 0 || charts.length > 0">
      <div class="columns is-mobile is-multiline">
        <generic-card v-for="card in getParticularCards('generic')" :key="card.id" :card="card"></generic-card>
        <temperature-card v-for="card in getParticularCards('temperature')" :key="card.id" :card="card"></temperature-card>
        <humdidity-card v-for="card in getParticularCards('humidity')" :key="card.id" :card="card"></humdidity-card>
        <status-card v-for="card in getParticularCards('status')" :key="card.id" :card="card"></status-card>
        <progress-card v-for="card in getParticularCards('progress')" :key="card.id" :card="card"></progress-card>
        <slider-card v-for="card in getParticularCards('slider')" :key="card.id" :card="card"></slider-card>
        <button-card v-for="card in getParticularCards('button')" :key="card.id" :card="card"></button-card>
      </div>
      <div class="columns is-mobile is-multiline">
        <bar-chart v-for="chart in getParticularCharts('bar')" :key="chart.id" :chart="chart"></bar-chart>
      </div>
    </div>
    <div class="container" v-else>
      <div class="section">
        <div class="row">
          <div class="columns is-centered has-text-centered" style="font-weight: 400; font-size: 18px">
            <div class="column">
              Loading
              <svg width="24px" height="24px" class="spinner" style="vertical-align: middle;" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                  <g id="Stockholm-icons-/-Code-/-Loading" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                      <g id="Group">
                          <polygon id="Shape" points="0 0 24 0 24 24 0 24"></polygon>
                      </g>
                      <path d="M12,4 L12,6 C8.6862915,6 6,8.6862915 6,12 C6,15.3137085 8.6862915,18 12,18 C15.3137085,18 18,15.3137085 18,12 C18,10.9603196 17.7360885,9.96126435 17.2402578,9.07513926 L18.9856052,8.09853149 C19.6473536,9.28117708 20,10.6161442 20,12 C20,16.418278 16.418278,20 12,20 C7.581722,20 4,16.418278 4,12 C4,7.581722 7.581722,4 12,4 Z" id="Oval-3" fill="currentColor" opacity="0.3" transform="translate(12.000000, 12.000000) scale(-1, 1) translate(-12.000000, -12.000000) "></path>
                  </g>
              </svg>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import GenericCard from '@/components/GenericCard.vue';
import TemperatureCard from '@/components/TemperatureCard.vue';
import HumdidityCard from '@/components/HumidityCard.vue';
import StatusCard from '@/components/StatusCard.vue';
import ProgressCard from '@/components/ProgressCard.vue';
import SliderCard from '@/components/SliderCard.vue';
import ButtonCard from '@/components/ButtonCard.vue';

import BarChart from '@/components/BarChart.vue';

export default {
  name: 'home',

  props: ['cards', 'charts'],

  components: {
    GenericCard,
    TemperatureCard,
    HumdidityCard,
    StatusCard,
    ProgressCard,
    ButtonCard,
    SliderCard,
    BarChart
  },

  methods: {
    getParticularCards(type) {
      let cards = [];
      for(let card of this.cards){
        if(card.type === type){
          cards.push(card);
        }
      }
      return cards;
    },
    getParticularCharts(type) {
      let charts = [];
      for(let chart of this.charts){
        if(chart.type === type){
          charts.push(chart);
        }
      }
      return charts;
    }
  }
}
</script>