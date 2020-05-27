#pragma once
#ifndef ALLOWPRINT_H
#define ALLOWPRINT_H
//#include <string>
class AllowPrint {
    bool state=false;
public:
    AllowPrint():state(false){}
    virtual String toString()=0;
    void debug(bool changeState) {state = changeState;}
    void printItem() {
        if(state) Serial.println(toString());
    }
};

#endif