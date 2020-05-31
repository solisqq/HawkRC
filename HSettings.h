#ifndef HSETTINGS_H
#define HSETTINGS_H
#include "Arduino.h"

/*
Engines:
12,14,23,19
Bat:
D4
*/

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
        static int8_t DEAD_ZONE;
        static uint8_t LOW_RSI_SIGNAL;

        static int8_t MAX_VAL;
        static int8_t MIN_VAL;
    };
    class Filtering {
    public:
        class Receiver {
            public:
            static float axisSmoothing;
            static float yawMult;
        };
        class IMU {
            public:
            static float accStrength; 
        };
    };
    class Calibrating {
        public:
        class Gyro {
        public:
            static int precision;
            static float threshold;
        };
    };
};

uint8_t HSettings::Pins::Receiver::RX = 16;
uint8_t HSettings::Pins::Receiver::TX = 17;

int8_t HSettings::RadioValues::LOW_STATE = -90;
int8_t HSettings::RadioValues::MID_STATE = 0;
int8_t HSettings::RadioValues::MID_HIGH_STATE = 5;
int8_t HSettings::RadioValues::MID_LOW_STATE = -5;
int8_t HSettings::RadioValues::HIGH_STATE = 90;
int8_t HSettings::RadioValues::DEAD_ZONE = 2;
uint8_t HSettings::RadioValues::LOW_RSI_SIGNAL = 0;

int8_t HSettings::RadioValues::MAX_VAL = 105;
int8_t HSettings::RadioValues::MIN_VAL = -105;

float HSettings::Filtering::Receiver::axisSmoothing = 0.87;
float HSettings::Filtering::Receiver::yawMult = 0.15;
int HSettings::Calibrating::Gyro::precision = 6000;
float HSettings::Calibrating::Gyro::threshold = 10;

float HSettings::Filtering::IMU::accStrength = 0.035;



#endif