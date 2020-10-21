#ifndef __BOSCH_BMI088_H__
#define __BOSCH_BMI088_H__

#include <Arduino.h>
#include <Wire.h>
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HProcess.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/FrequencyCounter.h"


#define BMI088_ACC_ADDRESS          0x19

#define BMI088_ACC_CHIP_ID          0x00 // Default value 0x1E
#define BMI088_ACC_ERR_REG          0x02
#define BMI088_ACC_STATUS           0x03

#define BMI088_ACC_X_LSB            0x12
#define BMI088_ACC_X_MSB            0x13
#define BMI088_ACC_Y_LSB            0x14
#define BMI088_ACC_Y_MSB            0x15
#define BMI088_ACC_Z_LSB            0x16
#define BMI088_ACC_Z_MSB            0x17

#define BMI088_ACC_SENSOR_TIME_0    0x18
#define BMI088_ACC_SENSOR_TIME_1    0x19
#define BMI088_ACC_SENSOR_TIME_2    0x1A

#define BMI088_ACC_INT_STAT_1       0x1D

#define BMI088_ACC_TEMP_MSB         0x22
#define BMI088_ACC_TEMP_LSB         0x23

#define BMI088_ACC_CONF             0x40
#define BMI088_ACC_RANGE            0x41

#define BMI088_ACC_INT1_IO_CTRL     0x53
#define BMI088_ACC_INT2_IO_CTRL     0x54
#define BMI088_ACC_INT_MAP_DATA     0x58

#define BMI088_ACC_SELF_TEST        0x6D
#define BMI088_ACC_PWR_CONF         0x7C
#define BMI088_ACC_PWR_CTRl         0x7D
#define BMI088_ACC_SOFT_RESET       0x7E
#define BMI088_GYRO_CHIP_ID             0x00 // Default value 0x0F

#define BMI088_GYRO_RATE_X_LSB          0x02

enum device_type_t // device type
{
	ACC = 0x19, // 
	GYRO = 0x69, // 
};

enum acc_scale_type_t // measurement rage
{
	RANGE_3G = 0x00, // 
	RANGE_6G = 0x01, // 
	RANGE_12G = 0x02, // 
    RANGE_24G = 0x03, // 
};

enum acc_odr_type_t // output data rate
{
	ODR_12 = 0x05, // 
	ODR_25 = 0x06, // 
	ODR_50 = 0x07, // 
    ODR_100 = 0x08, // 
    ODR_200 = 0x09, // 
    ODR_400 = 0x0A, // 
    ODR_800 = 0x0B, // 
    ODR_1600 = 0x0C, // 
};

enum acc_power_type_t // power mode
{
	ACC_ACTIVE = 0x00, // 
    ACC_SUSPEND = 0x03, // 
};

class BMI088: public HProcess
{

    private:
        C3DPoint<int16_t> accel;
        C3DPoint<int16_t> gyro;
        bool accelReady = false;
        bool gyroReady = false;

        FrequencyCounter accelFCounter;
        FrequencyCounter gyroFCounter; 

        int gyroCounter = 0;

        
    public:
        BMI088(void);
        void init() override;
        bool work() override;

        bool isConnection(void);
        bool isAccelReady();
        bool isGyroReady();

        C3DPoint<int16_t>& getAccel();
        C3DPoint<int16_t>& getGyro();

    private:
        bool isAccelDataReady();
        bool isGyroDataReady();
        void receiveGyro();
        void receiveAccel();
        void write8(uint8_t destination, uint8_t reg, uint8_t val);
        uint8_t read8(uint8_t destination, uint8_t reg);
        void read(uint8_t destination, uint8_t reg, uint8_t* buf, uint16_t len);
        void setAccPoweMode(acc_power_type_t mode);
        void setAccScaleRange(acc_scale_type_t range);
        void setAccOutputDataRate(acc_odr_type_t odr);

        uint8_t getAccID(void);
        void resetAcc(void);

        double accRange;
        uint8_t devAddrAcc;
};
#include "BMI088.cpp"
extern BMI088 bmi088;
#endif
