/*
This was my go-to server at various points throughout the testing and planning 
process. Large pieces are missing from the commits, and some things that 
remain but are no longer used are artifacts of previous experiments.

Despite this, it's committed to this repo for posterity.
*/


var net = require("net");

var clients = {};

function clientConnected(socket) {
    var clientAddress = socket.remoteAddress;
    var existingSocket = clients[clientAddress];
    
    console.log("new connection at " + clientAddress);
    
    if (existingSocket) {
        existingSocket.end();
        console.log("disconnecting duplicate client at " + clientAddress);
    }
    
    clients[clientAddress] = socket;
    console.log(Object.keys(clients));
    
    socket.setEncoding("utf8");
    socket.on("data", socketReceivedData);
    // socket.on("close", function(){removeThisClient(this, socket.remoteAddress)});
    // socket.on("end", removeThisClient.bind(null, socket, socket.remoteAddress));
    // socket.setKeepAlive(true, 10000);
    socket.setTimeout(20000, function(){
        console.log("socket timeout event (one time)");
        this.end();
    });
    socket.on("close", function(){
        console.log("close socket");
        removeThisClient(socket, clientAddress);
    });
    socket.on("end", function(){
        console.log("end socket");
        socket.destroy();
        removeThisClient(socket, clientAddress);
    });
}

function socketReceivedData(data) {
    console.log("[" + this.remoteAddress + "]: " + data);
    // for (address in clients) {
    //     clients[address].write(data);
    // }
}

function removeThisClient(socket, address) {
    console.log("connection closed: " + address);
    if (clients[address] === socket) {
        console.log("removing closed connection from clients list");
        delete clients[address];
    }
}

var tcpServer = net.createServer(clientConnected);
    
tcpServer.listen(9487);

// var counter = 5095;
// function sendTimeAfterDelay() {
//     setTimeout(function(){
//         socketReceivedData("" + (counter++ * .01) + "\r\n");
//         sendTimeAfterDelay();
//     }, counter * 10);
// }

// setTimeout(function(){console.log("starting");sendTimeAfterDelay()}, 10000);
