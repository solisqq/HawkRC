#ifndef HCALLBACK_H
#define HCALLBACK_H
#include "Arduino.h"
#include "HSignal.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"

class HCallback {
public:
    
    virtual void OnRXAxisRead(C4DPoint<int8_t>& channels){}
    virtual void OnRXSwitchesRead(C4DPoint<uint8_t>& channels){}
    virtual void OnStearingRead(C4DPoint<float>& channels){}
    virtual void OnRXConnectionChange(bool& state){}
    //CHANGE HERE
};

#endif