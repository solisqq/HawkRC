#ifndef HCALLBACK_H
#define HCALLBACK_H
#include "Arduino.h"
#include "HSignal.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"

class Signals {
public:
    static HSignal<C4DPoint> RXDataReady;
};
HSignal<C4DPoint> Signals::RXDataReady; 


class HCallback {
public:
    virtual void OnRXRead(C4DPoint& channels){}
};

#endif