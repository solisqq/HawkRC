#ifndef HSIGNAL_H
#define HSIGNAL_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"

template <typename Type>
class HSignal {
    MSTimer handleTime;
    bool ready = false;
    Type value;
public:
    HSignal(){}
    void emit(Type valueToEmit) {ready = true; value=valueToEmit;}
    bool wasEmited() {return ready;}
    void disable(){ready = false;}
    Type& getValue() {return value;}
};

#endif