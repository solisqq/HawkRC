#ifndef HSTATE_TEST_H
#define HSTATE_TEST_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/Engines.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/HState.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"

class StateTest: public HState {
public:
    StateTest() {state = FCStates::State::Test;}
    virtual void init(Engines &engines) {
        delay(3000);
        Serial.println("Test_ Front left");
        engines.SetSpeedAll(settings.engineValues.STARTV.get(),settings.engineValues.MINV.get()+1,settings.engineValues.MINV.get()+1,settings.engineValues.MINV.get()+1);
        delay(5000);
        engines.StopAll();
        delay(1000);
        Serial.println("Test_ Front right");
        engines.SetSpeedAll(settings.engineValues.MINV.get()+1,settings.engineValues.STARTV.get(),settings.engineValues.MINV.get()+1,settings.engineValues.MINV.get()+1);
        delay(5000);
        engines.StopAll();
        delay(1000);
        Serial.println("Test_ Back left");
        engines.SetSpeedAll(settings.engineValues.MINV.get()+1,settings.engineValues.MINV.get()+1,settings.engineValues.STARTV.get(),settings.engineValues.MINV.get()+1);
        delay(5000);
        engines.StopAll();
        delay(1000);
        Serial.println("Test_ Back right");
        engines.SetSpeedAll(settings.engineValues.MINV.get()+1,settings.engineValues.MINV.get()+1,settings.engineValues.MINV.get()+1,settings.engineValues.STARTV.get());
        delay(5000);
        engines.StopAll();
    }
    virtual void keep(Engines &engines) {
        engines.StopAll();
    }
    virtual void updatePID(C3DPoint<double>){}
    virtual void updateStearing(C4DPoint<float>){}
};

#endif