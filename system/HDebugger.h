#ifndef HDEBUGGER_H
#define HDEBUGGER_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HProcess.h"


class HDebugger: public HProcess {
    List<AllowPrint*> printables;
protected:
    virtual void init() {}
    virtual void work() {
        if(Serial.available()) {
            String cmd = "";
            while(Serial.available()) {
                char c = Serial.read();
                cmd+=c;
            }
            for(List<AllowPrint*>::Node *it = printables.top(); it!=nullptr; it=it->next) 
                if(it->val->getName().length()>1)
                    if(it->val->getName()==cmd) 
                        it->val->debug(!it->val->isDebugged());
        }
        
        for(List<AllowPrint*>::Node *it = printables.top(); it!=nullptr; it=it->next) 
            it->val->printItem();
    }
public:
    void addPrintable(AllowPrint* printable, String cmd="") {
        printables.pushBack(printable);
        printable->setName(cmd);
    }
};

#endif