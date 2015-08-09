// Indicator.h

#ifndef Indicator_h
#define Indicator_h
#endif

#include <Arduino.h>

#define SHORT   125
#define MEDIUM  250
#define LONG    500

class Indicator {
public:
    Indicator(int pin);
    void blink(int count, int duration, bool repeatForever = false);
    void blinkPattern(char pattern[], int duration, bool repeatForever = false);

private:
    int _pin;
};
