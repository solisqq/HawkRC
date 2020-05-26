#ifndef HPROCESS_H
#define HPROCESS_H
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"

class HProcess {
    MSTimer ptimer;
    String processName;
public:
    HProcess() {}
    void start(unsigned long frequency, String name) {
        ptimer.start(1000/frequency);
        processName = name;
        init();
    }
    void run() {
        if(ptimer.isTimeout())
            work();
    }
    bool isReadyToHandle() {return ptimer.isTimeout();}
    String getName() {return processName;}
protected:
    virtual void work()=0;
    virtual void init()=0;
};

#endif