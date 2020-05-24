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
        };
    };
    class RadioValues {
        public:
        static int8_t LOW_STATE;
        static int8_t HIGH_STATE;
        static int8_t MID_STATE;
        static int8_t MID_HIGH_STATE;
        static int8_t MID_LOW_STATE;
    };
};

uint8_t HSettings::Pins::Receiver::RX = 16;
uint8_t HSettings::Pins::Receiver::TX = 17;

int8_t HSettings::RadioValues::LOW_STATE = -90;
int8_t HSettings::RadioValues::MID_STATE = 0;
int8_t HSettings::RadioValues::MID_HIGH_STATE = 5;
int8_t HSettings::RadioValues::MID_LOW_STATE = -5;
int8_t HSettings::RadioValues::HIGH_STATE = 90;



#endif