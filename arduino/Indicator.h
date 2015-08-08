// Indicator.h

#ifndef Indicator_h
#define Indicator_h
#endif

#include <Arduino.h>

#define SHORT   50
#define MEDIUM  250
#define LONG    500

class Indicator {
public:
    Indicator(int pin);
    ~Indicator();
    void blink(int count, int length, bool repeatForever = false);
    void blinkPattern(char pattern[], int length, bool repeatForever = false);

private:
    int _pin;
};
