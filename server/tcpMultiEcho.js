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
    socket.on("data", socketReceivedData);
}

function socketReceivedData(data) {
    for (address in clients) {
        clients[address].write(address + ": " + data.trim() + "\r\n");
    }
}

function removeThisClient() {
    delete clients[this.remoteAddress];
}

var tcpServer = net.createServer(clientConnected);
    
tcpServer.listen(9487);
