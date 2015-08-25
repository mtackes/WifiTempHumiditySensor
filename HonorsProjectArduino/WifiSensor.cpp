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

bool WifiSensor::connectToWifi(unsigned int timeout) {
    Serial.println(WIFI_SSID);
    Serial.println(WIFI_PASSWORD);
    return wifi.connect(WIFI_SSID, WIFI_SECURITY, WIFI_PASSWORD, timeout);
}

bool WifiSensor::connectToServer() {
    return client.connect(SERVER_ADDRESS, SERVER_PORT);
}

bool WifiSensor::isConnectedToServer() {
    return client.connected();
}

bool WifiSensor::closeConnectionToServer() {
    // FIXME: See if there's a way to actually check for pending write data
    // Delay closing for 1 second to allow final data to send properly
    delay(1000);
    
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
