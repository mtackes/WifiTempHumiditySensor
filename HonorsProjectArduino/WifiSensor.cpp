// WifiSensor.cpp

#include "WifiSensor.h"

WifiSensor::WifiSensor() :
    wifi(WIFI_INTERRUPT, WIFI_ENABLE, WIFI_CHIPSELECT),
    client(wifi),
    dht(DHT_PIN, DHT_TYPE) {
}

bool WifiSensor::init() {
    dht.begin();
    bool isInitialized = wifi.init();
    
    // If it initialized correctly
    if (isInitialized) {
        // Construct the `macAddress` instance variable
        byte macAddressBytes[6];
        wifi.getMacAddress(macAddressBytes);
        
        // For each byte
        for (int i = 0; i < 6; i++) {
            // Format it into the instance variable at the correct spot
            // `i * 2` moves the insertion point one hex pair for each byte
            sprintf(&macAddress[i * 2], "%02X", macAddressBytes[i]);
        }
    }
    
    return isInitialized;
}

bool WifiSensor::connectToWifi(unsigned int timeout) {
    Serial.println(WIFI_SSID);
    Serial.println(WIFI_PASSWORD);

    // (char *) casts to sidestep warning
    // SFE CC3000 Library would need to update to fix this properly
    return wifi.connect((char *)WIFI_SSID, WIFI_SECURITY, (char *)WIFI_PASSWORD, timeout);
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
    client.print(macAddress);
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
