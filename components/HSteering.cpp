#include "HSteering.h"
HSteering::HSteering(): HCStearingRead(), HCRXAxisRead() {}
void HSteering::init(){
    throttle.addFilter(new Mapper<float>(HSettings::RadioValues::MAX_VAL, HSettings::RadioValues::MIN_VAL, HSettings::EngineValues::START-50, HSettings::EngineValues::MAX-100));
    throttle.addFilter(new SimpleIR<float>(HSettings::Filtering::Receiver::axisSmoothing-0.1));

    yaw.addFilter(new DeadZoneFilter<float>(0, HSettings::RadioValues::DEAD_ZONE, -HSettings::RadioValues::DEAD_ZONE));
    yaw.addFilter(new SimpleIR<float>(HSettings::Filtering::Receiver::axisSmoothing-0.1));
    yaw.addFilter(new InfiniteAdd<float>(HSettings::Filtering::Receiver::yawMult));

    pitch.addFilter(new DeadZoneFilter<float>(0, HSettings::RadioValues::DEAD_ZONE, -HSettings::RadioValues::DEAD_ZONE));
    pitch.addFilter(new SimpleIR<float>(HSettings::Filtering::Receiver::axisSmoothing));
    pitch.addFilter(new Mapper<float>(HSettings::RadioValues::MAX_VAL, HSettings::RadioValues::MIN_VAL, -25, 25));

    roll.addFilter(new DeadZoneFilter<float>(0, HSettings::RadioValues::DEAD_ZONE, -HSettings::RadioValues::DEAD_ZONE));
    roll.addFilter(new SimpleIR<float>(HSettings::Filtering::Receiver::axisSmoothing));
    roll.addFilter(new Mapper<float>(HSettings::RadioValues::MAX_VAL, HSettings::RadioValues::MIN_VAL, -25, 25));
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
