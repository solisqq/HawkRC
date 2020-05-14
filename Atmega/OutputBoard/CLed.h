#pragma once
#ifndef CLED_H
#define CLED_H
#include "Arduino.h"

class CLed {
    bool invertedLogic=false;
    uint8_t pin = 0;
public:
    CLed();
    void init(uint8_t pinID, bool invertLogic=false);
    void turnOn();
    void turnOff();
    void pwm(uint8_t pwmValue);
};
#include "CLed.cpp"
#endif