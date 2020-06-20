<template>
  <div class="columns page-columns">
    <!-- Made by Ayush Sharma -->
    <!-- ESP-DASH V3 | 25-01-2019 -->
    <!-- GitHub Profile: https://github.com/ayushsharma82 -->
    <div class="column is-4-tablet is-3-desktop is-one-fifth-fullhd page-sidebar">
      <div class="section">
        <navbar :connected="ws.connected" :stats="stats"></navbar>
      </div>
    </div>
    <div class="column page-content">
      <div class="container is-hidden-tablet" style="margin: 0.8rem 0rem;">
        <div class="sicon is-inline align-middle" style="margin-left: 0.8rem">
          <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
            xmlns:xlink="http://www.w3.org/1999/xlink">
            <g id="Stockholm-icons-/-Code-/-Right-circle" stroke="none" stroke-width="1" fill="none"
              fill-rule="evenodd">
              <rect id="bound" x="0" y="0" width="24" height="24"></rect>
              <circle id="Oval-5" fill="#335EEA" opacity="0.3" cx="12" cy="12" r="10"></circle>
              <path
                d="M7.96323356,15.1775211 C7.62849853,15.5122561 7.08578582,15.5122561 6.75105079,15.1775211 C6.41631576,14.842786 6.41631576,14.3000733 6.75105079,13.9653383 L11.8939067,8.82248234 C12.2184029,8.49798619 12.7409054,8.4866328 13.0791905,8.79672747 L18.2220465,13.5110121 C18.5710056,13.8308912 18.5945795,14.3730917 18.2747004,14.7220508 C17.9548212,15.0710098 17.4126207,15.0945838 17.0636617,14.7747046 L12.5257773,10.6149773 L7.96323356,15.1775211 Z"
                id="Path-94" fill="#335EEA"
                transform="translate(12.500001, 12.000001) rotate(-270.000000) translate(-12.500001, -12.000001) ">
              </path>
            </g>
          </svg>
        </div>
        <span class="is-inline" style="font-weight: 600; font-size: 1.1rem; vertical-align: top;">&nbsp;
          {{ $route.name }} </span>
      </div>
      <div class="container" style="margin: 1rem 0rem;">
        <transition name="fade" mode="out-in">
          <router-view :cards="cards" :stats="stats" />
        </transition>
      </div>
    </div>
  </div>
</template>

<script>
  import EventBus from './event-bus.js';
  import Socket from './socket';
  import Navbar from './components/Navbar';

  export default {
    components: {
      Navbar
    },

    data() {
      return {
        ws: {
          url: "",
          connected: false
        },
        stats: {
          enabled: false,
          releaseTag: null,
          sdk: null,
          chipId: null,
          sketchHash: null,
          macAddress: null,
          freeHeap: null,
          heapFragmentation: null,
          wifiMode: null,
          wifiSignal: null
        },
        cards: {
          temperature: [],
          humidity: [],
          status: [],
          button: [],
          number: [],
          lineChart: [],
          gauge: [],
          slider: []
        }
      }
    },

    mounted() {

      Socket.$on("connected", () => {
        this.ws.connected = true;
        Socket.send(JSON.stringify({
          "command": "getLayout"
        }));
      });

      Socket.$on("disconnected", () => {
        this.ws.connected = false;
      });

      Socket.$on("message", (json) => {
        this.ws.connected = true;

        if (json.response === "getLayout") {
          this.cards.temperature = [];
          this.cards.humidity = [];
          this.cards.status = [];
          this.cards.button = [];
          this.cards.number = [];
          this.cards.lineChart = [];
          this.cards.gauge = [];
          this.cards.slider = [];
          this.stats.enabled = json.statistics.enabled;
          if (this.stats.enabled) {
            this.stats.releaseTag = json.statistics.releaseTag;
            this.stats.hardware = json.statistics.hardware;
            this.stats.sdk = json.statistics.sdk;
            this.stats.chipId = json.statistics.chipId;
            this.stats.sketchHash = json.statistics.sketchHash;
            this.stats.macAddress = json.statistics.macAddress;
            this.stats.freeHeap = json.statistics.freeHeap;
            if (json.statistics?.heapFragmentation) {
              this.stats.heapFragmentation = json.statistics.heapFragmentation;
            }
            this.stats.wifiMode = json.statistics.wifiMode;
            this.stats.wifiSignal = json.statistics.wifiSignal;
          }

          json.cards.forEach(card => {
            switch (card.card_type) {
              case "temperature":
                this.cards.temperature.push({
                  id: card.id,
                  name: card.name,
                  value: card.value,
                  value_type: card.value_type
                });
                break;

              case "humidity":
                this.cards.humidity.push({
                  id: card.id,
                  name: card.name,
                  value: card.value
                });
                break;

              case "status":
                this.cards.status.push({
                  id: card.id,
                  name: card.name,
                  value: card.value
                });
                break;

              case "button":
                this.cards.button.push({
                  id: card.id,
                  name: card.name
                });
                break;

              case "number":
                this.cards.number.push({
                  id: card.id,
                  name: card.name,
                  value: card.value
                });
                break;

              case "slider":
                this.cards.slider.push({
                  id: card.id,
                  name: card.name,
                  type: card.type,
                  value: card.value,
                  min: card.value_min,
                  max: card.value_max
                });
                break;

              case "lineChart":
                this.cards.lineChart.push({
                  id: card.id,
                  name: card.name,
                  xAxis: card.x_axis_value,
                  yAxisName: card.y_axis_name,
                  yAxis: card.y_axis_value
                });
                break;

              case "gaugeChart":
                this.cards.gauge.push({
                  id: card.id,
                  name: card.name,
                  value: card.value,
                  max: card.value_max
                });
                break;

              default:
                break;
            }
          });
        }
        // TODO: better rewrite this
        else if (json.response === "updateCards") {
          json.cards.forEach(card => {
            switch (card.response) {
              case "updateLineChart":
                this.cards.lineChart.forEach((chart) => {
                  if (chart.id == card.id) {
                    chart.xAxis = card.x_axis_value;
                    chart.yAxis = card.y_axis_value;
                  }
                });
                break;

              case "updateStatusCard":
                this.cards.status.forEach((data) => {
                  if (data.id == card.id) {
                    data.value = card.value;
                  }
                });
                break;

              case "updateNumberCard":
                this.cards.number.forEach((data) => {
                  if (data.id == card.id) {
                    data.value = card.value;
                  }
                });
                break;

              case "updateTemperatureCard":
                this.cards.temperature.forEach((data) => {
                  if (data.id == card.id) {
                    data.value = card.value;
                  }
                });
                break;

              case "updateHumidityCard":
                this.cards.humidity.forEach((data) => {
                  if (data.id == card.id) {
                    data.value = card.value;
                  }
                });
                break;

              case "updateGaugeChart":
                this.cards.gauge.forEach((data) => {
                  if (data.id == card.id) {
                    data.value = card.value;
                  }
                });

                break;
              case "updateSliderCard":
                this.cards.slider.forEach((data) => {
                  if (data.id == card.id) {
                    data.value = card.value;
                  }
                });
                break;
            }
          });
        } else if (json.response == "updateLayout") {
          Socket.send(JSON.stringify({
            "command": "getLayout"
          }));
        }
      });

      EventBus.$on('buttonClicked', id => {
        Socket.send(JSON.stringify({
          "command": "buttonClicked",
          "id": id
        }));
      });

      EventBus.$on('sliderChanged', msg => {
        Socket.send(JSON.stringify({
          "command": "sliderChanged",
          "id": msg.id,
          "value": msg.value
        }));
      });
    }
  }
</script>

<style lang="scss">
  @import './assets/scss/main.scss';
</style>