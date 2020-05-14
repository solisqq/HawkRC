#pragma once

#ifndef PINOUT_H
#define PINOUT_H

class Pinout {
public:
    enum Leds {
        BatteryError = 10,
        RCError = 11,
        IMUError = 12,
        SOFTError = 13
    };
    enum Buttons {
        Left=5,
        Right=7,
        Up=6,
        Down=8
    };
    enum Misc {
        Buzzer=9
    };
};
#endif