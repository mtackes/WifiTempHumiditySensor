// WifiTemp.cpp

#include "WifiTemp.h"

WifiTemp::WifiTemp(SFE_CC3000 wifi, DHT dht) {
    _wifi = wifi;
    _dht = dht;
    
    _client = SFE_CC3000_Client(wifi);
}

bool WifiTemp::wifiConnect(char *ssid,
                            unsigned int security,
                            char *password,
                            unsigned int timeout = 30000) {
    
    if (!_wifi.init()) {
        return false;
    }
    
    if (!_wifi.connect(ssid, security, password,  timeout)) {
        return false;
    }
}
