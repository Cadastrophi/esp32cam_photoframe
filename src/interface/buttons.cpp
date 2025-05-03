#include "buttons.h"

Buttons::Buttons() {
}

void Buttons::begin() {
    // Initialize button pins as INPUT_PULLUP
    pinMode(BUTTON_PHOTO, INPUT);
    pinMode(BUTTON_BACK, INPUT);
    
    // Initialize button states
    for (int i = 0; i < 2; i++) {
        buttonState[i] = HIGH;
        lastButtonState[i] = HIGH;
        buttonPressed[i] = false;
        buttonLongPressed[i] = false;
        buttonPressStartTime[i] = 0;
    }
}

void Buttons::update() {
    // Process photo button (index 0)
    handleButtonState(BUTTON_PHOTO, 0);
    
    // Process back button (index 1)
    handleButtonState(BUTTON_BACK, 1);
}

void Buttons::handleButtonState(int pin, int index) {
    // Read the current button state
    bool reading = digitalRead(pin);
    
    // If the button state changed due to noise or pressing
    if (reading != lastButtonState[index]) {
        // Reset the debouncing timer
        lastButtonState[index] = reading;
    }
    
    // The button state has changed
    if (reading != buttonState[index]) {
        buttonState[index] = reading;
        
        // Button pressed (LOW because of INPUT_PULLUP)
        if (buttonState[index] == LOW) {
            buttonPressStartTime[index] = millis();
            buttonPressed[index] = false;
            buttonLongPressed[index] = false;
        }
        // Button released
        else {
            // If not already marked as pressed or long pressed, mark as pressed
            if (!buttonPressed[index] && !buttonLongPressed[index]) {
                buttonPressed[index] = true;
            }
        }
    }
    
    // Check for long press while button is still held down
    if (buttonState[index] == LOW) {
        unsigned long pressDuration = millis() - buttonPressStartTime[index];
        if (pressDuration > LONG_PRESS_TIME && !buttonLongPressed[index]) {
            buttonLongPressed[index] = true;
            buttonPressed[index] = false; // Cancel normal press when long press happens
        }
    }
}

bool Buttons::isPressed(int button) {
    int index = (button == BUTTON_PHOTO) ? 0 : 1;
    bool wasPressed = buttonPressed[index];
    buttonPressed[index] = false; // Reset flag after reading
    return wasPressed;
}

bool Buttons::isLongPressed(int button) {
    int index = (button == BUTTON_PHOTO) ? 0 : 1;
    bool wasLongPressed = buttonLongPressed[index];
    buttonLongPressed[index] = false; // Reset flag after reading
    return wasLongPressed;
}