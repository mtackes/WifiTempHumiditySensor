// Indicator.cpp

#include "Indicator.h"

Indicator::Indicator(int pin) {
    _pin = pin;
    
    pinMode(_pin, OUTPUT);
}

void Indicator::blink(int count, int length, bool repeatForever = false) {
    do {
        for (int i = 1; i <= count; i++) {
            digitalWrite(_pin, HIGH);
            delay(length);
            digitalWrite(_pin, LOW);
            
            int lengthMultiplier = 1;
            
            // At the end of the loop
            if (i == count) {
                // Double the length of the final 'off' phase
                lengthMultiplier = 2;
            }
            
            delay(length * lengthMultiplier);
        }
    } while (repeatForever);
}

void Indicator::blinkPattern(char[] pattern, int length, bool repeatForever) {
    do {
        
    } while (repeatForever);
}