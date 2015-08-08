// WifiTemp.h

#ifndef WifiTemp_h
#define WifiTemp_h
#endif

#include <Arduino.h>
#include <SPI.h>
#include "DHT.h"
#include "SFE_CC3000.h"
#include "SFE_CC3000_Client.h"

class WifiTemp {
public:
    WifiTemp(SFE_CC3000 wifi, DHT dht);
    ~WifiTemp();
    bool wifiConnect(char *ssid,
                    unsigned int security,
                    char *password,
                    unsigned int timeout = 30000);
    
private:
    SFE_CC3000 _wifi;
    DHT _dht;
    SFE_CC3000_Client _client;
};
