#ifndef HCALLBACK_H
#define HCALLBACK_H
#include "Arduino.h"
#include "Signal.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"


class HCallback {
public:
    Signal<C4DPoint&> RXDataReady();
    virtual void OnRXRead(C4DPoint& channels){}
};

#endif