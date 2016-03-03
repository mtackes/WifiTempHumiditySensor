var express = require("express");
var mongodb = require("mongodb");
var config = require("./config.json");

function appWithMongoCollection(mongoCollection) {
    var app = require("express")();
    
    app.get("/", function(req, res, next) {
        res.type("json");
        
        mongoCollection.find().sort({"date": 1}).toArray(function(err, results) {
            if (err) {
                console.log(err);
                process.exit(3);
            }
            
            res.json(results)
        });
    });
    
    app.use("/after/:time", function(req, res, next) {
        res.type("json");
        // TODO: filter to 
        req.params.time;
        
        mongoCollection.find({date: {"$gt": new Date(parseInt(req.params.time, 10))}});
        
    });
    
    return app;
}

module.exports = {
    collectionDataSource: appWithMongoCollection
}
