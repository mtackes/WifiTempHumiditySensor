// Indicator.cpp

#include "Indicator.h"

Indicator::Indicator(int pin) {
    _pin = pin;
    
    pinMode(_pin, OUTPUT);
}

void Indicator::blink(int count, int duration, bool repeatForever) {
    do {
        for (int i = 1; i <= count; i++) {
            digitalWrite(_pin, HIGH);
            delay(duration);
            digitalWrite(_pin, LOW);
            
            int durationMultiplier = 1;
            
            // At the end of the loop
            if (i == count) {
                // Double the duration of the final 'off' phase
                durationMultiplier = 3;
            }
            
            delay(duration * durationMultiplier);
        }
    } while (repeatForever);
}

void Indicator::blinkPattern(char pattern[], int duration, bool repeatForever) {
    int patternLength = strlen(pattern);
    
    do {
        for (int i = 0; i < patternLength; i++) {
            int intensity = 255;
            
            switch (pattern[i]) {
            case ' ':
                intensity = 0;
                break;
            case '_':
                intensity = 7;
                break;
            case '-':
                intensity = 63;
                break;
            case '*':
                intensity = 255;
                break;
            }
            
            analogWrite(_pin, intensity);
            
            delay(duration);
        }
    } while (repeatForever);
    
    digitalWrite(_pin, LOW);
}
