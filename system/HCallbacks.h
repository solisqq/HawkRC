#ifndef HCALLBACKS_H
#define HCALLBACKS_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"

template <typename cType>
class HCallback {
public:
    virtual void runCallback(cType);
};

template <typename Type>
class HSignal {
    List<HCallback<Type>*> callbacks;
    Type value;
public:
    HSignal(){}
    void emit(Type valueToEmit) {
        value = valueToEmit;
        for(int i=0; i<callbacks.count(); i++) {
            callbacks[i]->runCallback(value);
        }
        //for(List<HCallback<Type>*>::Node* it = callbacks.top(); it!=nullptr; it=it->next) 
            //it->val->runCallback(valueToEmit);
    }
    void addCallback(HCallback<Type>* callback) {
        callbacks.pushBack(callback);
    }
    Type& getValue() {return value;}
};

class Signals {
public:
    static HSignal<C4DPoint<int8_t>> RXAxisReady;
    static HSignal<C4DPoint<uint8_t>> RXSwitchesReady;
    static HSignal<C4DPoint<float>> StearingReady;
    static HSignal<bool> RXConnectionSwitchState;
    static HSignal<C3DPoint<float>> GyroReady;
    //CHANGE HERE
};

HSignal<bool> Signals::RXConnectionSwitchState;
class HCRXConnectionChange: public HCallback<bool> {
protected:
    virtual void OnRXConnectionChange(bool)=0;
    HCRXConnectionChange(){Signals::RXConnectionSwitchState.addCallback(this);}
public:
    void runCallback(bool val) {OnRXConnectionChange(val);}
    ~HCRXConnectionChange(){}
};

HSignal<C4DPoint<int8_t>> Signals::RXAxisReady;
class HCRXAxisRead: public HCallback<C4DPoint<int8_t>> {
protected:
    virtual void OnRXAxisRead(C4DPoint<int8_t>)=0;
    HCRXAxisRead(){Signals::RXAxisReady.addCallback(this);}
public:
    void runCallback(C4DPoint<int8_t> val) {OnRXAxisRead(val);}
    ~HCRXAxisRead(){}
};

HSignal<C4DPoint<uint8_t>> Signals::RXSwitchesReady;
class HCRXSwitchesRead: public HCallback<C4DPoint<uint8_t>> {
protected:
    virtual void OnRXSwitchesRead(C4DPoint<uint8_t>)=0;
    HCRXSwitchesRead(){Signals::RXSwitchesReady.addCallback(this);}
public:
    void runCallback(C4DPoint<uint8_t> val) {OnRXSwitchesRead(val);}
    ~HCRXSwitchesRead(){}
};

HSignal<C4DPoint<float>> Signals::StearingReady;
class HCStearingRead: public HCallback<C4DPoint<float>> {
protected:
    virtual void OnStearingRead(C4DPoint<float>)=0;
    HCStearingRead(){Signals::StearingReady.addCallback(this);}
public:
    void runCallback(C4DPoint<float> val) {OnStearingRead(val);}
    ~HCStearingRead(){}
};

HSignal<C3DPoint<float>> Signals::GyroReady;
class HCGyroRead: public HCallback<C3DPoint<float>> {
protected:
    virtual void OnGyroRead(C3DPoint<float>)=0;
    HCGyroRead(){Signals::GyroReady.addCallback(this);}
public:
    void runCallback(C3DPoint<float> val) {OnGyroRead(val);}
    ~HCGyroRead(){}
};

/*template:
HSignal<Type> Signals::SignalName;
class objectName: public HCallback<Type> {
protected:
    virtual void funcName(Type)=0;
    objectName(){Signals::SignalName.addCallback(this);}
public:
    void runCallback(Type val) {funcName(val);}
    ~objectName(){}
};
*/


#endif