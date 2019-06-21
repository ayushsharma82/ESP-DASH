<template>
    <!-- Gauge Card -->
    <div class="column is-3">
      <div class="card">
        <span class="dot" :class="{'active': activity}"></span>
        <div class="graph-card">
          <apexchart type="radialBar" height="320px" :options="generateChartOptions" :series="generateSeries"/>
        </div>
      </div>
    </div>
</template>

<script>
export default {
  props:['id', 'name', 'value'],

  data(){
    return{
      activity: true
    }
  },

  watch: { 
    value: function() {
      this.activity = true;
      setTimeout(() => {this.activity = false}, 100);
    }
  },

  computed:{
    generateSeries: function(){
        return [this.value];
    },

    generateChartOptions(){
        let json = {
          responsive: [{
            breakpoint: undefined,
            options: {},
          }],
          chart: {
              height: 'auto',
              type: 'radialBar',
          },
          series: [this.value],
          labels: [this.name],
        };

        return json;
      }
  },

  mounted(){
    setTimeout(() => { this.activity = false }, 500);
  }
}
</script>

<style scoped>
.card-content .apex-canvas{
    height: 150px !important;
}
</style>
