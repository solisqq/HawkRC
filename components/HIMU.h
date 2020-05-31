#ifndef HIMU_H
#define HIMU_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallbacks.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/FilterableValue.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/ButterworthLP.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"
#include <Wire.h>
#include "BMI088/BMI088.h"


class HIMU: public HProcess, public HCGyroRead, public AllowPrint, public HCAccRead {
public:
    C3DPoint<double> values;
    unsigned long long prevTime=0;
    HIMU();
    virtual void init();
protected:
    virtual void work();
    virtual void OnGyroRead(C3DPoint<float>);
    virtual void OnAccRead(C3DPoint<float>);
    virtual String toString();
};
#include "HIMU.cpp"

#endif