<template>
    <!-- Graph Card -->
    <div class="column is-4">
      <div class="card">
        <span class="dot" :class="{'active': activity}"></span>
        <div class="card-content graph-card">
          <header><h5>{{name}}</h5></header>
          <div><apexchart height="200px" type="line" :options="generateChartOptions" :series="generateSeries"></apexchart></div>
        </div>
      </div>
    </div>
</template>

<script>
export default {
  props:['id', 'name', 'xAxis', 'yAxisName', 'yAxis'],

  data: function() {
    return {
      activity: true
    }
  },

  watch: {
      yAxis: function() {
      this.activity = true;
      setTimeout(() => {this.activity = false}, 100);
    }
  },

  computed:{
    generateSeries(){
      let json = [{
        'name': this.yAxisName,
        'type': 'line',
        'data': this.yAxis
      }];

      return json;
    },

    generateChartOptions(){
      let json = {
        breakpoint: undefined,
        grid: {
            show: false,
        },
        chart: {
            id: this.id,
            toolbar: {
              show: false,
            }
        },
        stroke: {
          curve: 'smooth'
        },
        fill:{
          type:'solid',
          opacity: [0.35, 1],
        },
        markers: {
          size: 0
        },
        xaxis: {
            categories: this.xAxis
        }
      };

      return json;
    }
  },

  mounted(){
    setTimeout(() => { this.activity = false }, 500);
  }
}
</script>

<style>

</style>
