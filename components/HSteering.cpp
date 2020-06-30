#include "HSteering.h"
HSteering::HSteering(): HCStearingRead(), HCRXAxisRead() {}
void HSteering::init(){
    throttle.addFilter(new Mapper<float>(settings.radioValues.maxVal.get(), settings.radioValues.minVal.get(), settings.engineValues.STARTV.get()-50, settings.engineValues.MAXV.get()-100));
    throttle.addFilter(new SimpleIR<float>(settings.filtering.receiver.axisSmoothing.get()-0.1));

    yaw.addFilter(new DeadZoneFilter<float>(0, settings.radioValues.deadZone.get(), -settings.radioValues.deadZone.get()));
    yaw.addFilter(new SimpleIR<float>(settings.filtering.receiver.axisSmoothing.get()-0.1));
    yaw.addFilter(new InfiniteAdd<float>(settings.filtering.receiver.yawMult.get()));

    pitch.addFilter(new DeadZoneFilter<float>(0, settings.radioValues.deadZone.get(), -settings.radioValues.deadZone.get()));
    pitch.addFilter(new SimpleIR<float>(settings.filtering.receiver.axisSmoothing.get()));
    pitch.addFilter(new Mapper<float>(settings.radioValues.maxVal.get(), settings.radioValues.minVal.get(), -25, 25));

    roll.addFilter(new DeadZoneFilter<float>(0, settings.radioValues.deadZone.get(), -settings.radioValues.deadZone.get()));
    roll.addFilter(new SimpleIR<float>(settings.filtering.receiver.axisSmoothing.get()));
    roll.addFilter(new Mapper<float>(settings.radioValues.maxVal.get(), settings.radioValues.minVal.get(), -25, 25));
}
void HSteering::OnRXAxisRead(C4DPoint<int8_t> channels){
    throttle.update(static_cast<float>(channels[0]));
    yaw.update(static_cast<float>(channels[1]));
    pitch.update(static_cast<float>(channels[2]));
    roll.update(static_cast<float>(channels[3]));
    Signals::StearingReady.emit(C4DPoint<float>(throttle.value, yaw.value, pitch.value, roll.value));
}
void HSteering::OnStearingRead(C4DPoint<float> channels) {
    //Serial.println(channels.toString());
}

String HSteering::toString() {
    return throttle.toString()+" "+yaw.toString()+" "+pitch.toString()+" "+roll.toString();
}
