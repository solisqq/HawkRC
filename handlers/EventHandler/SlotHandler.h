#pragma once

#ifndef CSLOT_HANDLER_H
#define CSLOT_HANDLER_H
#include "Signal.h"
#include "Slot.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"

class CSlotHandler {
public:
    virtual void handle()=0;
};

#endif