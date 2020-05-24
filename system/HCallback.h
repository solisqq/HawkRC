#ifndef HCALLBACK_H
#define HCALLBACK_H
#include "Arduino.h"
#include "HSignal.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"

class Signals {
public:
    static HSignal<C4DPoint<float>> RXAxisReady;
    static HSignal<C4DPoint<uint8_t>> RXSwitchesReady;
};
HSignal<C4DPoint<float>> Signals::RXAxisReady;
HSignal<C4DPoint<uint8_t>> Signals::RXSwitchesReady;


class HCallback {
public:
    virtual void OnRXAxisRead(C4DPoint<float>& channels){}
    virtual void OnRXSwitchesRead(C4DPoint<uint8_t>& channels){}
};

#endif