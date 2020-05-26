#ifndef HRECEIVER_H
#define HRECEIVER_H
#include "Arduino.h"
#include <HardwareSerial.h>
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallbacks.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"


class HReceiver: public HProcess {
    HardwareSerial rxSerial;
public:
    HReceiver();
    virtual void init();
protected:
    virtual void work();
private:
    uint8_t getSwitchStateByValue(int8_t val, bool threeStates=false);
};
#include "HReceiver.cpp"

#endif