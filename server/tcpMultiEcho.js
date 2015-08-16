var net = require("net");

var clients = {};

function clientConnected(socket) {
    var clientAddress = socket.remoteAddress;
    var existingSocket = clients[clientAddress];
    
    if (existingSocket) {
        existingSocket.end("closing duplicate connection\r\n");
        console.log("disconnecting duplicate client at " + clientAddress);
    }
    
    clients[clientAddress] = socket;
    console.log(Object.keys(clients));
    
    socket.setEncoding("utf8");
    socket.on("data", socketReceivedData);
    // socket.on("close", function(){removeThisClient(this, socket.remoteAddress)});
    // socket.on("end", removeThisClient.bind(null, socket, socket.remoteAddress));
    socket.setTimeout(5000, function(){
        console.log("socket timeout event (one time)");
    });
    socket.on("close", function(){
        removeThisClient(socket, clientAddress)
    });
}

function socketReceivedData(data) {
    for (address in clients) {
        clients[address].write(data);
    }
}

function removeThisClient(socket, address) {
    console.log("connection closed: " + address);
    if (clients[address] === socket) {
        console.log("duplicate in close handler");
        delete clients[address];
    }
}

var tcpServer = net.createServer(clientConnected);
    
tcpServer.listen(9487);
