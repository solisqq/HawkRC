#ifndef CBUTTON_H
#define CBUTTON_H

#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/Atmega/OutputBoard/Pinout.h"
class CButton {
private:
    uint8_t pin;
    bool state=false;
    Pinout::Buttons type = Pinout::Buttons::Up;
public:
    CButton(){}
    
    void init(uint8_t btn_pin) {
        pin = btn_pin;
        pinMode(pin, INPUT_PULLUP);
        state=false;
        type = static_cast<Pinout::Buttons>(btn_pin);
    }
    bool isReleased() {
        if(digitalRead(pin)==HIGH && state==true) {
            state = false;
            return true;
        }
        if(digitalRead(pin)==LOW) 
            state = true;
        return false;
    }
    Pinout::Buttons getType() {
        return type;
    }
};

#endif