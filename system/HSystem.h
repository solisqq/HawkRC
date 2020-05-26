#ifndef HSYSTEM_H
#define HSYSTEM_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "HProcess.h"
#include "HCallback.h"

class HSystem {
    List<HProcess*> processes;
public:
    HSystem(){}
    void addProcess(HProcess *processToAdd, unsigned long frequency, String name) {
        processes.pushBack(processToAdd);
        processToAdd->start(frequency, name);
    }
    void operate(){
        for(List<HProcess*>::Node* it=processes.top(); it!=nullptr; it=it->next) {
            it->val->run();
            if(Signals::RXConnectionSwitchState.wasEmited()) {
                it->val->OnRXConnectionChange(Signals::RXConnectionSwitchState.getValue());
            }
            if(Signals::RXSwitchesReady.wasEmited()) {
                it->val->OnRXSwitchesRead(Signals::RXSwitchesReady.getValue());
            }
            if(Signals::RXAxisReady.wasEmited()) {
                it->val->OnRXAxisRead(Signals::RXAxisReady.getValue());
            }
            if(Signals::SteeringReady.wasEmited()) {
                it->val->OnStearingRead(Signals::SteeringReady.getValue());
            }
            //CHANGE HERE
        }
        //CHANGE HERE
        Signals::RXAxisReady.disable();
        Signals::RXSwitchesReady.disable();
        Signals::SteeringReady.disable();
        Signals::RXConnectionSwitchState.disable();
        
    }
};

#endif