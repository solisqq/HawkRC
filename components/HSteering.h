#ifndef HSTEERING_H
#define HSTEERING_H
#include "Arduino.h"
#include <HardwareSerial.h>
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/FilterableValue.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallback.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/SimpleIR.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/Mapper.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/InfiniteAdd.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/DeadZoneFilter.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"


class HSteering: public HProcess {
    FilterableValue<float> throttle;
    FilterableValue<float> yaw;
    FilterableValue<float> pitch;
    FilterableValue<float> roll;
public:
    HSteering();
    virtual void init();
    virtual void work(){}
    virtual void OnRXAxisRead(C4DPoint<int8_t>& channels);
    virtual void OnStearingRead(C4DPoint<float>& channels);
};
#include "HSteering.cpp"

#endif