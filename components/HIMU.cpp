#include "HIMU.h"

HIMU::HIMU():values(true){}

void HIMU::init(){
    /*Wire.begin();
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
    calibrate();*/
    //values.addFilters(new ButterworthLP<float>(2000,40));
    values.setAll(-9999);
    state = 1;
}
void HIMU::work(){
    if(values.X()==-9999 && values.Y()==-9999 && values.Z()==-9999) return;
    state = 3;
    Signals::IMUReady.emit(values);
}

void HIMU::OnGyroRead(C3DPoint<float> gyroData) {
    if(prevTime==0) {
        prevTime = micros();
        return;
    }
    double deltaTime = (micros()-prevTime)/1000000.0;
    if(values.X()==-9999 && values.Y()==-9999 && values.Z()==-9999) return;
    values.X() = values.X()+(gyroData.X()*deltaTime);
    values.Y() = values.Y()+(gyroData.Y()*deltaTime);
    values.Z() = values.Z()+(gyroData.Z()*deltaTime);
    prevTime = micros();
}

void HIMU::OnAccRead(C3DPoint<float> accData) {
    if(values.X()==-9999 && values.Y()==-9999 && values.Z()==-9999) {
        values.X() = accData.X();
        values.Y() = accData.Y();
        values.Z() = accData.Z();
        return;
    }
    values.X() = values.X()*(1.0-settings.filtering.imu.accStrength.get()) + (accData.X()*settings.filtering.imu.accStrength.get());
    values.Y() = values.Y()*(1.0-settings.filtering.imu.accStrength.get()) + (accData.Y()*settings.filtering.imu.accStrength.get());
}
String HIMU::toString() {
    return values.toString();
}

