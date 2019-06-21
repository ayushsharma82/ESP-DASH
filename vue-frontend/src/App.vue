<template>
<div class="section">
    <!-- Made by Ayush Sharma -->
    <!-- ESP-DASH V2 | 25-01-2019 -->
    <!-- GitHub Profile: https://github.com/ayushsharma82 -->
    <navbar :connected="ws.connected"></navbar>
    <transition name="fade" mode="out-in">
        <router-view :cards="cards" :stats="stats" @reboot="rebootMicrocontroller"/>
    </transition>
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

    data(){
        return{
            ws:{
                url: "",
                connected: false
            },
            stats:{
                enabled: false,
                hardware: null,
                chipId: null,
                sketchHash: null,
                macAddress: null,
                freeHeap: null,
                heapFragmentation: null,
                wifiMode: null
            },
            cards:{
                temperature: [],
                humidity: [],
                status: [],
                button: [],
                buttonStatus: [],
                number: [],
                lineChart: [],
                gauge: [],
                slider:[]
            }
        }
    },

    methods:{
        rebootMicrocontroller(){
            Socket.send(JSON.stringify({"command": "reboot"}));
        }
    },

    mounted(){
        
        Socket.$on("connected", () => {
            this.ws.connected = true;
            Socket.send(JSON.stringify({"command":"getLayout"}));
        });

        Socket.$on("disconnected", () => {
            this.ws.connected = false;
        });

        Socket.$on("message", (json) => {
            this.ws.connected = true;

            if(json.response == "getLayout"){
                this.cards.temperature = [];
                this.cards.humidity = [];
                this.cards.status = [];
                this.cards.button = [];
                this.cards.buttonStatus = [];
                this.cards.number = [];
                this.cards.lineChart = [];
                this.cards.gauge = [];
                this.cards.slider = [];
                this.stats.enabled = json.statistics.enabled;
                if(this.stats.enabled){
                    this.stats.hardware = json.statistics.hardware;
                    this.stats.chipId = json.statistics.chipId;
                    this.stats.sketchHash = json.statistics.sketchHash;
                    this.stats.macAddress = json.statistics.macAddress;
                    this.stats.freeHeap = json.statistics.freeHeap;
                    if(json.statistics.hasOwnProperty("heapFragmentation")){
                        this.stats.heapFragmentation = json.statistics.heapFragmentation;
                    }
                    this.stats.wifiMode = json.statistics.wifiMode;
                }
                json.cards.forEach(card => {
                    switch(card.card_type){
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

                        case "buttonStatus":
                            this.cards.buttonStatus.push({
                                id: card.id,
                                name: card.name,
                                value: card.value
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
                                value: card.value
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
                                value: card.value
                            });
                            break;

                        default:
                            break;
                    }
                });
            }else if(json.response == "updateLineChart"){
                this.cards.lineChart.forEach((chart) => {
                    if(chart.id == json.id){
                        chart.xAxis = json.x_axis_value;
                        chart.yAxis = json.y_axis_value;
                    }
                });
            }else if(json.response == "updateStatusCard"){
                this.cards.status.forEach((card) => {
                    if(card.id == json.id){
                        card.value = json.value;
                    }
                });
            }else if(json.response == "updateButtonStatusCard"){
                this.cards.buttonStatus.forEach((card) => {
                    if(card.id == json.id){
                        card.value = json.value;
                    }
                });
            }else if(json.response == "updateNumberCard"){
                this.cards.number.forEach((card) => {
                    if(card.id == json.id){
                        card.value = json.value;
                    }
                });
            }else if(json.response == "updateTemperatureCard"){
                this.cards.temperature.forEach((card) => {
                    if(card.id == json.id){
                        card.value = json.value;
                    }
                });
            }else if(json.response == "updateHumidityCard"){
                this.cards.humidity.forEach((card) => {
                    if(card.id == json.id){
                        card.value = json.value;
                    }
                });
            }else if(json.response == "updateGaugeChart"){
                this.cards.gauge.forEach((card) => {
                    if(card.id == json.id){
                        card.value = json.value;
                    }
                });
            }else if(json.response == "updateSliderCard"){
                this.cards.slider.forEach((card) => {
                    if(card.id == json.id){
                        card.value = json.value;
                    }
                });
            }else if(json.response == "updateLayout"){
                Socket.send(JSON.stringify({"command":"getLayout"}));
            }
        });

        EventBus.$on('buttonClicked', id => {
            Socket.send(JSON.stringify({"command": "buttonClicked", "id": id}));
        });

        EventBus.$on('sliderChanged', msg  => {
            Socket.send(JSON.stringify({"command": "sliderChanged", "id": msg.id, "value": msg.value }));
        });
    }
}
</script>

<style>

.container{
    margin-top: 3rem;
    margin-bottom: 2rem;
}

.button{
    border-radius: 5px !important;
}

.card{
  background-color: #FFF;
  border: none;
  box-shadow: 0px 0px 50px rgba(232,232,232, 0.9);
  text-align: center;
}

.graph-card{
  padding-left: 0;
  padding-right: 0;
  padding-bottom: 0;
}

.card-loader{
    display: block;
    position: absolute;
    left: 0;
    top: 0;
    margin: 15px;
    color: #6c757d !important;
}

.dot{
  display: none;
  width: 7px !important;
  height: 7px !important;
  border-radius: 50%;
  background: #61CBF2;
  vertical-align: middle;
  position: absolute;
  top: 9px;
  right: 10px;
}

.dot.active{
    display: block;
}

.fade-enter-active, .fade-leave-active {
  transition: opacity .3s;
}
.fade-enter, .fade-leave-to /* .fade-leave-active below version 2.1.8 */ {
  opacity: 0;
}

.spinner{
  width: 1.25em;
  height: 1.25em;
  animation-name: spin;
  animation-duration: 5000ms;
  animation-iteration-count: infinite;
  animation-timing-function: linear; 
}

@keyframes spin {
    from {
        transform:rotate(0deg);
    }
    to {
        transform:rotate(360deg);
    }
}
</style>

