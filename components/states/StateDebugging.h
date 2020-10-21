#include <dummy.h>
#ifndef HDEBBUGING_STATE_H
#define HDEBBUGING_STATE_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/Engines.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/HState.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"

class StateDebugging: public HState {
    int speeds[4] = { 1148, 1148, 1148, 1148 };
public:
    StateDebugging() {state = FCStates::State::Debugging;}
    virtual void init(Engines &engines) {
        engines.SetSpeedAll(settings.engineValues.MINV.get(), settings.engineValues.MINV.get(), settings.engineValues.MINV.get(), settings.engineValues.MINV.get());
        //setSpeed();
    }
    virtual void keep(Engines &engines) {
        engines.SetSpeedAll(speeds[0],speeds[1],speeds[2],speeds[3]);
    }
    void setSpeed(int speed) {
        for (int i = 0; i < 4; i++) speeds[i] = speed;
    }
    void setSpeed(String engineName, int speed) {
        if (engineName == "fl")
            speeds[0] = speed;
        else if (engineName == "fr")
            speeds[1] = speed;
        else if (engineName == "bl")
            speeds[2] = speed;
        else if (engineName == "br")
            speeds[3] = speed;
    }
    virtual void updatePID(C3DPoint<double>){}
    virtual void updateStearing(C4DPoint<float>){}
};

#endif