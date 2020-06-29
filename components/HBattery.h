#ifndef HBATTERY_H
#define HBATTERY_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallbacks.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/FilterableValue.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/SimpleIR.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"
#include <Wire.h>
#include "BMI088/BMI088.h"


class HBattery: public HProcess, public AllowPrint {
    FilterableValue<float> batteryLevel;
public:
    HBattery();
    virtual void init();
    int8_t getLevel();
protected:
    virtual void work();
    virtual String toString();
};
#include "HBattery.cpp"

#endif