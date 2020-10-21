#include "BMI088.h"

BMI088::BMI088(void)
{
    devAddrAcc = BMI088_ACC_ADDRESS;
}

void BMI088::init()
{
    Wire.begin(22,21);
    Wire.setClock(400000);
    //gyroFCounter.enablePrinting(true,"GYROR: ");
    //accelFCounter.enablePrinting(true,"ACCELR: ");
    delay(30);
    while(1)
    {
        if(isConnection())
        {
            setAccScaleRange(RANGE_12G); delay(30);
            setAccOutputDataRate(ODR_200); delay(30);
            setAccPoweMode(ACC_ACTIVE); delay(30);
            //write8(ACC, 0x0A, 0x08);//OSR4 0x08-OSR4 0x09-OSR2
            //write8(ACC, 0x08, 0x0A);//accOdr 0x08 - 100, 0x09 - 200
            //write8(ACC, 0x01, 0x02);//range 0x02 - 12g 0x01-6g 0x03
            write8(GYRO, 0x15, 0x80); delay(30); //interrupts
            write8(GYRO, 0x10, 0x02); delay(30); //1000Hz/116Hz cutoff
            write8(GYRO, 0x11, 0x00); delay(30); //Normal mode
            Serial.print("$");
            break;
        }
        delay(2000);
        Serial.print("!");
    }
}

bool BMI088::work() {
    if (!isGyroDataReady()) return false;
    gyroCounter++;
    receiveGyro();
    
    if (gyroCounter >= 5) {
        gyroCounter = 0;
        receiveAccel();
    }
    return true;
}

void BMI088::receiveAccel()
{
    uint8_t buf[6] = { 0 };
    uint16_t ax = 0, ay = 0, az = 0;
    float value = 0;

    read(ACC, BMI088_ACC_X_LSB, buf, 6);

    ax = buf[0] | (buf[1] << 8);
    ay = buf[2] | (buf[3] << 8);
    az = buf[4] | (buf[5] << 8);

    accel.setX((int16_t)ax);
    accel.setY((int16_t)ay);
    accel.setZ((int16_t)az);
    accelReady = true;
    accelFCounter.calc();
}

void BMI088::receiveGyro()
{
    uint8_t buf[6] = { 0 };
    uint16_t gx = 0, gy = 0, gz = 0;
    float value = 0;

    read(GYRO, BMI088_GYRO_RATE_X_LSB, buf, 6);

    gx = buf[0] | (buf[1] << 8);
    gy = buf[2] | (buf[3] << 8);
    gz = buf[4] | (buf[5] << 8);

    gyro.setX((int16_t)gx);
    gyro.setY((int16_t)gy);
    gyro.setZ((int16_t)gz);
    gyroReady = true;
    gyroFCounter.calc();
}


bool BMI088::isAccelReady() {
    if(accelReady==true) {
        accelReady = false;
        return true;
    }
    return false;
}

bool BMI088::isGyroReady() {
    if (gyroReady == true) {
        gyroReady = false;
        return true;
    }
    return false;
}

C3DPoint<int16_t>& BMI088::getAccel()
{
    return accel;
}

C3DPoint<int16_t>& BMI088::getGyro()
{
    return gyro;
}

bool BMI088::isConnection(void)
{
    return ((getAccID() == 0x1E));
}

void BMI088::resetAcc(void)
{
    write8(ACC, BMI088_ACC_SOFT_RESET, 0xB6);
}

uint8_t BMI088::getAccID(void)
{
    return read8(ACC, BMI088_GYRO_CHIP_ID);
}

bool BMI088::isGyroDataReady() {
    return (read8(GYRO, 0x0A) != 0);
}

void BMI088::setAccPoweMode(acc_power_type_t mode)
{
    if(mode == ACC_ACTIVE)
    {
        write8(ACC, BMI088_ACC_PWR_CTRl, 0x04);
        write8(ACC, BMI088_ACC_PWR_CONF, 0x00);
    }
    else if(mode == ACC_SUSPEND)
    {
        write8(ACC, BMI088_ACC_PWR_CONF, 0x03);
        write8(ACC, BMI088_ACC_PWR_CTRl, 0x00);
    }
}

void BMI088::setAccScaleRange(acc_scale_type_t range)
{
    if(range == RANGE_3G) accRange = 3000;
    else if(range == RANGE_6G) accRange = 6000;
    else if(range == RANGE_12G) accRange = 12000;
    else if(range == RANGE_24G) accRange = 24000;
    
    write8(ACC, BMI088_ACC_RANGE, (uint8_t)range);
}

void BMI088::setAccOutputDataRate(acc_odr_type_t odr)
{
    uint8_t data = 0;
    
    data = read8(ACC, BMI088_ACC_CONF);
    data = data & 0xf0;
    data = data | (uint8_t)odr;
    
    write8(ACC, BMI088_ACC_CONF, data);
}

void BMI088::read(uint8_t destination, uint8_t reg, uint8_t *buf, uint16_t len)
{
    Wire.beginTransmission(destination);
    Wire.write(reg);
    Wire.endTransmission();
    
    Wire.requestFrom(static_cast<int>(destination), len);
    while(Wire.available())
    {
        for(uint16_t i = 0; i < len; i ++) buf[i] = Wire.read();
    }
}

void BMI088::write8(uint8_t destination, uint8_t reg, uint8_t val)
{
    Wire.beginTransmission(destination);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
}

uint8_t BMI088::read8(uint8_t destination, uint8_t reg)
{
    uint8_t data = 0;
    Wire.beginTransmission(destination);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(static_cast<int>(destination), 1);
    while (Wire.available())
    {
        data = Wire.read();
    }
    return data;
}

BMI088 bmi088;

/*ax = buf[0] | (buf[1] << 8);
    ay = buf[2] | (buf[3] << 8);
    az = buf[4] | (buf[5] << 8);
    
    value = (int16_t)ax;
    acceleration.X() = accRange * value / 32768;
    
    value = (int16_t)ay;
    acceleration.Y() = accRange * value / 32768;
    
    value = (int16_t)az;
    acceleration.Z() = accRange * value / 32768;
    accelReady = true;
    accelCounter.calc();*/