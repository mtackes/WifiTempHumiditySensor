// Indicator.h

#ifndef INDICATOR_H
#define INDICATOR_H
#endif

#include <Arduino.h>

#define SHORT   125
#define MEDIUM  250
#define LONG    500

class Indicator {
public:
    Indicator(int pin);
    void on();
    void off();
    void toggle();
    
    void blink(int count, int duration, bool repeatForever = false);
    void blinkPattern(char pattern[], int duration, bool repeatForever = false);
    
    void blinkAsync(int duration);
    
private:
    int pin;
    unsigned long previousTime;
    int state;
};
