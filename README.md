# Wifi Temp and Humidity Sensor
#### An honors project for Madison College.
###### Second place winner in Madison College Honors Competition, December 2015.

Uses an Arduino, wifi module, and temperature/humidity sensor to record data from multiple locations in a household to a Node.js server.

The Arduino code relies on two third-party libraries:

- [Sparkfun CC3000 library](https://github.com/sparkfun/SFE_CC3000_Library)
- [Adafruit DHT Sensor library](https://github.com/adafruit/DHT-sensor-library)

The Node server relies on Express and MongoDB (links in [package.json](server/package.json)), while the client uses jQuery and the non-commercial version of [Highcharts](http://highcharts.com).

### Project Notes

Now that I'm done with the honors program at Madison College, this project will likely receive no more updates (I had to hand the hardware back to the school).

The Arduino code is relatively solid, not that I did anything super fancy with it, though I never figured out a particular issue where the device would occasionally fail to connect to its designated server address (despite many, _many_ hours lost). The (small) library that I wrote to wrap the wifi and DHT libraries was mostly an exuse to learn just a little C++.

The Node server, on the other hand, is a bit more lacking. In order to get things working by my deadline with the relatively little time I could spare for the project, things are bolted together in strange ways. I'm particularly unhappy with the integration of MongoDB, something I wanted to try because my only experience had been with more traditional SQL databases. Specifically, I had trouble getting the connection object to the code that needed it and efficiently getting JSON out to the client. Both of these are rooted, at least partially, in the async nature of Node. If I had more time, I would have liked to research how others handled these issues, and maybe used a higher level Mongo connection library.

Regardless of the issues and headaches along the way, I had a lot of fun working with hardware like this, something that I really never had the chance to try before, although I probably won't be trying to take on a project like this single-handedly again.
