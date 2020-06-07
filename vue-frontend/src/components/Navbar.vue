<template>
  <div>
    <div class="columns is-gapless is-mobile" style="margin-bottom: 0;">
      <div class="column navbar-logo is-inline align-middle">
        <img
          src="data:image/png;base64,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"
          alt="ESP-DASH" width="140px">
      </div>
      <div class="column is-inline-block is-hidden-tablet has-text-right align-middle">
        <a role="button" class="navbar-burger burger" aria-label="menu" aria-expanded="false"
          :class="{'is-active': open}" data-target="navbarBasicExample" @click.prevent="open = !open">
          <span aria-hidden="true"></span>
          <span aria-hidden="true"></span>
          <span aria-hidden="true"></span>
        </a>
      </div>
    </div>
    <aside class="menu" :class="{ 'is-hidden-mobile': !open }">
      <p class="menu-label">
        General
      </p>
      <ul class="menu-list">
        <li>
          <router-link @click.native="open = false" to="/" exact>
            <span class="sicon">
              <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
                xmlns:xlink="http://www.w3.org/1999/xlink" class="">
                <g id="Stockholm-icons-/-Layout-/-Layout-left-panel-1" stroke="none" stroke-width="1" fill="none"
                  fill-rule="evenodd">
                  <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                  <rect id="Rectangle-7-Copy" fill="currentColor" x="9" y="5" width="13" height="14" rx="1.5">
                  </rect>
                  <rect id="Rectangle-7-Copy-2" fill="currentColor" opacity="0.3" x="2" y="5" width="5" height="14"
                    rx="1">
                  </rect>
                </g>
              </svg>
            </span>

            <span>Dashboard</span>
          </router-link>
        </li>
        <li>
          <router-link @click.native="open = false" to="/statistics">
            <span class="sicon">
              <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
                xmlns:xlink="http://www.w3.org/1999/xlink">
                <g id="Stockholm-icons-/-Layout-/-Layout-4-blocks" stroke="none" stroke-width="1" fill="none"
                  fill-rule="evenodd">
                  <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                  <rect id="Rectangle-7" fill="currentColor" x="4" y="4" width="7" height="7" rx="1.5">
                  </rect>
                  <path
                    d="M5.5,13 L9.5,13 C10.3284271,13 11,13.6715729 11,14.5 L11,18.5 C11,19.3284271 10.3284271,20 9.5,20 L5.5,20 C4.67157288,20 4,19.3284271 4,18.5 L4,14.5 C4,13.6715729 4.67157288,13 5.5,13 Z M14.5,4 L18.5,4 C19.3284271,4 20,4.67157288 20,5.5 L20,9.5 C20,10.3284271 19.3284271,11 18.5,11 L14.5,11 C13.6715729,11 13,10.3284271 13,9.5 L13,5.5 C13,4.67157288 13.6715729,4 14.5,4 Z M14.5,13 L18.5,13 C19.3284271,13 20,13.6715729 20,14.5 L20,18.5 C20,19.3284271 19.3284271,20 18.5,20 L14.5,20 C13.6715729,20 13,19.3284271 13,18.5 L13,14.5 C13,13.6715729 13.6715729,13 14.5,13 Z"
                    id="Combined-Shape" fill="currentColor" opacity="0.3"></path>
                </g>
              </svg>
            </span>
            <span>Statistics</span>
          </router-link>
        </li>
      </ul>
      <!--
            <p class="menu-label">
                Administration
            </p>
            <ul class="menu-list">
                <li>
                    <router-link @click.native="open = false" to="/settings">
                        <span class="sicon">
                            <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1"
                                xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                                <g id="Stockholm-icons-/-Code-/-Settings#4" stroke="none" stroke-width="1" fill="none"
                                    fill-rule="evenodd">
                                    <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                                    <path
                                        d="M18.6225,9.75 L18.75,9.75 C19.9926407,9.75 21,10.7573593 21,12 C21,13.2426407 19.9926407,14.25 18.75,14.25 L18.6854912,14.249994 C18.4911876,14.250769 18.3158978,14.366855 18.2393549,14.5454486 C18.1556809,14.7351461 18.1942911,14.948087 18.3278301,15.0846699 L18.372535,15.129375 C18.7950334,15.5514036 19.03243,16.1240792 19.03243,16.72125 C19.03243,17.3184208 18.7950334,17.8910964 18.373125,18.312535 C17.9510964,18.7350334 17.3784208,18.97243 16.78125,18.97243 C16.1840792,18.97243 15.6114036,18.7350334 15.1896699,18.3128301 L15.1505513,18.2736469 C15.008087,18.1342911 14.7951461,18.0956809 14.6054486,18.1793549 C14.426855,18.2558978 14.310769,18.4311876 14.31,18.6225 L14.31,18.75 C14.31,19.9926407 13.3026407,21 12.06,21 C10.8173593,21 9.81,19.9926407 9.81,18.75 C9.80552409,18.4999185 9.67898539,18.3229986 9.44717599,18.2361469 C9.26485393,18.1556809 9.05191298,18.1942911 8.91533009,18.3278301 L8.870625,18.372535 C8.44859642,18.7950334 7.87592081,19.03243 7.27875,19.03243 C6.68157919,19.03243 6.10890358,18.7950334 5.68746499,18.373125 C5.26496665,17.9510964 5.02757002,17.3784208 5.02757002,16.78125 C5.02757002,16.1840792 5.26496665,15.6114036 5.68716991,15.1896699 L5.72635306,15.1505513 C5.86570889,15.008087 5.90431906,14.7951461 5.82064513,14.6054486 C5.74410223,14.426855 5.56881236,14.310769 5.3775,14.31 L5.25,14.31 C4.00735931,14.31 3,13.3026407 3,12.06 C3,10.8173593 4.00735931,9.81 5.25,9.81 C5.50008154,9.80552409 5.67700139,9.67898539 5.76385306,9.44717599 C5.84431906,9.26485393 5.80570889,9.05191298 5.67216991,8.91533009 L5.62746499,8.870625 C5.20496665,8.44859642 4.96757002,7.87592081 4.96757002,7.27875 C4.96757002,6.68157919 5.20496665,6.10890358 5.626875,5.68746499 C6.04890358,5.26496665 6.62157919,5.02757002 7.21875,5.02757002 C7.81592081,5.02757002 8.38859642,5.26496665 8.81033009,5.68716991 L8.84944872,5.72635306 C8.99191298,5.86570889 9.20485393,5.90431906 9.38717599,5.82385306 L9.49484664,5.80114977 C9.65041313,5.71688974 9.7492905,5.55401473 9.75,5.3775 L9.75,5.25 C9.75,4.00735931 10.7573593,3 12,3 C13.2426407,3 14.25,4.00735931 14.25,5.25 L14.249994,5.31450877 C14.250769,5.50881236 14.366855,5.68410223 14.552824,5.76385306 C14.7351461,5.84431906 14.948087,5.80570889 15.0846699,5.67216991 L15.129375,5.62746499 C15.5514036,5.20496665 16.1240792,4.96757002 16.72125,4.96757002 C17.3184208,4.96757002 17.8910964,5.20496665 18.312535,5.626875 C18.7350334,6.04890358 18.97243,6.62157919 18.97243,7.21875 C18.97243,7.81592081 18.7350334,8.38859642 18.3128301,8.81033009 L18.2736469,8.84944872 C18.1342911,8.99191298 18.0956809,9.20485393 18.1761469,9.38717599 L18.1988502,9.49484664 C18.2831103,9.65041313 18.4459853,9.7492905 18.6225,9.75 Z"
                                        id="Combined-Shape" fill="currentColor" opacity="0.3"></path>
                                    <path
                                        d="M12,15 C13.6568542,15 15,13.6568542 15,12 C15,10.3431458 13.6568542,9 12,9 C10.3431458,9 9,10.3431458 9,12 C9,13.6568542 10.3431458,15 12,15 Z"
                                        id="Path" fill="currentColor"></path>
                                </g>
                            </svg>
                        </span>
                        <span>Settings</span>
                    </router-link>
                </li>
            </ul>
            -->
      <p class="menu-label">
        Info
      </p>
      <ul class="menu-list">
        <li>
          <router-link @click.native="open = false" to="/contribute">
            <span class="sicon">
              <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
                xmlns:xlink="http://www.w3.org/1999/xlink">
                <g id="Stockholm-icons-/-Code-/-Compiling" stroke="none" stroke-width="1" fill="none"
                  fill-rule="evenodd">
                  <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                  <path
                    d="M2.56066017,10.6819805 L4.68198052,8.56066017 C5.26776695,7.97487373 6.21751442,7.97487373 6.80330086,8.56066017 L8.9246212,10.6819805 C9.51040764,11.267767 9.51040764,12.2175144 8.9246212,12.8033009 L6.80330086,14.9246212 C6.21751442,15.5104076 5.26776695,15.5104076 4.68198052,14.9246212 L2.56066017,12.8033009 C1.97487373,12.2175144 1.97487373,11.267767 2.56066017,10.6819805 Z M14.5606602,10.6819805 L16.6819805,8.56066017 C17.267767,7.97487373 18.2175144,7.97487373 18.8033009,8.56066017 L20.9246212,10.6819805 C21.5104076,11.267767 21.5104076,12.2175144 20.9246212,12.8033009 L18.8033009,14.9246212 C18.2175144,15.5104076 17.267767,15.5104076 16.6819805,14.9246212 L14.5606602,12.8033009 C13.9748737,12.2175144 13.9748737,11.267767 14.5606602,10.6819805 Z"
                    id="Combined-Shape" fill="currentColor" opacity="0.3"></path>
                  <path
                    d="M8.56066017,16.6819805 L10.6819805,14.5606602 C11.267767,13.9748737 12.2175144,13.9748737 12.8033009,14.5606602 L14.9246212,16.6819805 C15.5104076,17.267767 15.5104076,18.2175144 14.9246212,18.8033009 L12.8033009,20.9246212 C12.2175144,21.5104076 11.267767,21.5104076 10.6819805,20.9246212 L8.56066017,18.8033009 C7.97487373,18.2175144 7.97487373,17.267767 8.56066017,16.6819805 Z M8.56066017,4.68198052 L10.6819805,2.56066017 C11.267767,1.97487373 12.2175144,1.97487373 12.8033009,2.56066017 L14.9246212,4.68198052 C15.5104076,5.26776695 15.5104076,6.21751442 14.9246212,6.80330086 L12.8033009,8.9246212 C12.2175144,9.51040764 11.267767,9.51040764 10.6819805,8.9246212 L8.56066017,6.80330086 C7.97487373,6.21751442 7.97487373,5.26776695 8.56066017,4.68198052 Z"
                    id="Combined-Shape" fill="currentColor"></path>
                </g>
              </svg>
            </span>
            <span>Contribute</span>
          </router-link>
        </li>
        <li>
          <router-link @click.native="open = false" to="/licensing">
            <span class="sicon">
              <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg"
                xmlns:xlink="http://www.w3.org/1999/xlink">
                <g id="Stockholm-icons-/-Code-/-Github" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                  <rect id="Rectangle-5" x="0" y="0" width="24" height="24"></rect>
                  <path
                    d="M16.5428932,17.4571068 L11,11.9142136 L11,4 C11,3.44771525 11.4477153,3 12,3 C12.5522847,3 13,3.44771525 13,4 L13,11.0857864 L17.9571068,16.0428932 L20.1464466,13.8535534 C20.3417088,13.6582912 20.6582912,13.6582912 20.8535534,13.8535534 C20.9473216,13.9473216 21,14.0744985 21,14.2071068 L21,19.5 C21,19.7761424 20.7761424,20 20.5,20 L15.2071068,20 C14.9309644,20 14.7071068,19.7761424 14.7071068,19.5 C14.7071068,19.3673918 14.7597852,19.2402148 14.8535534,19.1464466 L16.5428932,17.4571068 Z"
                    id="Combined-Shape" fill="currentColor"></path>
                  <path
                    d="M7.24478854,17.1447885 L9.2464466,19.1464466 C9.34021479,19.2402148 9.39289321,19.3673918 9.39289321,19.5 C9.39289321,19.7761424 9.16903559,20 8.89289321,20 L3.52893218,20 C3.25278981,20 3.02893218,19.7761424 3.02893218,19.5 L3.02893218,14.136039 C3.02893218,14.0034307 3.0816106,13.8762538 3.17537879,13.7824856 C3.37064094,13.5872234 3.68722343,13.5872234 3.88248557,13.7824856 L5.82567301,15.725673 L8.85405776,13.1631936 L10.1459422,14.6899662 L7.24478854,17.1447885 Z"
                    id="Combined-Shape" fill="currentColor" opacity="0.3"></path>
                </g>
              </svg>
            </span>
            <span>Licensing</span>
          </router-link>
        </li>
      </ul>
      <br />
      <div>
        <div class="control">
          <div class="tags has-addons" v-if="stats.enabled">
            <span class="tag is-rounded is-dark">Version</span>
            <span class="tag is-rounded is-info">{{stats.releaseTag}}</span>
          </div>
          <div class="tags has-addons" v-if="showUpdateTag">
            <a :href="update.url">
              <span class="tag is-rounded is-dark">Update Available</span>
              <span class="tag is-rounded is-success">{{update.releaseTag}}</span>
            </a>
          </div>
        </div>
      </div>
    </aside>
  </div>
</template>

<script>
  export default {
    props: ['connected', 'stats'],

    data() {
      return {
        open: false,
        update: {
          retrieved: false,
          releaseTag: 'NaN',
          url: '#'
        }
      }
    },

    mounted() {
      // Check for new releases and show update tag
      let that = this;
      let xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          let res = JSON.parse(this.responseText);
          that.update.releaseTag = res.tag_name;
          that.update.url = res.html_url;
          that.update.retrieved = true;
        }
      };
      xhttp.open("GET", "https://api.github.com/repos/ayushsharma82/ESP-DASH/releases/latest", true);
      xhttp.send();
    },

    computed: {
      showUpdateTag: function () {
        if (this.stats.enabled === true && this.update.retrieved === true && this.stats.releaseTag !== this.update
          .releaseTag) {
          return true;
        } else {
          return false;
        }
      }
    }
  }
</script>

<style lang="scss">
  .menu-list svg {
    vertical-align: middle;
    margin-right: 1rem;
  }

  .menu-list svg {
    vertical-align: middle;
  }


  .menu-list a {
    color: #A8A8AD;
    letter-spacing: 0.8px !important;
    font-weight: 500;
  }

  .menu-list a:hover {
    background-color: transparent;
  }

  .menu-list a.is-active {
    font-weight: 600;
  }

  .navbar-burger:focus {
    outline: none;
    text-decoration: none;
    background: transparent;
  }
</style>