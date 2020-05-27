#ifndef HGYRO_H
#define HGYRO_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallbacks.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/FilterableValue.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/ButterworthLP.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"
#include <Wire.h>
#include "BMI088/BMI088.h"


class HGyro: public HProcess, public HCGyroRead, public AllowPrint {
public:
    FilterableValue<float> X,Y,Z;
    HGyro();
    virtual void init();
protected:
    virtual void work();
    virtual void OnGyroRead(C3DPoint<float>);
    void scanForDevices();
    virtual String toString();
};
#include "HGyro.cpp"

#endif