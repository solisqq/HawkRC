#ifndef HDROP_STATE_H
#define HDROP_STATE_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/Engines.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/HState.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"

class DropState: public HState {
public:
    DropState() {state = FCStates::State::Drop;}
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