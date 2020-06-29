#include "HBattery.h"

HBattery::HBattery(){
}
void HBattery::init(){
    pinMode(HSettings::Pins::Battery, INPUT_PULLDOWN);
    batteryLevel.addFilter(new SimpleIR<float>(0.99));
}
void HBattery::work(){
    int8_t val = analogRead(HSettings::Pins::Battery);
    //val = val*1.3;
    if(val<-126) val = -126;
    else if(val>126) val = 126;
    batteryLevel.update(val);
}
int8_t HBattery::getLevel() {
    int toPass = ((batteryLevel.value*4));
    if(toPass>120) toPass = 120;
    if(toPass<-120) toPass = -120;
    return static_cast<int8_t>(toPass);
}
String HBattery::toString(){
    return String(static_cast<int8_t>(getLevel()));
}