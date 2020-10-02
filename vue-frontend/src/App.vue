<template>
<div>
  <div class="section pt-1">
    <div class="container mt-6">
      <navbar />
    </div>
  </div>
  <div class="section pt-2">
    <transition name="fade" mode="out-in">
      <router-view :cards="cards" :stats="stats" />
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
        cards: [{
          id: 1,
          type: "number",
          value: 1234,
          name: 'Random Number',
          symbol: ''
        },
        {
          id: 2,
          type: "temperature",
          value: 12,
          name: 'Temperature',
          symbol: '°C'
        },
        {
          id: 3,
          type: "humidity",
          value: 55,
          name: 'Humidity',
          symbol: '%'
        },
        {
          id: 4,
          type: "status",
          value: "Working",
          name: 'Status',
          symbol: 'success'
        },
        {
          id: 4,
          type: "slider",
          name: 'Slider',
          value: 4,
          value_min: 0,
          value_max: 100,
          symbol: '%'
        },
        {
          id: 5,
          type: "button",
          name: "Button",
          value: true
        }]
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

        if (json.response == "getLayout") {
          this.stats.enabled = json.statistics.enabled;
          if (this.stats.enabled) {
            this.stats = json.statistics;
          }

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
        } else if (json.response == "updateCards") {
          json.cards.forEach(card => {
            for(let existingcard of this.cards) {
              if(existingcard.id === card.id){
                existingcard.value = card.value;
              }
            }
          });
        } else if (json.response == "updateLayout") {
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