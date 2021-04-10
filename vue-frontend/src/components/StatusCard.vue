<template>
  <div class="column is-12-mobile is-4-tablet is-4-desktop is-3-fullhd">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <div class="columns is-mobile">
          <div class="column is-narrow">
            <div class="card-icon pb-3 pt-4 px-4 has-background-success-light has-text-success" v-if="card.symbol === 'success'">
              <svg width="24" height="24" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><g fill="none" fill-rule="evenodd"><path d="M0 0h24v24H0z"></path><circle fill="currentColor" opacity=".3" cx="12" cy="12" r="10"></circle><path d="M16.769 7.818a1 1 0 011.462 1.364l-7 7.5a1 1 0 01-1.382.077l-3.5-3a1 1 0 011.302-1.518l2.772 2.376 6.346-6.8z" fill="currentColor"></path></g></svg>
            </div>
            <div class="card-icon pb-3 pt-4 px-4 has-background-danger-light has-text-danger" v-else-if="card.symbol === 'danger'">
              <svg width="24" height="24" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><g fill="none" fill-rule="evenodd"><path d="M0 0h24v24H0z"></path><circle fill="currentColor" opacity=".3" cx="12" cy="12" r="10"></circle><path d="M12.036 10.621l2.828-2.828a1 1 0 011.414 1.414l-2.828 2.829 2.828 2.828a1 1 0 01-1.414 1.414l-2.828-2.828-2.829 2.828a1 1 0 11-1.414-1.414l2.828-2.828-2.828-2.829a1 1 0 011.414-1.414l2.829 2.828z" fill="currentColor"></path></g></svg>
            </div>
            <div class="card-icon pb-3 pt-4 px-4 has-background-warning-light has-text-warning" v-else-if="card.symbol === 'warning'">
              <svg width="24" height="24" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><g fill="none" fill-rule="evenodd"><path d="M0 0h24v24H0z"></path><circle fill="currentColor" opacity=".3" cx="12" cy="12" r="10"></circle><rect fill="currentColor" x="11" y="7" width="2" height="8" rx="1"></rect><rect fill="currentColor" x="11" y="16" width="2" height="2" rx="1"></rect></g></svg>
            </div>
            <div class="card-icon pb-3 pt-4 px-4 has-background-grey-dark has-text-white" v-else>
              <svg width="24" height="24" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><g fill="none" fill-rule="evenodd"><path d="M0 0h24v24H0z"></path><circle fill="currentColor" opacity=".3" cx="12" cy="12" r="10"></circle><rect fill="currentColor" x="11" y="10" width="2" height="7" rx="1"></rect><rect fill="currentColor" x="11" y="7" width="2" height="2" rx="1"></rect></g></svg>
            </div>
          </div>
          <div class="column">
            <h6 class="is-size-6 has-text-muted">{{card.name}}</h6>
            <h2 class="is-size-4 has-text-dark has-text-weight-semibold">{{card.value}}</h2>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  export default {
    props: ['card'],

    data() {
      return {
        activity: true
      }
    },

    watch:{
      'card.value':function() {
        this.activity = true;
        setTimeout(() => {this.activity = false}, 100);
      },
      'card.symbol':function() {
        this.activity = true;
        setTimeout(() => {this.activity = false}, 100);
      },
    },

    mounted() {
      setTimeout(() => {
        this.activity = false
      }, 500);
    }
  }
</script>