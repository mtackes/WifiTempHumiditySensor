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
}

void loop() {
}

