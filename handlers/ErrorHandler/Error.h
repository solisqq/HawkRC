#pragma once

#ifndef CERROR_H
#define CERROR_H
#include "Arduino.h"

class CError {
    bool showed = false;
public:
    enum ErrorType {
        Warning = 0,
        Error = 1,
        Critical = 2
    };
    enum ErrorLed {
        SoftwareLed = 1,
        RXLed = 2,
        BatteryLed = 4,
        IMULed = 8
    };
    void active();
    void disactive();
    bool isActive();
    String text = "";
    ErrorType type = ErrorType::Warning;
    ErrorLed eled = ErrorLed::SoftwareLed;
    CError(ErrorType errorType, String errorText, ErrorLed errorLed=ErrorLed::SoftwareLed);

};
#include "Error.cpp"

#endif