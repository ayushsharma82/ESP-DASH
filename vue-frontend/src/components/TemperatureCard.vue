<template>
  <div class="column is-12-mobile is-4-tablet is-4-desktop is-3-fullhd">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <div class="columns is-mobile">
          <div class="column is-narrow">
            <div class="card-icon pb-3 pt-4 px-4 has-background-danger-light has-text-danger">
              <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                <g id="Stockholm-icons-/-Weather-/-Temperature-half" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                    <polygon id="Shape" points="0 0 24 0 24 24 0 24"></polygon>
                    <path d="M18,16 C18,19.3137085 15.3137085,22 12,22 C8.6862915,22 6,19.3137085 6,16 C6,13.7791529 7.20659589,11.8401214 9,10.8026932 L9,5 C9,3.34314575 10.3431458,2 12,2 C13.6568542,2 15,3.34314575 15,5 L15,10.8026932 C16.7934041,11.8401214 18,13.7791529 18,16 Z M12,4 C11.4477153,4 11,4.44771525 11,5 L11,10 C11,10.5522847 11.4477153,11 12,11 C12.5522847,11 13,10.5522847 13,10 L13,5 C13,4.44771525 12.5522847,4 12,4 Z" id="Combined-Shape" fill="currentColor"></path>
                </g>
              </svg>
            </div>
          </div>
          <div class="column">
            <h6 class="is-size-6 has-text-muted">{{card.name}}</h6>
            <h2 class="is-size-4 has-text-dark has-text-weight-semibold">{{card.value}} <small class="is-size-6">{{card.symbol}}</small></h2>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  props:['card'],
  data(){
    return{
      activity: true
    }
  },
  watch:{
    'card.value':function() {
      this.activity = true;
      setTimeout(() => {this.activity = false}, 100);
    }
  },
  mounted(){
    setTimeout(() => { this.activity = false }, 500);
  }
}
</script>

<style>
.card{
  border-radius: 0.525rem;
}

.card header{
  font-weight: 600;
  font-size: 1.25rem;
}

.card p{
  font-size: 1.15rem;
}

.card-content{
  padding: 1.2rem 1.4rem;
}

.card-content p{
  padding: 0.5rem 0rem 0rem 0.2rem;
}


.card header h4{
  font-weight: 600;
  margin-left: 0.5rem;
}

.card small{
  font-weight: 500;
  line-height: 1.6;
}
</style>
