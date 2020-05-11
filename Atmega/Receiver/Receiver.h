#pragma once

#ifndef RECEIVER_H
#define RECEIVER_H
#include "CPPMHandler.h"
//#include "../Timer/Timer.h"

class Receiver {
    unsigned long RSSI_AVG = 0;
    uint8_t RSSI_PIN = 0;
    unsigned long RSSI_TIME = 0;
    unsigned long RSSI_VAL = 0;
    int RSSI_COUNTER = 0;
public:
    Receiver();
    void init(uint8_t interruptPin, uint8_t RSSIPin);
    bool isActive();
    void sendData();
    uint8_t getRSSI();
    void updateRSSI();
    String toString();
};
#include "Receiver.cpp"
#endif