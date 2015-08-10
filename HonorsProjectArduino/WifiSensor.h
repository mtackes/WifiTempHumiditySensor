// WifiSensor.h

#ifndef WifiSensor_h
#define WifiSensor_h
#endif

#include "SFE_CC3000.h"
#include "SFE_CC3000_Client.h"
#include "DHT.h"

// Config Constants
#define WIFI_INTERRUPT  3
#define WIFI_ENABLE     7
#define WIFI_CHIPSELECT 10
#define DHT_PIN         2
#define DHT_TYPE        DHT22

class WifiSensor {
public:
    WifiSensor();
    
private:
    SFE_CC3000 wifi;
    SFE_CC3000_Client client;
    DHT dht;
};
