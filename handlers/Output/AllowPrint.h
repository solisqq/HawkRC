#pragma once
#ifndef ALLOWPRINT_H
#define ALLOWPRINT_H
//#include <string>
class AllowPrint {
    bool state=false;
    String name = "";
public:
    AllowPrint():state(false){}
    virtual String toString()=0;
    void debug(bool changeState) {state = changeState;}
    void printItem() {
        if(state) Serial.println(toString());
    }
    void setName(String& cmd) {name = cmd;}
    String& getName() {return name;}
    bool isDebugged(){return state;}
};

#endif