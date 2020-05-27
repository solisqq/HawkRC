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
        for(List<AllowPrint*>::Node *it = printables.top(); it!=nullptr; it=it->next) 
            it->val->printItem();
    }
public:
    void addPrintable(AllowPrint* printable) {
        printables.pushBack(printable);
    }
};

#endif