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
    WifiSensor(char ssid[] = WIFI_SSID,
        unsigned int security = WIFI_SECURITY,
        char password[] = WIFI_PASSWORD);
    
private:
    SFE_CC3000 wifi;
    SFE_CC3000_Client client;
    DHT dht;
    char *ssid;
    unsigned int security;
    char *password;
};
