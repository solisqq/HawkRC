#pragma once

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "ErrorSrc.h"
#include "Error.h"
class ErrorHandler {
    List<CError*> errors;
    List<ErrorSrc*> sources;
public:
    
    List<CError*>& getErrors(); 
    bool raise(CError &error);
    bool cancel(CError &error);
    void update();
    void addSource(ErrorSrc *err_src);
};
ErrorHandler errorHandler;
#include "ErrorHandler.cpp"

#endif