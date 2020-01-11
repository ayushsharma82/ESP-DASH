import Vue from "vue"

let host = "ws://"+document.location.host+"/dashws";
// let host = "ws://192.168.1.x/dashws"; // For Local Testing via npm run serve

const socket = new WebSocket(host);

const emitter = new Vue({
  methods:{
    send(message){
      if (1 === socket.readyState)
        socket.send(message)
    }
  }
});

socket.onopen = function(){
  emitter.$emit("connected");
};

socket.onclose = function(){
  emitter.$emit("disconnected");
};

socket.onmessage = function(msg){
  emitter.$emit("message",  JSON.parse(msg.data));
};
socket.onerror = function(err){
  emitter.$emit("error", err)
};


let socketInterval = setInterval(() => {
    if(socket.readyState == 0){
        emitter.$emit("disconnected");
    }else if(socket.readyState === 3){
        location.reload();
    }else{
        socket.send("{\"command\":\"ping\"}");
    }
}, 5000);

if(process.env.NODE_ENV !== 'production'){
  clearInterval(socketInterval);
}

export default emitter
