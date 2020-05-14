#pragma once

#ifndef CSIGNAL_H
#define CSIGNAL_H
#include "Arduino.h"

class CSignal {
public:
    bool handled=true;
    CSignal() {handled=true;}
};

#endif