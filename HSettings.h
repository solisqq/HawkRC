#ifndef HSETTINGS_H
#define HSETTINGS_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"

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
        static uint8_t Battery; 
        class Engines {
            public:
            static uint8_t frontLeft;
            static uint8_t frontRight;
            static uint8_t backLeft;
            static uint8_t backRight;
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
    class EngineValues {
    public:
        static int MIN;
        static int START;
        static int MAX;
        static int PWMFreq;
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
    class PID {
        public:
        static C3DPoint<double> P;
        static C3DPoint<double> I;
        static C3DPoint<double> D;
        static C3DPoint<double> PID_LIMITS;
        static double OVERALL_LIMIT;
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
int HSettings::Calibrating::Gyro::precision = 3000;
float HSettings::Calibrating::Gyro::threshold = 40;

float HSettings::Filtering::IMU::accStrength = 0.035;

C3DPoint<double> HSettings::PID::P = C3DPoint<double>(4.0, 4.0, 2.5); 
C3DPoint<double> HSettings::PID::I = C3DPoint<double>(0.5, 0.5, 0.3); 
C3DPoint<double> HSettings::PID::D = C3DPoint<double>(2.0, 2.0, 1.5);
C3DPoint<double> HSettings::PID::PID_LIMITS = C3DPoint<double>(300, 150, 500);
double HSettings::PID::OVERALL_LIMIT = 700;

uint8_t HSettings::Pins::Battery = 4;

uint8_t HSettings::Pins::Engines::frontLeft = 12;//12
uint8_t HSettings::Pins::Engines::frontRight = 14;//14
uint8_t HSettings::Pins::Engines::backLeft = 23;//23
uint8_t HSettings::Pins::Engines::backRight = 19;//19

int HSettings::EngineValues::MIN = 1148;
int HSettings::EngineValues::MAX = 1840;
int HSettings::EngineValues::START = 1250;
int HSettings::EngineValues::PWMFreq = 12000;

#endif