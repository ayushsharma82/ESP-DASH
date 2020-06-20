<template>
    <div class="container" style="margin: 1.55rem 1rem;">
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
            if (this.readyState === 4 && this.status === 200) {
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