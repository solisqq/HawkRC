##pragma once

#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"

class Debugger {
    List<CError*> errors;
    List<ErrorSrc*> sources;
public:
    
    List<CError*>& getErrors(); 
    void raise(CError &error);
    void cancel(CError &error);
    void update();
    void addSource(ErrorSrc *err_src);
};
ErrorHandler errorHandler;
#include "Debugger.cpp"

#endif