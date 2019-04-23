<template>
    <!-- Temperature Card -->
    <div class="column is-3">
      <div class="card">
        <span class="dot" :class="{'active': activity}"></span>
        <div class="card-content">
          <header><h5>{{name}}</h5></header>
          <p><b>{{value}}<small>{{getSymbol}}</small></b></p>
        </div>
      </div>
    </div>
</template>

<script>
export default {
  props:['name', 'type', 'value'],
  data(){
    return{
      activity: true
    }
  },
  watch:{
      value:function() {
      this.activity = true;
      setTimeout(() => {this.activity = false}, 100);
    }
  },
  computed:{
    getSymbol(){
      switch(this.type){
        case 0:
          return "°C"; // Celsius
        case 1:
          return "°F";  // Fahrenheit
        case 2:
          return "K"; // Kelvin
        case 3:
          return "°R"; // Rakine
        case 4:
          return "°De"; // Delisle
        case 5:
          return "°N"; // Newton
        default:
          return "°C";
      }
    }
  },

  mounted(){
    setTimeout(() => { this.activity = false }, 500);
  }
}
</script>

<style scoped>
.card p{
  font-size: 4rem;
}

.card small{
  vertical-align: top;
  font-size: 2.45rem;
}
</style>
