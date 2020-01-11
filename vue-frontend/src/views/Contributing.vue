<template>
    <div class="container" style="margin: 1.55rem 1rem;">
        <div class="section has-text-centered">
            <svg width="128px" id="Layer_1" data-name="Layer 1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
                <g id="Stockholm-icons-_-Home-_-Deer" data-name="Stockholm-icons-/-Home-/-Deer">
                    <rect id="bound" fill="none" width="24" height="24"></rect>
                    <path id="Combined-Shape" fill="#384c74" opacity="0.3" isolation="isolate"
                        d="M22,8.19a1,1,0,0,1-.47.67l-5,3A1,1,0,0,1,16,12H8a1,1,0,0,1-.51-.14l-5-3A1,1,0,0,1,2,8.19l-1-5a1,1,0,0,1,2-.4L3.61,6,6.29,3.29A1,1,0,0,1,7.71,4.71L4.61,7.8,8.28,10h7.44l3.67-2.2-3.1-3.09a1,1,0,0,1,1.42-1.42L20.39,6,21,2.8a1,1,0,0,1,2,.4Zm-6.93.7A1,1,0,0,1,16,7.11l3,1.5A1,1,0,0,1,19,10.36l-2.5,1.5A1,1,0,0,1,16,12H8a1,1,0,0,1-.51-.14L5,10.36A1,1,0,0,1,5,8.64l2.5-1.5a1,1,0,1,1,1,1.72L7.44,9.5l.84.5h7.44l.7-.42Z">
                    </path>
                    <path id="Rectangle-192" fill="#384c74"
                        d="M9.86,10h4.28A2,2,0,0,1,16,12.68l-2.68,7.38A1.43,1.43,0,0,1,12,21h0a1.43,1.43,0,0,1-1.34-.94L8,12.68A2,2,0,0,1,9.86,10Z">
                    </path>
                </g>
            </svg>
            <br/>
            <h1 class="title is-4">ESP-DASH</h1>
        </div>
        <br/>
        <hr/>
        <br/>
        <p class="section">
            A open-source software library is never made perfect in one go. It's the collective effort of all the users in making it stable. Don't let the efforts of everyone go waste! Contribute a bit in the library to keep it up-to-date.   
        </p>
        <br/>
        <br/>
        <p class="section">
            <span class="title is-6">There are a couple of ways by which you can contibute to ESP-DASH:</span>
            <br/>
            <br/>
            <ol style="margin-left: 2rem;">
                <li>Create an issue</li>
                <li>Create a pull request</li>
                <li>Sponsor the project</li>
            </ol>
        </p>
        <br/>
        <br/>
        <p class="section">
            <span class="title is-5">1. Create an issue</span>
            <br/>
            A absolutely necessary thing which you can do is to create an issue on ESP-DASH's repository. It can be a bug or a feature request. 
            As soon as you encounter a bug related to ESP-DASH, You can create an issue on Github where people will try to fix it for all. You can create a issue <a href="https://github.com/ayushsharma82/ESP-DASH/issues" target="_blank">here</a>.
        </p>
        <br/>
        <br/>
        <p class="section">
            <span class="title is-5">2. Create a pull request</span>
            <br/>
            You can go through the list of issues on ESP-DASH's repository and try to create a pull request to fix something. It will be much appriciated by everyone! Don't worry if your pull request is doubtful, collaborartors will help you with your efforts in fixing that particular thing.
            You can create / check pending pull requests <a href="https://github.com/ayushsharma82/ESP-DASH/pulls" target="_blank">here</a>.
        </p>
        <br/>
        <br/>
        <p class="section">
            <span class="title is-5">3. Sponsor / Donate to the Project</span>
            <br/>
            Development of any open-source software comes at the cost of time. I can't force this enough, but if you think ESP-DASH has met your expectations and should do better, then you can think of supporting the project on <a href="https://opencollective.com/espdash#section-contribute" target="_blank">OpenCollective</a>. We would love to have you on board our contributors list!
            <br/>
            <br/>
            <a href="https://opencollective.com/espdash#section-contribute" target="_blank">
                <img :src="$collectiveLogo" width="300">
            </a>
        </p>
        <br/>
        <br/>
        <div class="section">
            <nav class="level">
                <div class="level-item has-text-centered">
                    <div>
                        <p class="heading">Stars</p>
                        <p class="title">{{ repo.stars }}</p>
                    </div>
                </div>
                <div class="level-item has-text-centered">
                    <div>
                        <p class="heading">Subscribers</p>
                        <p class="title">{{ repo.subscribers }}</p>
                    </div>
                </div>
                <div class="level-item has-text-centered">
                    <div>
                        <p class="heading">Forks</p>
                        <p class="title">{{ repo.forks }}</p>
                    </div>
                </div>
            </nav>
        </div>
    </div>
</template>

<script>
export default {
    data(){
        return{
            repo:{
                stars: null,
                subscribers: null,
                forks: null
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
                that.repo.stars = res.stargazers_count;
                that.repo.subscribers = res.subscribers_count;
                that.repo.forks = res.forks;
            }
        };
        xhttp.open("GET", "https://api.github.com/repos/ayushsharma82/ESP-DASH", true);
        xhttp.send();
    }
}
</script>