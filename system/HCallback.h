#ifndef HCALLBACK_H
#define HCALLBACK_H
#include "Arduino.h"
#include "HSignal.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"

class HCallback {
public:
    virtual void OnRXAxisRead(C4DPoint<int8_t>&);
    virtual void OnRXSwitchesRead(C4DPoint<uint8_t>&);
    virtual void OnStearingRead(C4DPoint<float>&);
    virtual void OnRXConnectionChange(bool&);
    //CHANGE HERE
};

class Signals {
public:
    static HSignal<C4DPoint<int8_t>> RXAxisReady;
    static HSignal<C4DPoint<uint8_t>> RXSwitchesReady;
    static HSignal<C4DPoint<float>> SteeringReady;
    static HSignal<bool> RXConnectionSwitchState;
    //CHANGE HERE
};
HSignal<C4DPoint<int8_t>> Signals::RXAxisReady;
HSignal<C4DPoint<uint8_t>> Signals::RXSwitchesReady;
HSignal<C4DPoint<float>> Signals::SteeringReady;
HSignal<bool> Signals::RXConnectionSwitchState;
//CHANGE HERE



class HCallback {
public:
    
    virtual void OnRXAxisRead(C4DPoint<int8_t>& channels){}
    virtual void OnRXSwitchesRead(C4DPoint<uint8_t>& channels){}
    virtual void OnStearingRead(C4DPoint<float>& channels){}
    virtual void OnRXConnectionChange(bool& state){}
    //CHANGE HERE
};

#endif