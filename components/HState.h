#ifndef HSTATE_H
#define HSTATE_H
#include "Arduino.h"
#include "Engines.h"

class HState {
public:
    virtual void init(Engines &engines)=0;
    virtual void keep(Engines &engines)=0;
    virtual void updatePID(C3DPoint<double>)=0;
    virtual void updateStearing(C4DPoint<float>)=0;
};

#endif