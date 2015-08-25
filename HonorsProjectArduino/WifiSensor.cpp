// WifiSensor.cpp

#include "WifiSensor.h"

WifiSensor::WifiSensor() :
    wifi(WIFI_INTERRUPT, WIFI_ENABLE, WIFI_CHIPSELECT),
    client(wifi),
    dht(DHT_PIN, DHT_TYPE) {
}

bool WifiSensor::init() {
    dht.begin();
    return wifi.init();
}

bool WifiSensor::connectWifi(unsigned int timeout) {
    Serial.println(WIFI_SSID);
    Serial.println(WIFI_PASSWORD);
    return wifi.connect(WIFI_SSID, WIFI_SECURITY, WIFI_PASSWORD, timeout);
}

bool WifiSensor::connectToServer() {
    return client.connect(SERVER_ADDRESS, SERVER_PORT);
}

bool WifiSensor::isConnected() {
    return client.connected();
}

bool WifiSensor::closeConnection() {
    return client.close();
}

void WifiSensor::sendStartup() {
    sendSeparator();
    sendIdentifier();
    sendSeparator();
}

void WifiSensor::sendData() {
    sendIdentifier();
    sendSeparator();
    sendTemperature();
    sendSeparator();
    sendHumidity();
}

void WifiSensor::sendIdentifier() {
    const int addressLength = 6;
    unsigned char macAddress[addressLength];
    wifi.getMacAddress(macAddress);
    // Modified from SFE CC3000 'board test' example
    for (int i = 0; i < addressLength; i++) {
        if (macAddress[i] < 0x10) {
            client.print("0");
        }
        client.print(macAddress[i], HEX);
    }
}

void WifiSensor::sendTemperature() {
    client.print(dht.readTemperature(), 1);
}

void WifiSensor::sendHumidity() {
    client.print(dht.readHumidity(), 1);
}

void WifiSensor::sendSeparator() {
    client.print(';');
}

void WifiSensor::sendLineBreak() {
    client.println();
}
