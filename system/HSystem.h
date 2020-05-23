#ifndef HSYSTEM_H
#define HSYSTEM_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "HProcess.h"
#include "HCallback.h"

class HSystem {
public:
    List<HProcess*> processes;
    HSystem(){}
    void addProcess(HProcess *processToAdd, unsigned long frequency, String name) {
        processes.pushBack(processToAdd);
        processToAdd->start(frequency, name)
    }
    void operate(){
        for(List<HProcess*>::Node* it=processes.top(); it!=nullptr; it=it->next) {
            if(Signals::RXDataReady.wasEmited()) {
                it->val->OnRXRead(Signals::RXDataReady.getValue())
            }
        }
    }
};

#endif