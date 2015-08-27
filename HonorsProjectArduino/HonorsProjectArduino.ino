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
    
    if (currentTime >= nextReadTime) {
        nextReadTime += READ_INTERVAL;
        
        status.on();
        
        if (!module.connectToServer()) {
            // TODO: Handle error instead of just trapping here
            error.blinkPattern("*-* ", MEDIUM, true);
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
