<template>
    <div>
        <div class="columns is-gapless is-mobile" style="margin-bottom: 0;">
            <div class="column navbar-logo is-inline align-middle">
                <svg id="Layer_1" data-name="Layer 1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
                    <g id="Stockholm-icons-_-Home-_-Deer" data-name="Stockholm-icons-/-Home-/-Deer">
                        <rect id="bound" fill="none" width="24" height="24" />
                        <path id="Combined-Shape" fill="#384c74" opacity="0.3" isolation="isolate"
                            d="M22,8.19a1,1,0,0,1-.47.67l-5,3A1,1,0,0,1,16,12H8a1,1,0,0,1-.51-.14l-5-3A1,1,0,0,1,2,8.19l-1-5a1,1,0,0,1,2-.4L3.61,6,6.29,3.29A1,1,0,0,1,7.71,4.71L4.61,7.8,8.28,10h7.44l3.67-2.2-3.1-3.09a1,1,0,0,1,1.42-1.42L20.39,6,21,2.8a1,1,0,0,1,2,.4Zm-6.93.7A1,1,0,0,1,16,7.11l3,1.5A1,1,0,0,1,19,10.36l-2.5,1.5A1,1,0,0,1,16,12H8a1,1,0,0,1-.51-.14L5,10.36A1,1,0,0,1,5,8.64l2.5-1.5a1,1,0,1,1,1,1.72L7.44,9.5l.84.5h7.44l.7-.42Z" />
                        <path id="Rectangle-192" fill="#384c74"
                            d="M9.86,10h4.28A2,2,0,0,1,16,12.68l-2.68,7.38A1.43,1.43,0,0,1,12,21h0a1.43,1.43,0,0,1-1.34-.94L8,12.68A2,2,0,0,1,9.86,10Z" />
                    </g>
                </svg>
            </div>
            <div class="column is-inline-block is-hidden-tablet has-text-right align-middle">
                <a role="button" class="navbar-burger burger" aria-label="menu" aria-expanded="false" :class="{'is-active': open}"
                    data-target="navbarBasicExample" @click.prevent="open = !open">
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
                            <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1"
                                xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" class="">
                                <g id="Stockholm-icons-/-Layout-/-Layout-left-panel-1" stroke="none" stroke-width="1"
                                    fill="none" fill-rule="evenodd">
                                    <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                                    <rect id="Rectangle-7-Copy" fill="#335EEA" x="9" y="5" width="13" height="14"
                                        rx="1.5">
                                    </rect>
                                    <rect id="Rectangle-7-Copy-2" fill="#335EEA" opacity="0.3" x="2" y="5" width="5"
                                        height="14" rx="1"></rect>
                                </g>
                            </svg>
                        </span>

                        <span>Dashboard</span>
                    </router-link>
                </li>
                <li>
                    <router-link @click.native="open = false" to="/statistics">
                        <span class="sicon">
                            <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1"
                                xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                                <g id="Stockholm-icons-/-Layout-/-Layout-4-blocks" stroke="none" stroke-width="1"
                                    fill="none" fill-rule="evenodd">
                                    <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                                    <rect id="Rectangle-7" fill="#335EEA" x="4" y="4" width="7" height="7" rx="1.5">
                                    </rect>
                                    <path
                                        d="M5.5,13 L9.5,13 C10.3284271,13 11,13.6715729 11,14.5 L11,18.5 C11,19.3284271 10.3284271,20 9.5,20 L5.5,20 C4.67157288,20 4,19.3284271 4,18.5 L4,14.5 C4,13.6715729 4.67157288,13 5.5,13 Z M14.5,4 L18.5,4 C19.3284271,4 20,4.67157288 20,5.5 L20,9.5 C20,10.3284271 19.3284271,11 18.5,11 L14.5,11 C13.6715729,11 13,10.3284271 13,9.5 L13,5.5 C13,4.67157288 13.6715729,4 14.5,4 Z M14.5,13 L18.5,13 C19.3284271,13 20,13.6715729 20,14.5 L20,18.5 C20,19.3284271 19.3284271,20 18.5,20 L14.5,20 C13.6715729,20 13,19.3284271 13,18.5 L13,14.5 C13,13.6715729 13.6715729,13 14.5,13 Z"
                                        id="Combined-Shape" fill="#335EEA" opacity="0.3"></path>
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
                                        id="Combined-Shape" fill="#335EEA" opacity="0.3"></path>
                                    <path
                                        d="M12,15 C13.6568542,15 15,13.6568542 15,12 C15,10.3431458 13.6568542,9 12,9 C10.3431458,9 9,10.3431458 9,12 C9,13.6568542 10.3431458,15 12,15 Z"
                                        id="Path" fill="#335EEA"></path>
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
                            <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1"
                                xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                                <g id="Stockholm-icons-/-Code-/-Compiling" stroke="none" stroke-width="1" fill="none"
                                    fill-rule="evenodd">
                                    <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                                    <path
                                        d="M2.56066017,10.6819805 L4.68198052,8.56066017 C5.26776695,7.97487373 6.21751442,7.97487373 6.80330086,8.56066017 L8.9246212,10.6819805 C9.51040764,11.267767 9.51040764,12.2175144 8.9246212,12.8033009 L6.80330086,14.9246212 C6.21751442,15.5104076 5.26776695,15.5104076 4.68198052,14.9246212 L2.56066017,12.8033009 C1.97487373,12.2175144 1.97487373,11.267767 2.56066017,10.6819805 Z M14.5606602,10.6819805 L16.6819805,8.56066017 C17.267767,7.97487373 18.2175144,7.97487373 18.8033009,8.56066017 L20.9246212,10.6819805 C21.5104076,11.267767 21.5104076,12.2175144 20.9246212,12.8033009 L18.8033009,14.9246212 C18.2175144,15.5104076 17.267767,15.5104076 16.6819805,14.9246212 L14.5606602,12.8033009 C13.9748737,12.2175144 13.9748737,11.267767 14.5606602,10.6819805 Z"
                                        id="Combined-Shape" fill="#335EEA" opacity="0.3"></path>
                                    <path
                                        d="M8.56066017,16.6819805 L10.6819805,14.5606602 C11.267767,13.9748737 12.2175144,13.9748737 12.8033009,14.5606602 L14.9246212,16.6819805 C15.5104076,17.267767 15.5104076,18.2175144 14.9246212,18.8033009 L12.8033009,20.9246212 C12.2175144,21.5104076 11.267767,21.5104076 10.6819805,20.9246212 L8.56066017,18.8033009 C7.97487373,18.2175144 7.97487373,17.267767 8.56066017,16.6819805 Z M8.56066017,4.68198052 L10.6819805,2.56066017 C11.267767,1.97487373 12.2175144,1.97487373 12.8033009,2.56066017 L14.9246212,4.68198052 C15.5104076,5.26776695 15.5104076,6.21751442 14.9246212,6.80330086 L12.8033009,8.9246212 C12.2175144,9.51040764 11.267767,9.51040764 10.6819805,8.9246212 L8.56066017,6.80330086 C7.97487373,6.21751442 7.97487373,5.26776695 8.56066017,4.68198052 Z"
                                        id="Combined-Shape" fill="#335EEA"></path>
                                </g>
                            </svg>
                        </span>
                        <span>Contribute</span>
                    </router-link>
                </li>
                <li>
                    <router-link @click.native="open = false" to="/licensing">
                        <span class="sicon">
                            <svg width="24px" height="24px" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                                <g id="Stockholm-icons-/-Code-/-Github" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                                    <rect id="Rectangle-5" x="0" y="0" width="24" height="24"></rect>
                                    <path d="M16.5428932,17.4571068 L11,11.9142136 L11,4 C11,3.44771525 11.4477153,3 12,3 C12.5522847,3 13,3.44771525 13,4 L13,11.0857864 L17.9571068,16.0428932 L20.1464466,13.8535534 C20.3417088,13.6582912 20.6582912,13.6582912 20.8535534,13.8535534 C20.9473216,13.9473216 21,14.0744985 21,14.2071068 L21,19.5 C21,19.7761424 20.7761424,20 20.5,20 L15.2071068,20 C14.9309644,20 14.7071068,19.7761424 14.7071068,19.5 C14.7071068,19.3673918 14.7597852,19.2402148 14.8535534,19.1464466 L16.5428932,17.4571068 Z" id="Combined-Shape" fill="#335EEA"></path>
                                    <path d="M7.24478854,17.1447885 L9.2464466,19.1464466 C9.34021479,19.2402148 9.39289321,19.3673918 9.39289321,19.5 C9.39289321,19.7761424 9.16903559,20 8.89289321,20 L3.52893218,20 C3.25278981,20 3.02893218,19.7761424 3.02893218,19.5 L3.02893218,14.136039 C3.02893218,14.0034307 3.0816106,13.8762538 3.17537879,13.7824856 C3.37064094,13.5872234 3.68722343,13.5872234 3.88248557,13.7824856 L5.82567301,15.725673 L8.85405776,13.1631936 L10.1459422,14.6899662 L7.24478854,17.1447885 Z" id="Combined-Shape" fill="#335EEA" opacity="0.3"></path>
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
                update:{
                    retrieved: false,
                    releaseTag: 'NaN',
                    url: '#'
                }
            }
        },
    
        mounted(){
            // Check for new releases and show update tag
            let that = this;
            let xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
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

        computed:{
            showUpdateTag: function(){
                if(this.stats.enabled === true && this.update.retrieved === true && this.stats.releaseTag !== this.update.releaseTag){
                    return true;
                }else{
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

    .navbar-burger:focus{
        outline: none;
        text-decoration: none;
        background: transparent;
    }
</style>