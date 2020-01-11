<template>
    <div class="columns page-columns">
        <!-- Made by Ayush Sharma -->
        <!-- ESP-DASH V3 | 25-01-2019 -->
        <!-- GitHub Profile: https://github.com/ayushsharma82 -->
        <div class="column is-3-tablet is-one-fifth-desktop is-one-fifth-widescreen is-one-fifth-fullhd page-sidebar">
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
        <transition name="fade" mode="out-in">
            <div class="modal" :class="{'is-active': donation.open}" v-if="donation.open">
                <div class="modal-background" @click="donation.open = false"></div>
                <div class="modal-content message-box">
                    <div class="box">
                        <center>
                            <h1 style="font-size: 1.4rem; font-weight: 600;"><b>ESP-DASH V3.0 🎉</b></h1>
                            <br/>
                            <img src="https://media.giphy.com/media/yoJC2GnSClbPOkV0eA/source.gif" width="auto">
                        </center>
                            <br/>
                            <br/>
                            <p>
                                Hi There!
                                <br/>
                                I hope everybody's doing well!
                            </p>
                            <p>
                                <br/>
                                It's been some very busy months for all, but we were working offline on something special! We are glad to announce <b>ESP-DASH V3.0</b>!
                                <br/><br/>
                                This major release fixes <i>most</i> of the previous bugs and issues while maintaining a lesser or equal size to it's previous generation. ESP-DASH V3.0 comes with reworked UI and Core routines ( Thanks to <a href="https://github.com/polaco1782" target="_blank">Cassiano Martin</a>! ). Performance has been improved again with the expertise of Cassiano handling the backend part and me handling the UI part.
                                <br><br>
                                The road doesn't stops here! Help us achieve more by supporting the project on <a href="#" target="_blank">OpenCollective</a>. There are still a lot of components ( charts, buttons, specific utilities etc. ) which are to be added in the library, and all of this requires time and funding.
                                <br/><br/>
                                The progress we have made, wouldn't had been possible without the support of our backers and contributors!. I'll continue developing ESP-DASH as it's the <b>love</b> from the community which drives any maker in this world to support his / her own creation 😉.
                                <br/><br/>
                                <a href="https://opencollective.com/espdash#section-contribute" target="_blank">
                                    <img :src="$collectiveLogo" width=300 />
                                </a>
                                <br/><br/>
                                Regards,
                                <br/>
                                Ayush Sharma <br/>
                                Owner and Maintainer of ESP-DASH
                            </p>
                    </div>
                </div>
                <button class="modal-close is-large" @click="donation.open = false" aria-label="close"></button>
            </div>
        </transition>
        
        <div class="contrifloater" @click="donation.open = true">
            <div class="content">
                <div class="sicon has-text-white">
                    <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
                        xmlns:xlink="http://www.w3.org/1999/xlink">
                        <g id="Stockholm-icons-/-Communication-/-Mail-heart" stroke="none" stroke-width="1" fill="none"
                            fill-rule="evenodd">
                            <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                            <path
                                d="M6,2 L18,2 C18.5522847,2 19,2.44771525 19,3 L19,13 C19,13.5522847 18.5522847,14 18,14 L6,14 C5.44771525,14 5,13.5522847 5,13 L5,3 C5,2.44771525 5.44771525,2 6,2 Z M13.8,4 C13.1562,4 12.4033,4.72985286 12,5.2 C11.5967,4.72985286 10.8438,4 10.2,4 C9.0604,4 8.4,4.88887193 8.4,6.02016349 C8.4,7.27338783 9.6,8.6 12,10 C14.4,8.6 15.6,7.3 15.6,6.1 C15.6,4.96870845 14.9396,4 13.8,4 Z"
                                id="Combined-Shape" fill="#335EEA" opacity="0.3"></path>
                            <path
                                d="M3.79274528,6.57253826 L12,12.5 L20.2072547,6.57253826 C20.4311176,6.4108595 20.7436609,6.46126971 20.9053396,6.68513259 C20.9668779,6.77033951 21,6.87277228 21,6.97787787 L21,17 C21,18.1045695 20.1045695,19 19,19 L5,19 C3.8954305,19 3,18.1045695 3,17 L3,6.97787787 C3,6.70173549 3.22385763,6.47787787 3.5,6.47787787 C3.60510559,6.47787787 3.70753836,6.51099993 3.79274528,6.57253826 Z"
                                id="Combined-Shape" fill="#335EEA"></path>
                        </g>
                    </svg>
                </div>
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
                donation:{
                    open: false
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

                if (json.response == "getLayout") {
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
                        this.stats.sdk = json.statistics.sdk;
                        this.stats.chipId = json.statistics.chipId;
                        this.stats.sketchHash = json.statistics.sketchHash;
                        this.stats.macAddress = json.statistics.macAddress;
                        this.stats.freeHeap = json.statistics.freeHeap;
                        if (json.statistics.hasOwnProperty("heapFragmentation")) {
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
                                    min: card.min,
                                    max: card.max
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
                }
                // TODO: better rewrite this
                else if (json.response == "updateCards") {
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
    @import './styles/custom.scss';
</style>