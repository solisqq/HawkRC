#pragma once

#ifndef CSLOT_H
#define CSLOT_H
#include "Signal.h"

class CSlot {
    CSignal *signal = nullptr;
public:
    CSlot(){}
    void connect(CSignal &csignal){
        signal = &csignal;
        signal->handled = false;
    }
    bool checkAndHandle() {
        if(signal->handled==true) return true;
        signal->handled = true;
        return false;
    }
    bool isHandled() {
        return signal->handled;
    }
};

#endif