<template>
<div>
  <div class="section pt-1">
    <div class="container mt-6">
      <navbar />
    </div>
  </div>
  <div class="section pt-2">
    <transition name="fade" mode="out-in">
      <router-view :cards="cards" :charts="charts" :stats="stats" />
    </transition>
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
      cards: [],
      charts: []
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

      if (json.command === "updateLayout") {
        this.stats.enabled = json.statistics.enabled;
        if (this.stats.enabled) {
          this.stats = json.statistics;
        }

        this.cards = [];
        this.charts = [];
        json.cards.forEach(card => {
          this.cards.push({
            id: card.id,
            type: card.type,
            name: card.name,
            value: card.value,
            symbol: card.symbol,
            min: card.value_min,
            max: card.value_max
          });
        });
        json.charts.forEach(chart => {
          this.charts.push({
            id: chart.id,
            type: chart.type,
            name: chart.name,
            x_axis: chart.x_axis,
            y_axis: chart.y_axis,
          });
        });
      } else if (json.command === "updateStats") {
        this.stats.enabled = json.statistics.enabled;
        if (this.stats.enabled) {
          this.stats = json.statistics;
        }
      } else if (json.command === "updateCards") {
        json.cards.forEach(card => {
          for(let existingcard of this.cards) {
            if(existingcard.id === card.id){
              existingcard.symbol = card.symbol;
              existingcard.value = card.value;
            }
          }
        });
        json.charts.forEach(chart => {
          for(let existingchart of this.charts) {
            if(existingchart.id === chart.id){
              existingchart.x_axis = chart.x_axis;
              existingchart.y_axis = chart.y_axis;
              existingchart.y_axis_label = chart.y_axis_label;
            }
          }
        });
      } else if (json.command === "refreshLayout") {
        Socket.send(JSON.stringify({
          "command": "getLayout"
        }));
      }
    });

    EventBus.$on('buttonClicked', data => {
      Socket.send(JSON.stringify({
        "command": "buttonClicked",
        "id": data.id,
        "value": data.value
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