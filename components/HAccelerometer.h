#ifndef HACCELEROMETER_H
#define HACCELEROMETER_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallbacks.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/FilterableValue.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/Offset.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"
#include <Wire.h>
#include "BMI088/BMI088.h"
#define MATH_PI 3.1415

class HAccelerometer: public HProcess, public HCAccRead, public AllowPrint {
public:
    C3DPoint<float> values;
    HAccelerometer();
    virtual void init();
protected:
    virtual void work();
    virtual void OnAccRead(C3DPoint<float>);
    virtual String toString();
    void calibrate();
};
#include "HAccelerometer.cpp"

#endif