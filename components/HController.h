#ifndef HCONTROLLER_H
#define HCONTROLLER_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallbacks.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"
#include "HState.h"
#include "states/StateIdle.h"
#include "states/StateFlying.h"

class HController: public HProcess, public HCPIDRead, public HCStearingRead, public HCRXSwitchesRead, public AllowPrint {
public:
    HState *currentState;
    Engines engines;

    StateIdle idleState;
    StateFlying flyingState;
    
    HController();
    void init() override;
protected:
    void work() override;
    void OnPIDRead(C3DPoint<double>) override;
    void OnStearingRead(C4DPoint<float>) override;
    void OnRXSwitchesRead(C4DPoint<uint8_t>) override;
    String toString() override;
private:
    void setState(HState* state);
};
#include "HController.cpp"

#endif