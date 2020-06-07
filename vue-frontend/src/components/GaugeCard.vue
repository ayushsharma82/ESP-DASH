<template>
  <div class="column is-6-mobile is-4-tablet is-3-desktop">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <header class="columns is-gapless is-mobile">
          <div class="column is-narrow sicon sicon-xs is-inline has-text-danger align-middle">
            <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
              xmlns:xlink="http://www.w3.org/1999/xlink">
              <g id="Stockholm-icons-/-Media-/-Rec" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                <path opacity="0.7"
                  d="M12,16 C14.209139,16 16,14.209139 16,12 C16,9.790861 14.209139,8 12,8 C9.790861,8 8,9.790861 8,12 C8,14.209139 9.790861,16 12,16 Z M12,20 C7.581722,20 4,16.418278 4,12 C4,7.581722 7.581722,4 12,4 C16.418278,4 20,7.581722 20,12 C20,16.418278 16.418278,20 12,20 Z"
                  id="Oval-6" fill="#335EEA"></path>
              </g>
            </svg>
          </div>
          <p class="column" style="margin-left: 0.5rem; line-height: 1.2;">{{card.name}}</p>
        </header>
        <div class="card-name has-text-dark">
          <doughnut-chart :chart-data="datacollection" :options="options"></doughnut-chart>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import DoughnutChart from './charts/DoughnutChart';

  export default {
    props: ['card'],

    components: {
      DoughnutChart
    },

    data() {
      return {
        activity: true,
        datacollection: {
          labels: [this.card.value],
          datasets: [{
            label: this.card.name,
            backgroundColor: ['#f87979', '#f2f2f2'],
            data: [this.card.value, this.card.max - this.card.value]
          }]
        },
        options: {
          events: [],
          rotation: 1 * Math.PI,
          circumference: 1 * Math.PI,
          layout: {
            padding: {
              left: 0,
              right: 0,
              top: 10,
              bottom: 0
            }
          },
          legend: {
            position: 'bottom',
            labels: {
              // This more specific font property overrides the global property
              fontFamily: "'Quicksand', 'sans-serif'"
            }
          },
          tooltips: {
            bodyFontFamily: "'Quicksand', 'sans-serif'",
            filter: function () {
              return false;
            }
          }
        }
      }
    },

    watch:{
      'card.value':function() {
        this.activity = true;
        setTimeout(() => {this.activity = false}, 100);
      }
    },

    methods: {
      getRandomInt() {
        return Math.floor(Math.random() * (50 - 5 + 1)) + 5
      }
    },

    computed: {
      generateSeries: function () {
        return [this.value];
      },

      generateChartOptions() {
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

    mounted() {
      setTimeout(() => {
        this.activity = false
      }, 500);
    }
  }
</script>