<template>
  <div>
      <div class="container">
        <div class="columns is-multiline">
          <number-card v-for="card in cards.number" :key="card.id" :name="card.name" :value="card.value"></number-card>
          <temperature-card v-for="card in cards.temperature" :key="card.id" :name="card.name" :value="card.value" :type="card.value_type"></temperature-card>
          <humdidity-card v-for="card in cards.humidity" :key="card.id" :name="card.name" :value="card.value"></humdidity-card>
          <status-card v-for="card in cards.status" :key="card.id" :name="card.name" :value="card.value"></status-card>
          <button-card v-for="card in cards.button" :key="card.id" :id="card.id" :name="card.name"></button-card>
          <buttonStatus-card v-for="card in cards.buttonStatus" :key="card.id" :id="card.id" :name="card.name" :value="card.value"></buttonStatus-card>
        </div>
        <br/>
        <div class="columns is-multiline">
          <slider-card v-for="card in cards.slider" :key="card.id" :id="card.id" :name="card.name" :value="card.value" :type="card.type"></slider-card>
        </div>
        <br/>
        <div class="columns is-multiline">
          <line-chart v-for="chart in cards.lineChart" :key="chart.id" :id="chart.id" :name="chart.name" :xAxis="chart.xAxis" :yAxisName="chart.yAxisName" :yAxis="chart.yAxis"></line-chart>
        </div>
        <br/>
        <div class="columns is-multiline">
          <gauge-card v-for="card in cards.gauge" :key="card.id" :name="card.name" :value="card.value"></gauge-card>
        </div>
    </div>
    <div class="container" v-if="totalNumOfCards == 0">
      
    </div>
  </div>
</template>

<script>
import TemperatureCard from '@/components/TemperatureCard.vue';
import HumdidityCard from '@/components/HumidityCard.vue';
import NumberCard from '@/components/NumberCard.vue';
import StatusCard from '@/components/StatusCard.vue';
import ButtonCard from '@/components/ButtonCard.vue';
import ButtonStatusCard from '@/components/ButtonStatusCard.vue';
import LineChart from '@/components/LineChart.vue';
import GaugeCard from '@/components/GaugeCard.vue';
import SliderCard from '@/components/SliderCard.vue';

export default {
  name: 'home',

  props:['cards'],
  
  components: {
    TemperatureCard,
    HumdidityCard,
    NumberCard,
    StatusCard,
    ButtonCard,
    ButtonStatusCard,
    LineChart,
    GaugeCard,
    SliderCard
  },

  computed: {
    totalNumOfCards(){
      let num = 0;
      num = num + this.cards.temperature.length;
      num = num + this.cards.humidity.length;
      num = num + this.cards.number.length;
      num = num + this.cards.status.length;
      num = num + this.cards.button.length;
      num = num + this.cards.buttonStatus.length;
      num = num + this.cards.slider.length;
      num = num + this.cards.lineChart.length;
      return num;
    }
  }  
}
</script>

