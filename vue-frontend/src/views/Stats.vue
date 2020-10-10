<template>
  <div>
    <div class="container" v-if="stats.enabled">
      <div class="card">
        <div class="card-content py-6">
          <div class="px-5"><b>Hardware:</b> &nbsp; {{stats.hardware}}</div>
          <hr class="my-4" style="height: 0px"/>
          <div class="px-5"><b>SDK Version:</b> &nbsp; {{stats.sdk}}</div>
          <hr class="my-4" style="height: 0px"/>
          <div class="px-5"><b>Chip ID:</b> &nbsp; {{stats.chipId}}</div>
          <hr class="my-4" style="height: 0px"/>
          <div class="px-5"><b>Free Heap:</b> &nbsp; {{stats.freeHeap}} bytes</div>
          <hr class="my-4" style="height: 0px"/>
          <div v-if="stats.heapFragmentation" class="px-5"><b>Heap Fragmentation:</b> &nbsp; {{stats.heapFragmentation}}</div>
          <hr v-if="stats.heapFragmentation"/>
          <div class="px-5"><b>Sketch Hash:</b> &nbsp; {{stats.sketchHash}}</div>
          <hr class="my-4" style="height: 0px"/>
          <div class="px-5"><b>MAC Address:</b> &nbsp; {{stats.macAddress}}</div>
          <hr class="my-4" style="height: 0px"/>
          <div class="px-5"><b>Connection Type:</b> &nbsp; {{getWifiMode}}</div>
          <hr class="my-4" style="height: 0px"/>
          <div class="px-5"><b>Signal Level (RSSI):</b> &nbsp; {{stats.wifiSignal}}</div>
        </div>
      </div>
    </div>
    <div class="section" v-else>
      <div class="row">
        <div class="columns is-centered has-text-centered" style="font-weight: 400; font-size: 18px">
          <div class="column">
            <div class="sicon sicon-lg align-middle">
              <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
                xmlns:xlink="http://www.w3.org/1999/xlink">
                <g id="Stockholm-icons-/-Code-/-Lock-circle" stroke="none" stroke-width="1" fill="none"
                  fill-rule="evenodd">
                  <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                  <circle id="Oval-5" fill="currentColor" opacity="0.3" cx="12" cy="12" r="10"></circle>
                  <path
                    d="M14.5,11 C15.0522847,11 15.5,11.4477153 15.5,12 L15.5,15 C15.5,15.5522847 15.0522847,16 14.5,16 L9.5,16 C8.94771525,16 8.5,15.5522847 8.5,15 L8.5,12 C8.5,11.4477153 8.94771525,11 9.5,11 L9.5,10.5 C9.5,9.11928813 10.6192881,8 12,8 C13.3807119,8 14.5,9.11928813 14.5,10.5 L14.5,11 Z M12,9 C11.1715729,9 10.5,9.67157288 10.5,10.5 L10.5,11 L13.5,11 L13.5,10.5 C13.5,9.67157288 12.8284271,9 12,9 Z"
                    id="Combined-Shape" fill="currentColor"></path>
                </g>
              </svg>
            </div>
            <br>
            <br>
            Stats are disabled
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import Socket from '../socket';

export default {
  props: ['stats'],

  computed: {
    getWifiMode() {
      switch (this.stats.wifiMode) {
        case 0:
          return "WIFI_AP";
        case 1:
          return "WIFI_STA";
        case 2:
          return "WIFI_AP_STA";
        case 3:
          return "WIFI_OFF";
        default:
          return "NaN";
      }
    }
  },

  mounted(){
    Socket.send(JSON.stringify({
      "command": "getStats"
    }));
  }
}
</script>

<style>

</style>