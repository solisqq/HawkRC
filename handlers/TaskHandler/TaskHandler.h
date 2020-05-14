#pragma once

#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H
#include "Arduino.h"
//void loop();

class TaskHandler {
public:
    void delayMS(unsigned long time) {
        loop();
    }
};

#endif