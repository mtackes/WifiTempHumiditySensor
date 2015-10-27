var net = require("net");
var mongo = require("mongodb").MongoClient;

var dataPointFormat = /([0-9a-f]{12});(\d{1,3}\.\d);(\d{1,2}\.\d)/i;

module.exports = function(mongoURL, tcpPortNumber) {
    mongo.connect(mongoURL, function(err, db) {
        if (err) {
            console.log(err);
            process.exit(2);
        }
        
        console.log("Database Connected.");
        
        var tcpServer = net.createServer(function(socket) {
            clientConnected(socket, db);
        });
        
        tcpServer.listen(tcpPortNumber);
    });
};

function clientConnected(socket, db) {
    var clientAddress = socket.remoteAddress;
    
    console.log("new connection at " + clientAddress);
        
    socket.setEncoding("utf8");
    
    socket.on("data", function(data) {
        socketReceivedData.bind(this)(data, db);
    });
    
    // socket.on("close", function(){removeThisClient(this, socket.remoteAddress)});
    // socket.on("end", removeThisClient.bind(null, socket, socket.remoteAddress));
    // socket.setKeepAlive(true, 10000);
    
    socket.setTimeout(20000, function(){
        console.log("socket timeout event (one time)");
        this.end();
    });
    socket.on("close", function(){
        console.log("close socket");
    });
    socket.on("end", function(){
        console.log("end socket");
        socket.destroy();
    });
    socket.on("error", function(error) {
        console.log("\n\n*********************\n\n");
        console.log(this);
        console.log("\n\n*********************\n\n");
        console.log(error);
        console.log("\n\n*********************\n\n");
    });
}

function socketReceivedData(data, db) {
    var dateReceived = new Date();
    var dataMatch = data.match(dataPointFormat);
    
    if (!dataMatch) {
        console.log("Error: data does not match format.");
        console.log("Data: " + data);
        console.log("Sent from: " + this.remoteAddress);
        
        return;
    }
    
    var hardwareId = dataMatch[1];
    var temperature = parseFloat(dataMatch[2]);
    var humidity = parseFloat(dataMatch[3]);
    
    db.collection("data").insertOne({
        "date": dateReceived,
        "remoteAddress": this.remoteAddress,
        "hardwareId": hardwareId,
        "temperature": temperature,
        "humidity": humidity
    }, function(err, result) {
        if (err) {
            console.log("error inserting:");
            console.log(err);
        } else {
            console.log(result);
        }
    });
    console.log("[" + this.remoteAddress + "]: " + data);
}
