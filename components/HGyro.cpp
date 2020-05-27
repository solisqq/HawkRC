#include "HGyro.h"

HGyro::HGyro(){}

void HGyro::init(){
    Wire.begin();
    Wire.setClock(400000);
    while(1)
    {
        if(bmi088.isConnection())
        {
            bmi088.initialize();
            Serial.println("BMI088 is connected");
            break;
        }
        delay(2000);
    }
    X.addFilter(new ButterworthLP<float>(2000, 40));
    Y.addFilter(new ButterworthLP<float>(2000, 40));
    Z.addFilter(new ButterworthLP<float>(2000, 40));
}
void HGyro::work(){
    C3DPoint<float> point3D = bmi088.getGyroscope();
    X.update(point3D.X());
    Y.update(point3D.Y());
    Z.update(point3D.Z());
    Signals::GyroReady.emit(C3DPoint<float>(X.value,Y.value,Z.value));
}

void HGyro::OnGyroRead(C3DPoint<float> gyroData) {
    //Serial.println(gyroData.toString());
}

String HGyro::toString() {
    return String(X.value)+" "+String(Y.value)+" "+String(Z.value);
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

