#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "config.h"

class Buttons {
public:
    Buttons();
    void begin();
    void update();
    bool isPressed(int button);
    bool isLongPressed(int button);
    
private:
    unsigned long buttonPressStartTime[2]; // Time when button was pressed
    bool buttonState[2];                   // Current button state
    bool lastButtonState[2];               // Previous button state
    bool buttonPressed[2];                 // Button press event flag
    bool buttonLongPressed[2];             // Button long press event flag
    
    void handleButtonState(int pin, int index);
};

#endif // BUTTONS_H