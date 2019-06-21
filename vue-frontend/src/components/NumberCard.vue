<template>
    <!-- Number Card -->
    <div class="column is-3">
      <div class="card">
        <span class="dot" :class="{'active': activity}"></span>
        <div class="card-content">
          <header><h5>{{name}}</h5></header>
          <p><b>{{value}}</b></p>
        </div>
      </div>
    </div>
</template>

<script>
export default {
  props:['id', 'name', 'value'],

  data(){
    return{
      activity: true
    }
  },

  watch: {
      value: function() {
      this.activity = true;
      setTimeout(() => {this.activity = false}, 100);
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
</style>
