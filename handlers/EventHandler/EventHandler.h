#pragma once

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include "SlotHandler.h"
#include "Slot.h"
#include "Signal.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"

class EventHandler {
    List<CSlotHandler*> slotsToHandle;
public:
    void update() {
        if(slotsToHandle.count()<=0) return;
        for (List<CSlotHandler*>::Node* it = slotsToHandle.top(); it!=nullptr; it=it->next) 
            it->val->handle();
    }
    void addHandler(CSlotHandler* handler) {
        slotsToHandle.pushBack(handler);
    }
};
EventHandler eventHandler;
#endif