#pragma once

#ifndef ERROR_SRC_H
#define ERROR_SRC_H
#include "Error.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"

class ErrorSrc {
public:
    virtual void showErrors(List<CError*>& errors);
};

#endif