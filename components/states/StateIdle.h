#ifndef HSTATE_IDLE_H
#define HSTATE_IDLE_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/Engines.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/HState.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"

class StateIdle: public HState {
public:
    StateIdle() {}
    virtual void init(Engines &engines) {
        engines.StopAll();
    }
    virtual void keep(Engines &engines) {
        engines.StopAll();
    }
    virtual void updatePID(C3DPoint<double>){}
    virtual void updateStearing(C4DPoint<float>){}
};

#endif