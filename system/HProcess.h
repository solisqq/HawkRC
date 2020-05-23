#ifndef HPROCESS_H
#define HPROCESS_H
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallback.h.h"

class HProcess: public HCallback {
    USTimer timer;
    String processName;
public:
    HProcess() {}
    void start(unsigned long frequency, String name) {
        timer.start(1000000/frequency);
        processName = name;
        init();
    }
    String getName() {return processName;}
    virtual void init()=0;
};

#endif