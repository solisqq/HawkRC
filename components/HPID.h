#ifndef HPID_H
#define HPID_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallbacks.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/FilterableValue.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/ButterworthLP.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/InfiniteAdd.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/Offset.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/LimitsFilter.h"
#include <Wire.h>
#include "BMI088/BMI088.h"


class HPID: public HProcess, public HCIMURead, public HCStearingRead, public AllowPrint, public HCRXSwitchesRead {
public:
    C3DPoint<double> Proportional;
    C3DPoint<double> Integral;
    C3DPoint<double> Derivative;
    C3DPoint<double> cerror;
    C3DPoint<double> desiredAngles;
    C3DPoint<double> values;
    HPID();
    double prevTime=0;
    virtual void init();
protected:
    virtual void work();
    virtual void OnIMURead(C3DPoint<double>);
    virtual void OnStearingRead(C4DPoint<float>); 
    virtual String toString();
    void OnRXSwitchesRead(C4DPoint<uint8_t>) override;
};
#include "HPID.cpp"

#endif