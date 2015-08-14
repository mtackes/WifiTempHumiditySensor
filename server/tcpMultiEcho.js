var net = require("net");

var clients = {};

function clientConnected(socket) {
    var existingSocket = clients[socket.remoteAddress];
    
    if (existingSocket) {
        existingSocket.end("closing duplicate connection");
        console.log("disconnecting duplicate client at " + socket.remoteAddress);
    }
    
    clients[socket.remoteAddress] = socket;
    
    socket.setEncoding("utf8");
    // socket.on("data", socketReceivedData);
    // socket.on("close", function(){removeThisClient(this, socket.remoteAddress)});
    socket.on("end", removeThisClient.bind(null, socket, socket.remoteAddress));
}

function socketReceivedData(data) {
    console.log(this.remoteAddress);
    for (address in clients) {
        clients[address].write(address + ": " + data.trim() + "\r\n");
    }
}

function removeThisClient(that, address) {
    console.log(this);
    console.log("\n\n\n\n");
    console.log(that);
    console.log("connection closed: " + address);
    // if (clients[this.remoteAddress] === this) {
    //     console.log("duplicate in close handler");
    //     delete clients[this.remoteAddress];
    // }
}

var tcpServer = net.createServer(clientConnected);
    
tcpServer.listen(9487);
