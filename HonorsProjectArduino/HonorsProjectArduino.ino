#include <SPI.h>
#include "SFE_CC3000.h"
#include "SFE_CC3000_Client.h"
#include "DHT.h"
#include "Indicator.h"
#include "TestThing.h"

void setup() {
  Indicator ind(9);
  ind.blink(4, SHORT);
  SFE_CC3000 wifiThing(2, 7, 10);
  TestThing testThing(wifiThing);
  
  testThing.connectAll(21);
}

void loop() {
}

