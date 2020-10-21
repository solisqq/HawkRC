#ifndef MPU9250_H
#define MPU9250_H

#include <Arduino.h>
#include <SPI.h>
#include <Esp.h>
#include <Esp.cpp>
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HProcess.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/FrequencyCounter.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/FilterableValue.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/ButterworthLP.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/filters/BiquadBS.h"

class MPU9250: public HProcess {
    SPIClass* _spi;
    uint8_t _buffer[21];
    uint8_t MPU_SCK, MPU_MOSI, MPU_MISO, MPU_CS;
    C3DPoint<int16_t> gyroRaw;
    C3DPoint<int16_t> accelRaw;
    int accelCounter = 0;
    bool gyroReady = false;
    bool accelReady = false;
    int gyroCounter=0;
    FrequencyCounter gyroFreqCounter;
    FrequencyCounter accelFreqCounter;
    List<C3DPoint<int16_t>> cummulatedGyro;

    volatile bool isWriting = false;
public:
    MPU9250(uint8_t SCK, uint8_t MOSI, uint8_t MISO, uint8_t MPU_CS);
    void init() override;
    bool work() override;
    bool isGyroReady();
    bool isAccelReady();
    C3DPoint<int16_t> getGyro();
    C3DPoint<int16_t> getAccel();

    bool isInterrupt();
    void readRawGyro();
    void readRawAccel();
    /*
    void clearGyroQueue();
    void clearAccelQueue();
    List<C3DPoint<int16_t>>& getCumulatedGyro();
    List<C3DPoint<int16_t>> getGyroCumulated();
    List<C3DPoint<int16_t>> getAccelCumulated();*/
private:
    int readRegisters(uint8_t subAddress, uint8_t count, uint8_t* dest);
    int writeRegister(uint8_t subAddress, uint8_t data);
    int whoAmI();
};

#include "MPU9250.cpp"
extern MPU9250 mpu(25, 26, 27, 5);

#endif
/*
* 
bool isAccelReady();
static void startTaskImpl(void*);
C3DPoint<int16_t> accelRaw;
int accelCounter = 0;
bool accelReady = false;
void backgroundWorker();
C3DPoint<int16_t>& getAccel();
void readRawAccel();
*/