#ifndef HSTATE_FLYING_H
#define HSTATE_FLYING_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/Engines.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/HState.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallbacks.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"

class StateFlying: public HState {
public:

    C4DPoint<int> Stear_values;
    List<C3DPoint<float>> PID_values;

    StateFlying() {}
    virtual void init(Engines &engines) {
        PID_values.clear();
        engines.SetSpeedAll(HSettings::EngineValues::START);
    }
    virtual void keep(Engines &engines) {
        C3DPoint<float> avgPid(0);
        if(PID_values.count()<=0) 
            return;

        for(List<C3DPoint<float>>::Node* it = PID_values.top(); it!=nullptr; it=it->next) {
            avgPid = avgPid + it->val;
        } 
        avgPid = avgPid/PID_values.count();

        engines.SetSpeedAll(
            Stear_values[0] + avgPid.X() + avgPid.Y() + avgPid.Z(),//FRONT_LEFT
            Stear_values[0] - avgPid.X() + avgPid.Y() - avgPid.Z(),//FRONT_RIGHT
            Stear_values[0] + avgPid.X() - avgPid.Y() - avgPid.Z(),//BACK_LEFT
            Stear_values[0] - avgPid.X() - avgPid.Y() + avgPid.Z()//BACK_RIGHT
        );
        PID_values.clear();
    }
    virtual void updatePID(C3DPoint<double> pid) {
        if(PID_values.count()>=6) PID_values.popFront();
        PID_values.pushBack(pid.toFloat());
    }
    virtual void updateStearing(C4DPoint<float> channels) {
        Stear_values = channels.toInt();
    }
};

#endif