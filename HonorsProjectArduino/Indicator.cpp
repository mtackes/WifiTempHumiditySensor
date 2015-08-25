// Indicator.cpp

#include "Indicator.h"

Indicator::Indicator(int pin) : pin(pin), state(LOW) {    
    pinMode(pin, OUTPUT);
}

void Indicator::on() {
    state = HIGH;
    digitalWrite(pin, state);
}

void Indicator::off() {
    state = LOW;
    digitalWrite(pin, state);
}

void Indicator::toggle() {
    state = !state;
    digitalWrite(pin, state);
}

// Synchronous `blink` and `blinkPattern` do not change state as they
// block and return the led to the starting state when (if) they finish
void Indicator::blink(int count, int duration, bool repeatForever) {
    do {
        for (int i = 1; i <= count; i++) {
            digitalWrite(pin, HIGH);
            delay(duration);
            digitalWrite(pin, LOW);
            
            int durationMultiplier = 1;
            
            // At the end of the loop
            if (i == count) {
                // Double the duration of the final 'off' phase
                durationMultiplier = 3;
            }
            
            delay(duration * durationMultiplier);
        }
    } while (repeatForever);
    
    digitalWrite(pin, state);
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
            
            analogWrite(pin, intensity);
            
            delay(duration);
        }
    } while (repeatForever);
    
    digitalWrite(pin, state);
}

void Indicator::blinkAsync(int duration) {
    int currentTime = millis();
    
    if (currentTime - previousTime > duration) {
        previousTime = currentTime;
        toggle();
    }
    
}
