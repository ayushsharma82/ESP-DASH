<template>
  <div class="column is-12-mobile is-6-tablet is-5-desktop">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <div class="columns is-mobile is-vcentered">
          <div class="column is-narrow has-text-primary">
            <div class="card-icon pb-1 pt-2 px-2 has-background-link-light has-text-link">
              <svg width="24" height="24" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg">
                <g fill="none" fill-rule="evenodd">
                  <path d="M0 0h24v24H0z"></path>
                  <rect fill="currentColor" opacity=".6" x="12" y="4" width="3" height="13" rx="1.5"></rect>
                  <rect fill="currentColor" opacity=".6" x="7" y="9" width="3" height="8" rx="1.5"></rect>
                  <path d="M5 19h15a1 1 0 010 2H4a1 1 0 01-1-1V4a1 1 0 112 0v15z" fill="currentColor"></path>
                  <rect fill="currentColor" opacity=".6" x="17" y="11" width="3" height="6" rx="1.5"></rect>
                </g>
              </svg>
            </div>
          </div>
          <div class="column">
            <h6 class="is-size-6 has-text-muted">{{chart.name}}</h6>
          </div>
        </div>
        <div class="columns">
          <div class="column is-12">
            <bar-chartjs :chart-data="chartData" :options="options" height="200px"></bar-chartjs>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import BarChartjs from './Charts/Bar';

  export default {
    props: ['chart'],

    components: {
      BarChartjs
    },

    data() {
      return {
        activity: true,
        options: {
          responsive: true,
          aspectRatio: 1,
          height: 200,
          legend: {
            display: false
          },
          scales: {
            xAxes: [{
              barPercentage: 0.6,
              gridLines: {
                display: false
              }
            }],
          }
        }
      }
    },

    watch: {
      'chart.x_axis': {
        deep: true,
        handler() {
          if (this.activity === false) {
            this.activity = true;
            setTimeout(() => {
              this.activity = false
            }, 100);
          }
        }
      },
      'chart.y_axis': {
        deep: true,
        handler() {
          if (this.activity === false) {
            this.activity = true;
            setTimeout(() => {
              this.activity = false
            }, 100);
          }
        }
      },
    },

    computed: {
      chartData() {
        return {
          labels: this.chart.x_axis,
          datasets: [{
            label: '',
            backgroundColor: '#4c73f5',
            data: this.chart.y_axis
          }]
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