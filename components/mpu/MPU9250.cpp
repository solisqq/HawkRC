#include "MPU9250.h"

MPU9250::MPU9250(uint8_t SCK, uint8_t MOSI, uint8_t MISO, uint8_t MPU_CS) : MPU_SCK(SCK), MPU_MOSI(MOSI), MPU_MISO(MISO), MPU_CS(MPU_CS) {}

void MPU9250::init() {
    cummulatedGyro.setMaxSize(8);
    _spi = new SPIClass();
    _spi->begin(MPU_SCK, MPU_MISO, MPU_MOSI);
    _spi->setFrequency(20000000);
    _spi->setClockDivider(SPI_CLOCK_DIV2);
    pinMode(MPU_CS, OUTPUT);
    digitalWrite(MPU_CS, HIGH);
    writeRegister(0x6B, 0x80); //RESET
    delay(1);
    if (whoAmI() != 0x73) {
        Serial.println("Failed to initialize MPU9250. Reeboting...");
        delay(2000);
        ESP.restart();
    }
    delay(1);
    writeRegister(0x6C, 0x00);//ENable gyro and accel
    //GYRO 8800Hz, No DLPF
    writeRegister(0x1A, 0x00);
    writeRegister(0x1B, 0x00);
    //ENABLE INTERRUPTS
    writeRegister(0x37, 0x00);
    writeRegister(0x38, 0x01);
    //100HZ 16bits
    //ACCEL 4G range
    writeRegister(0x1C, 0x02); //0x08 -- 16g // now 4g
    //Accel 100HZ
    writeRegister(0x1D, 0x00); //0x0A -- 100hz now 1000HZ
    //gyroFreqCounter.enablePrinting(true, "G");
    //accelFreqCounter.enablePrinting(true, "A");
    //gyroCumulated.setMaxSize(8);
    //accelCumulated.setMaxSize(10);

    /*if (settings.filtering.imu.gyroLowPass.get() > 20)
        gyroRaw.addFilters(new ButterworthLP<int16_t>(1000, settings.filtering.imu.gyroLowPass.get()));
    if (settings.filtering.imu.gyroNotch.get() > 20)
        gyroRaw.addFilters(
            new BiquadBS<int16_t>(
                1000,
                settings.filtering.imu.gyroNotch.get(),
                settings.filtering.imu.gyroNotchWidth.get(),
                settings.filtering.imu.gyroNotch.get()
                ));

    if (settings.filtering.imu.gyroNotch2.get() > 20)
        gyroRaw.addFilters(
            new BiquadBS<int16_t>(
                1000,
                settings.filtering.imu.gyroNotch2.get(),
                settings.filtering.imu.gyroNotchWidth2.get(),
                settings.filtering.imu.gyroNotch2.get()
                ));*/    
}

bool MPU9250::isGyroReady() {
    if (gyroReady && isWriting == false) {
        gyroReady = false;
        return true;
    }
    return false;
}

bool MPU9250::isAccelReady()
{
    if (accelReady && isWriting==false) {
        accelReady = false;
        return true;
    }
    return false;
}

C3DPoint<int16_t> MPU9250::getGyro()
{
    return gyroRaw;
}

C3DPoint<int16_t> MPU9250::getAccel()
{
    return accelRaw;
}

/*List<C3DPoint<int16_t>>& MPU9250::getCumulatedGyro()
{
    return gyroCumulated;
}*/

void MPU9250::readRawGyro() {
    /*if (gyroReady) {
        cummulatedGyro.pushBack(gyroRaw);
    }*/
    isWriting = true;
    C3DPoint<int16_t> backup;
    if (gyroReady) backup = gyroRaw;
    readRegisters(0x43, 6, _buffer);
    gyroRaw.setX((((int16_t)_buffer[0]) << 8) | _buffer[1]);
    gyroRaw.setY((((int16_t)_buffer[2]) << 8) | _buffer[3]);
    gyroRaw.setZ((((int16_t)_buffer[4]) << 8) | _buffer[5]);
    if (gyroReady) {
        gyroRaw = gyroRaw + backup; Serial.println("G");
    }
    isWriting = false;
    //gyroFreqCounter.calc();
    gyroReady = true;
}

void MPU9250::readRawAccel()
{
    readRegisters(0x3B, 6, _buffer);
    isWriting = true;
    accelRaw.setX((((int16_t)_buffer[0]) << 8) | _buffer[1]);
    accelRaw.setY((((int16_t)_buffer[2]) << 8) | _buffer[3]);
    accelRaw.setZ((((int16_t)_buffer[4]) << 8) | _buffer[5]);
    isWriting = false;
    accelFreqCounter.calc();
    accelReady = true;
}

int MPU9250::readRegisters(uint8_t subAddress, uint8_t count, uint8_t* dest) {
    _spi->beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE3));
    digitalWrite(MPU_CS, LOW); // select the MPU9250 chip
    _spi->transfer(subAddress | 0x80); // specify the starting register address
    for (uint8_t i = 0; i < count; i++) {
        dest[i] = _spi->transfer(0x00); // read the data
    }
    digitalWrite(MPU_CS, HIGH); // deselect the MPU9250 chip
    _spi->endTransaction(); // end the transaction
    return 1;
}

int MPU9250::writeRegister(uint8_t subAddress, uint8_t data) {
    _spi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3)); // begin the transaction
    digitalWrite(MPU_CS, LOW); // select the MPU9250 chip
    _spi->transfer(subAddress); // write the register address
    _spi->transfer(data); // write the data
    digitalWrite(MPU_CS, HIGH); // deselect the MPU9250 chip
    _spi->endTransaction(); // end the transaction
    delay(5);
    readRegisters(subAddress, 1, _buffer);
    if (_buffer[0] == data) {
        return 1;
    }
    else {
        return -1;
    }
}

bool MPU9250::isInterrupt() {
    readRegisters(0x3A, 1, _buffer);
    return ((_buffer[0] & 1) == 1);
}

int MPU9250::whoAmI() {
    if (readRegisters(0x75, 1, _buffer) < 0) return -1;
    return _buffer[0];
}

bool MPU9250::work() {
    if (isInterrupt()) {
        readRawGyro();
        if (accelCounter >= 7) {
            accelCounter = 0;
            readRawAccel();
        } else accelCounter++;
    }
    return true;
}
/*
bool MPU9250::isDataReady() {
    readRegisters(0x3A, 1, _buffer);
    if ((_buffer[0] & 1) == 1) {
        //if (accelCounter > 18) readRawAccel();
        //else if (accelReady == false) accelCounter++;
        return true;
    }
    return false;
}
void MPU9250::readRawAccel() {
    readRegisters(0x3B, 6, _buffer);
    accelRaw.setX((((int16_t)_buffer[0]) << 8) | _buffer[1]);
    accelRaw.setY((((int16_t)_buffer[2]) << 8) | _buffer[3]);
    accelRaw.setZ((((int16_t)_buffer[4]) << 8) | _buffer[5]);
    accelReady = true;
}
C3DPoint<int16_t>& MPU9250::getAccel()
{
    return accelRaw;
}
bool MPU9250::isAccelReady() {
    if (accelReady) {
        accelReady = false;
        accelCounter = 0;
        return true;
    }
    return false;
}

*/
