#ifndef HRECEIVER_H
#define HRECEIVER_H
#include "Arduino.h"
#include <HardwareSerial.h>
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallback.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"


class HReceiver: public HProcess {
    HardwareSerial receiverSerial(2);
public:
    virtual void init() {
        Serial2.begin()//tu skończone
    }
    virtual void OnRXRead(C4DPoint& channels){

    }
};

#endif