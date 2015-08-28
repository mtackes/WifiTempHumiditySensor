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
    bool init();
    bool connectToWifi(unsigned int timeout = 0);
    bool connectToServer();
    bool isConnectedToServer();
    bool closeConnectionToServer();
    void sendStartup();
    void sendData();
    
private:
    SFE_CC3000 wifi;
    SFE_CC3000_Client client;
    DHT dht;
    char macAddress[13];
    
    void sendIdentifier();
    void sendTemperature();
    void sendHumidity();
    void sendSeparator();
    void sendLineBreak();
};
