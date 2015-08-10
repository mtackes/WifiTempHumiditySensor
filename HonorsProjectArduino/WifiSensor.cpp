// WifiSensor.cpp

#include "WifiSensor.h"

WifiSensor::WifiSensor()
    : wifi(WIFI_INTERRUPT, WIFI_ENABLE, WIFI_CHIPSELECT)
    , client(wifi)
    , dht(DHT_PIN, DHT_TYPE) {
    wifi.connect("asdf", WLAN_SEC_WPA2, "asdf");
    client.connect("google.com");
}

void WifiSensor::connectAll(int pointless) {
    wifi.connect("asdf", WLAN_SEC_WPA2, "asdf");
    client.connect("google.com");
}
