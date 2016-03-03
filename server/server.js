var net = require("net");
var express = require("express");
var mongo = require("mongodb").MongoClient;
var config = require("./config.json");

var app = express();
var dataInput = require("./dataInputServer.js");
var jsonServer = require("./jsonServer.js");
var staticAssetsServer = express.static("staticAssets");

mongo.connect(config.mongo.url, function(err, db) {
    if (err) {
        console.log(err);
        process.exit(2);
    }
    
    app.use("/", staticAssetsServer);
    
    var dataCollection = db.collection(config.mongo.collection);
    
    dataInputHandler = dataInput.collectionDataSource(dataCollection);
    dataInputServer = net.createServer(dataInputHandler);
    dataInputServer.listen(config.dataInput.port);
    
    var jsonApp = jsonServer.collectionDataSource(dataCollection);
    app.use("/data", jsonApp);
    app.listen(8080);
    
    // Adapted from http://stackoverflow.com/a/14032965
    function exitHandler(options, err) {
        if (err) {
            console.log(err.stack);
        }
        
        if (options.cleanup) {
            db.close();
        }
        
        if (options.exit) {
            process.exit();
        }
    }
    
    // do something when app is closing
    process.on('exit', exitHandler.bind(null,{cleanup:true}));
    // catches ctrl+c event
    process.on('SIGINT', exitHandler.bind(null, {exit:true}));
    // catches uncaught exceptions
    process.on('uncaughtException', exitHandler.bind(null, {exit:true}));
});
