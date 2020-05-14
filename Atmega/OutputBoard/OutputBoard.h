#pragma once

#ifndef OUTPUT_BOARD_H
#define OUTPUT_BOARD_H
#include "Arduino.h"
#include "CLed.h"
#include "Pinout.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/ErrorSrc.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/Error.h"
class OutputBoard: public ErrorSrc {
    CLed BatteryLed;
    CLed RxLed;
    CLed IMULed;
    CLed SOFTLed;
    CLed Buzzer;

    CLed *Leds[4];
public:
    OutputBoard();
    void init();
    void TurnOffLeds();
    void TurnOnLeds();
    virtual void showErrors(List<CError*>& errors);
    void TestLeds();
};
#include "OutputBoard.cpp"

#endif