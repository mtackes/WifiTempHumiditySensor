var net = require("net");

// Id is 12 hexadecimal digits
// Temperature is in the range of -40.0 and 80.0 degrees celcius
// Humidity is between 0.0 and 99.9 percent
// Will optionally match on the numbers without the decimal/digit -> dd(.d?)?
var dataPointFormat = /([0-9a-f]{12});(-?\d{1,2}(?:\.\d?)?);(\d{1,2}(?:\.\d?)?)/i;
var firstConnectFormat = /;([0-9a-f]{12});/i;


function tcpServerUsingMongoCollection(mongoCollection) {
    
    function clientConnected(socket) {
        var connectionDateTime = new Date();
        
        var clientAddress = socket.remoteAddress;
        
        // console.log("new connection at " + clientAddress);
            
        socket.setEncoding("utf8");
        
        // MARK: - Setup socket events
        
        var dataCollector = newDataCollector();
        socket.on("data", dataCollector.collect);
        
        socket.setTimeout(20000, function(){
            console.log("socket timeout event (one time) on remote: " + this.remoteAddress);
            this.end();
        });
        
        socket.on("close", closeHandlerForCollectorAtDateWithMongoCollection(
            dataCollector,
            connectionDateTime,
            mongoCollection
        ));
        
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
    
    return clientConnected
}


function newDataCollector() {
    var collector = Object.create(null);
    collector.data = "";
    
    var collectorFunction = function(data) {
        this.data += data;
    }
    collector.collect = collectorFunction.bind(collector);
    
    return collector;
}

function closeHandlerForCollectorAtDateWithMongoCollection(dataCollector, date, mongoCollection) {
    return function() {
        var mongoData = mongoDataFromRawInputs(
            dataCollector.data,
            date,
            this.remoteAddress
        );
        
        var firstConnectMatch;
        
        if (mongoData) {
            console.log("-");
            console.log(mongoData);
            insertDataInMongoCollection(mongoData, mongoCollection);
            console.log("-");
        } else if (firstConnectMatch = dataCollector.data.match(firstConnectFormat)) {
            console.log("\n---------");
            console.log("First connection from id: " + firstConnectMatch[1]);
            console.log("---------\n");
        } else {
            console.log("\n*********");
            console.log("Improperly formatted data received:");
            console.log(dataCollector.data);
            console.log("*********\n");
        }
        
        console.log("close socket");
    }

}

function mongoDataFromRawInputs(rawData, dateReceived, remoteAddress) {
    var dataMatch = rawData.match(dataPointFormat);
    
    if (!dataMatch) {
        return null;
    }
    
    var hardwareId = dataMatch[1];
    var temperature = parseFloat(dataMatch[2]);
    var humidity = parseFloat(dataMatch[3]);
    
    return {
        "date": dateReceived,
        "remoteAddress": remoteAddress,
        "hardwareId": hardwareId,
        "temperature": temperature,
        "humidity": humidity
    }
}

function insertDataInMongoCollection(data, mongoCollection) {
    mongoCollection.insertOne(data, function(err, result) {
        if (err) {
            console.log("error inserting data:");
            console.log(err);
        } else {
            console.log(result.result);
        }
    });
}


module.exports = {
    collectionDataSource: tcpServerUsingMongoCollection
};
