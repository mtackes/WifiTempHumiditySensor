var net = require("net");

var tcpServer = net.createServer(function(socket) {
    console.log("server connection event");
    console.log("local:  " + socket.localAddress + ", port " + socket.localPort);
    console.log("remote: " + socket.remoteAddress + ", port " + socket.remotePort);
    
    socket.setEncoding("utf8");
    
    socket.on("data", function(data) {
        console.log("socket data event");
        console.log("data: " + data);
        socket.write(data.trim().length.toString() + "\r\n");
    });
    
    socket.on("end", function() {
        console.log("socket end event");
    });
    
    socket.on("timeout", function() {
        console.log("socket timeout event");
    });
    
    socket.on("drain", function() {
        console.log("socket drain event");
    });
    
    socket.on("error", function(error) {
        console.log("socket error event");
        console.log("error: " + error);
    });
    
    socket.on("close", function(closedFomError) {
        console.log("socket close event");
        console.log("closed from error: " + closedFomError);
    });
});

tcpServer.listen(9487, function() {
    console.log("listening");
});

tcpServer.on("close", function() {
    console.log("server close event");
});

tcpServer.on("error", function(error) {
    console.log("server error event");
});
