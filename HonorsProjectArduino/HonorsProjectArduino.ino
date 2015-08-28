#include <SPI.h>
#include "SFE_CC3000.h"
#include "SFE_CC3000_Client.h"
#include "DHT.h"
#include "Configuration.h"
#include "Indicator.h"
#include "WifiSensor.h"

WifiSensor module;
Indicator status(LED_STATUS_PIN);
Indicator error(LED_ERROR_PIN);

unsigned long nextReadTime;
byte connectionMisses = 0;

void setup() {
    if (!module.init()) {
        error.blink(2, MEDIUM, true);
    }
    
    status.blink(1, SHORT);
    
    if (!module.connectToWifi(30000)) {
        error.blink(3, MEDIUM, true);
    }
    
    status.blink(2, SHORT);
    
    if (!module.connectToServer()) {
        error.blink(4, SHORT, true);
    }
    
    status.on();
    
    module.sendStartup();
    
    if (!module.closeConnectionToServer()) {
        error.blinkPattern("*_", MEDIUM, true);
    }
    
    status.off();
    
    // Set read time to now since initialization has finished
    nextReadTime = millis();
}

void loop() {
    unsigned long currentTime = millis();
    
    if (connectionMisses) {
        // Speeds up the blinking as number of misses increases
        int duration = map(connectionMisses, 0, 255, 1000, 25);
        error.blinkAsync(duration);
    }
    
    if (currentTime >= nextReadTime) {
        nextReadTime += READ_INTERVAL;
        
        status.on();
        
        if (!module.connectToServer()) {
            module.closeConnectionToServer();
            connectionMisses++;
            error.blinkPattern("*-* *-* *-*", MEDIUM, connectionMisses == 255);
            return;
        }
        
        status.blink(1, SHORT);
        module.sendData();
        
        if (!module.closeConnectionToServer()) {
            // TODO: Handle error instead of just trapping here
            error.blinkPattern("*-_", MEDIUM, true);
        }
        
        status.off();
    }
}
