#pragma once

#ifndef BATTERY_H
#define BATTERY_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/ErrorHandler.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/Error.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Arduino/libraries/Adafruit_GFX_Library/Adafruit_GFX.h"
#include <Adafruit_SSD1306.h>
#include "C:/Users/kamil/Documents/Programming/HawkRC/Atmega/Display/MenuElement.h"
//#include "../Timer/Timer.h"

class Battery: public CMenuElement {
    CError batError = CError(CError::ErrorType::Error, "BAT", CError::ErrorLed::BatteryLed);
    int8_t batLevel=0;
public:
    Battery();
    void init();
    String toString();
    virtual void paint();
    virtual void buttonPushed(Pinout::Buttons buttonID);
    void setLevel(int8_t val);
};
#include "Battery.cpp"
#endif