#pragma once

#ifndef RECEIVER_H
#define RECEIVER_H
#include "CPPMHandler.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/ErrorHandler.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/Error.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Arduino/libraries/Adafruit_GFX_Library/Adafruit_GFX.h"
#include <Adafruit_SSD1306.h>
#include "C:/Users/kamil/Documents/Programming/HawkRC/Atmega/Display/MenuElement.h"
//#include "../Timer/Timer.h"

class Receiver: public CMenuElement {
    unsigned long RSSI_AVG = 0;
    uint8_t RSSI_PIN = 0;
    unsigned long RSSI_TIME = 0;
    unsigned long RSSI_VAL = 0;
    int RSSI_COUNTER = 0;

    CError noRX_Error = CError(CError::ErrorType::Error, "RX", CError::ErrorLed::RXLed);
public:
    Receiver();
    void init(uint8_t interruptPin, uint8_t RSSIPin);
    bool isActive();
    void sendData();
    uint8_t getRSSI();
    void updateRSSI();
    String toString();
    virtual void paint();
    virtual void buttonPushed(Pinout::Buttons buttonID);
};
#include "Receiver.cpp"
#endif