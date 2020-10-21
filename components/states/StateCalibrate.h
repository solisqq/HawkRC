#ifndef HCALIBRATE_STATE_H
#define HCALIBRATE_STATE_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/Engines.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/HState.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"

class StateCalibrate: public HState {
public:
    StateCalibrate() {state = FCStates::State::Calibrate;}
    virtual void init(Engines &engines) {
        Serial.println("Plug in battery for callibration.");
        engines.SetSpeedAll(settings.engineValues.MAXV.get()-1);
        delay(12000);
        Serial.println("Calibration Late....");
        engines.SetSpeedAll(settings.engineValues.MINV.get()+1);
        delay(8000);
    }
    virtual void keep(Engines &engines) {
        engines.StopAll();
    }
    virtual void updatePID(C3DPoint<double>){}
    virtual void updateStearing(C4DPoint<float>){}
};

#endif