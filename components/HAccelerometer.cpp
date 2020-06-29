#include "HAccelerometer.h"

HAccelerometer::HAccelerometer(){}
void HAccelerometer::init(){
}
void HAccelerometer::work(){
    C3DPoint<float> rawAcc = bmi088.getAcceleration();
    values.X() = (atan2(rawAcc.Y(), rawAcc.Z())*180)/MATH_PI;
    values.Y() = (atan2(rawAcc.X(), sqrt(rawAcc.Y() * rawAcc.Y() + rawAcc.Z() * rawAcc.Z())) * 180.0) / MATH_PI;
    //values.Z() = rawAcc.Z();
    values.Z() = 0;
    Signals::AccReady.emit(values);
}
void HAccelerometer::OnAccRead(C3DPoint<float> data){
    //Serial.println(data.toString());
}
String HAccelerometer::toString(){ return "";}
void HAccelerometer::calibrate(){}