// WifiSensor.cpp

#include "WifiSensor.h"

WifiSensor::WifiSensor(char ssid[], unsigned int security, char password[]) :
    wifi(WIFI_INTERRUPT, WIFI_ENABLE, WIFI_CHIPSELECT),
    client(wifi),
    dht(DHT_PIN, DHT_TYPE),
    ssid(ssid),
    security(security),
    password(password) {
}
