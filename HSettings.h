#ifndef HSETTINGS_H
#define HSETTINGS_H
#include "Arduino.h"

class HSettings {
public:
    class Pins {
        public:
        class Receiver {
            public:
            static uint8_t RX;
            static uint8_t TX;
        }
    }
};

HSettings::Pins::Receiver::RX = 16;
HSettings::Pins::Receiver::TX = 17;

#endif