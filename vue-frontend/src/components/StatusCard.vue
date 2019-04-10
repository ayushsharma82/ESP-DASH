<template>
  <!-- Temperature Card -->
  <div class="column is-2">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <header>
          <h5>{{name}}</h5>
        </header>
        <Br />
        <p>
          <x-circle-icon v-if="value == 0"></x-circle-icon>
          <check-circle-icon class="active" v-else-if="value == 1"></check-circle-icon>
          <alert-octagon-icon class="danger" v-else-if="value == 2"></alert-octagon-icon>
          <pause-circle-icon class="warning" v-else-if="value == 3"></pause-circle-icon>
        </p>
      </div>
    </div>
  </div>
</template>

<script>
  import {
    CheckCircleIcon,
    XCircleIcon,
    AlertOctagonIcon,
    PauseCircleIcon
  } from 'vue-feather-icons';

  export default {
    props: ['name', 'value'],
    components: {
      CheckCircleIcon,
      XCircleIcon,
      AlertOctagonIcon,
      PauseCircleIcon
    },

    data() {
      return {
        activity: true
      }
    },
    watch: {
      value: function () {
        this.activity = true;
        setTimeout(() => {
          this.activity = false
        }, 100);
      }
    },

    mounted() {
      setTimeout(() => {
        this.activity = false
      }, 500);
    }
  }
</script>

<style scoped>
  .card svg {
    width: 64px;
    height: 64px;
    color: grey;
  }

  .card svg.active {
    color: chartreuse;
  }

  .card svg.danger {
    color: crimson;
  }

  .card svg.warning {
    color: rgb(221, 221, 59);
  }
</style>