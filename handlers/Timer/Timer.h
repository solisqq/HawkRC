#pragma once

#ifndef CTIMER_H
#define CTIMER_H
#include "Arduino.h"

class CTimer {
protected:
    unsigned long timeout = 0;
    unsigned long duration = 0;
    virtual void restart()=0;
    CTimer(){}
public:
    virtual void start(unsigned int duration)=0;
    void stop(int duration) {timeout = 0;}
    virtual bool isTimeout()=0;
};

class MSTimer: public CTimer {
protected:
    virtual void restart() {
        timeout = millis()+duration;
    }
public:
    MSTimer():CTimer() {}
    virtual void start(unsigned int durationInMS) {
        duration = durationInMS;
        restart();
    }
    virtual bool isTimeout() {
        if(timeout==0) 
            return false;

        if(millis()>timeout){
            restart();
            return true;
        }
        return false;
    }
};

class USTimer: public CTimer {
protected:
    virtual void restart() {
        timeout = micros()+duration;
    }
public:
    USTimer():CTimer() {}
    virtual void start(unsigned int durationInMS) {
        duration = durationInMS;
        restart();
    }
    virtual bool isTimeout() {
        if(timeout==0) 
            return false;

        if(micros()>timeout){
            restart();
            return true;
        }
        return false;
    }
};

#endif