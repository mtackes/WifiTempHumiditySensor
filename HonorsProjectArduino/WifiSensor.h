// WifiSensor.h

#ifndef WIFISENSOR_H
#define WIFISENSOR_H
#endif

#include "SFE_CC3000.h"
#include "SFE_CC3000_Client.h"
#include "DHT.h"
#include "Configuration.h"

class WifiSensor {
public:
    WifiSensor();
    
private:
    SFE_CC3000 wifi;
    SFE_CC3000_Client client;
    DHT dht;
};
