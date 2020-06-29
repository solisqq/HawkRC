#include "HGyro.h"

HGyro::HGyro():values(true){}

void HGyro::init(){
    Wire.begin(22,21);
    Wire.setClock(400000);
    while(1)
    {
        if(bmi088.isConnection())
        {
            bmi088.initialize();
            Serial.print("|");
            break;
        }
        delay(2000);
        Serial.println("BMI088 connection failed.");
    }
    calibrate();
    values.addFilters(new ButterworthLP<float>(1000,80));
}
void HGyro::work(){
    //if(!bmi088.isGyroDataReady()) return;
    values.updateFilters(bmi088.getGyroscope());
    Signals::GyroReady.emit(values);
}

void HGyro::OnGyroRead(C3DPoint<float> gyroData) {
    //Serial.println(gyroData.toString());
}

void HGyro::calibrate() {
    C3DPoint<double> sums;
    C3DPoint<float> prev;
    prev = bmi088.getGyroscope();
    delay(10);
    for(int i=0; i<HSettings::Calibrating::Gyro::precision; i++) {
        C3DPoint<float> gyroData = bmi088.getGyroscope();
        C3DPoint<float> motion = gyroData - prev;
        prev = gyroData;
        if((abs(motion.X())+abs(motion.Y())+abs(motion.Z()))>HSettings::Calibrating::Gyro::threshold) {
            Serial.println("Recalibrating...");
            delay(1000);
            calibrate();
            return;
        }
        sums = sums + C3DPoint<double>(gyroData.X(), gyroData.Y(), gyroData.Z());
        delay(1);
    }
    sums = sums/HSettings::Calibrating::Gyro::precision;
    values.addFilter(values.X(), new Offset<float>(sums.X()));
    values.addFilter(values.Y(), new Offset<float>(sums.Y()));
    values.addFilter(values.Z(), new Offset<float>(sums.Z()));
    Serial.print("|");
}

String HGyro::toString() {
    return values.toString();
}
void HGyro::scanForDevices() {
    while(true){
        byte error, address;
        int nDevices;
        Serial.println("Scanning...");
        nDevices = 0;
        for(address = 1; address < 127; address++ ) {
            Wire.beginTransmission(address);
            error = Wire.endTransmission();
            if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address<16) {
                Serial.print("0");
            }
            Serial.println(address,HEX);
            nDevices++;
            }
            else if (error==4) {
            Serial.print("Unknow error at address 0x");
            if (address<16) {
                Serial.print("0");
            }
            Serial.println(address,HEX);
            }    
        }
        if (nDevices == 0) {
            Serial.println("No I2C devices found\n");
        }
        else {
            Serial.println("done\n");
        }
        delay(5000);
    }       
}

