#ifndef HSYSTEM_H
#define HSYSTEM_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "HProcess.h"

class HSystem {
    List<HProcess*> processes;
public:
    HSystem(){}
    void addProcess(HProcess *processToAdd, unsigned long frequency, String name) {
        processes.pushBack(processToAdd);
        processToAdd->start(frequency, name);
        Serial.print(".");
    }
    void operate(){
        for(List<HProcess*>::Node* it=processes.top(); it!=nullptr; it=it->next) {
            it->val->run();
        }
    }
};

#endif