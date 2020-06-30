<template>
  <div class="column is-6-mobile is-4-tablet is-3-desktop">
    <div class="card">
      <span class="dot" :class="{'active': activity}"></span>
      <div class="card-content">
        <p class="card-name has-text-dark">{{card.name}}</p>
        <header class="columns is-gapless is-mobile">
        </header>
          <div id="Table">
            <table>
              <thead>
                  <tr>
                      <th v-for="header in headers" :key="header.id">{{header}}</th>
                  </tr>
              </thead>
              <tbody>
                  <tr v-for="row in rows" :key="row.id">
                      <td v-for="element in row" :key="element.id">{{element}}</td>
                  </tr>
              </tbody>
            </table>
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
  computed: {
    "lines": function lines() {
      return this.card.value.split(';');
    },
    "headers": function headers() {
      return this.lines[0].split(',');
    },
    "rows": function rows() {
      var datalines = this.lines;
      datalines.shift();
      var data = [];
      datalines.forEach(line => {
        data.push(line.split(','));
      });
      return data;
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
table {
  width: 100%;
  border-radius:6px;
  -moz-border-radius:6px;
}

table th {
  background-color: #4CAF50;
  color: white;
  padding: 5px 5px 5px 10px;
  text-align: center;
  border: 1px solid white;
}

td {
  padding: 0 15px;
  border: 1px solid rgb(175, 175, 175);
}

tr:nth-child(even) {
  background-color: #f2f2f2;
}

/* the first 'th' within the first 'tr' of the 'thead': */
thead tr:first-child th:first-child {
    border-radius: 10px 0 0 5px;
}
/* the last 'th' within the first 'tr' of the 'thead': */
thead tr:first-child th:last-child {
    border-radius: 0 10px 5px 0;
}
</style>