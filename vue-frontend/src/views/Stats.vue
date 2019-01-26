<template>
    <div class="container">
        <div class="section" v-if="stats.enabled">
            <div><b>Hardware:</b> &nbsp; {{stats.hardware}}</div> <br/>
            <div><b>Chip ID:</b> &nbsp; {{stats.chipId}}</div> <br/>
            <div><b>Free Heap:</b> &nbsp; {{stats.freeHeap}} bytes</div> <br/>
            <div v-if="stats.heapFragmentation"><b>Heap Fragmentation:</b> &nbsp; {{stats.heapFragmentation}}</div> <br v-if="stats.heapFragmentation"/>
            <div><b>Sketch Hash:</b> &nbsp; {{stats.sketchHash}}</div><br/>
            <div><b>MAC Address:</b> &nbsp; {{stats.macAddress}}</div><br/>
            <div><b>Connection Type:</b> &nbsp; {{getWifiMode}}</div><br/>
            <br/>
            <div><b>Reboot:</b> &nbsp; <button class="button is-danger is-small" @click="$emit('reboot')"><div class="icon"><refresh-ccw-icon></refresh-ccw-icon></div></button></div>
        </div>
        <div class="section" v-else>
            <div class="row">
                <div class="columns is-centered has-text-centered has-text-grey" style="font-weight: 400; font-size: 18px">
                    <div class="column is-3">
                        <br>
                        <br>
                        <lock-icon style="vertical-align:middle;"></lock-icon> &nbsp; Stats are disabled by admin.
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import { RefreshCcwIcon, LockIcon } from 'vue-feather-icons'

export default {
    props:['stats'],
    components:{
        LockIcon,
        RefreshCcwIcon
    },

    computed:{
        getWifiMode(){
            switch(this.stats.wifiMode){
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
    }
}
</script>

<style>

</style>
