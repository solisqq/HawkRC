#include "HController.h"

HController::HController() {}

void HController::init() {
    engines.Init();
    currentState = &idleState;
}
void HController::work() {
    currentState->keep(engines);
}

void HController::setState(HState* state) {
    if(state!=currentState) {
        currentState = state;
        currentState->init(engines);
        return;
    }
}

void HController::OnPIDRead(C3DPoint<double> pids) {
    currentState->updatePID(pids);
}
void HController::OnStearingRead(C4DPoint<float> stearings) {
    currentState->updateStearing(stearings);
}
void HController::OnRXSwitchesRead(C4DPoint<uint8_t> switches)  {
    if(switches[0]==1) {
        setState(&flyingState);
    } else if(switches[0]==0) {
        setState(&idleState);
    }
}
String HController::toString() {
    return engines.toString();
}