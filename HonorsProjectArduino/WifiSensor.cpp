// WifiSensor.cpp

#include "WifiSensor.h"

WifiSensor::WifiSensor() :
    wifi(WIFI_INTERRUPT, WIFI_ENABLE, WIFI_CHIPSELECT),
    client(wifi),
    dht(DHT_PIN, DHT_TYPE) {
}
