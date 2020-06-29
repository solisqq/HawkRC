#include "HPID.h"

HPID::HPID(){}
void HPID::init(){
    values.setAll(0);
    //Proportional.addFilters(new LimitsFilter<double>(-300,300));
    //Integral.addFilters(new LimitsFilter<double>(-150,150));
    //Derivative.addFilters(new LimitsFilter<double>(-400,400));
    //values.addFilters(new LimitsFilter<double>(-700,700));
}

void HPID::work() {

}

void HPID::OnIMURead(C3DPoint<double> currentAngles){
    if(prevTime==0) {
        prevTime = micros();
        return;
    }
    C3DPoint<double> prevError = cerror;
    cerror = desiredAngles-currentAngles;
    double deltaTime = (micros()-prevTime)/1000000.0;
    prevTime = micros();

    /*Proportional.updateFilters(cerror * HSettings::PID::P);
    Integral.updateFilters(Integral + ((cerror*deltaTime)*HSettings::PID::I));
    Derivative.updateFilters(((cerror-prevError)/deltaTime) * HSettings::PID::D);
    
    values.updateFilters(C3DPoint<double>(
        Proportional.X()+Integral.X()+Derivative.X(),
        Proportional.Y()+Integral.Y()+Derivative.Y(),
        Proportional.Z()+Integral.Z()+Derivative.Z()
        )
    );*/

    Proportional = cerror * HSettings::PID::P;
    Integral = Integral + ((cerror*deltaTime)*HSettings::PID::I);
    Derivative = ((cerror-prevError)/deltaTime) * HSettings::PID::D;

    for(int i=0; i<3; i++) {
        if(Integral[i]>HSettings::PID::PID_LIMITS.Y()) 
            Integral[i] = HSettings::PID::PID_LIMITS.Y();
        else if(Integral[i]<-HSettings::PID::PID_LIMITS.Y())
            Integral[i] = -HSettings::PID::PID_LIMITS.Y();

        if(Proportional[i]>HSettings::PID::PID_LIMITS.X()) 
            Proportional[i] = HSettings::PID::PID_LIMITS.X();
        else if(Proportional[i]<-HSettings::PID::PID_LIMITS.X())
            Proportional[i] = -HSettings::PID::PID_LIMITS.X();

        if(Derivative[i]>HSettings::PID::PID_LIMITS.Z()) 
            Derivative[i] = HSettings::PID::PID_LIMITS.Z();
        else if(Derivative[i]<-HSettings::PID::PID_LIMITS.Z())
            Derivative[i] = -HSettings::PID::PID_LIMITS.Z();
    }

    values = C3DPoint<double>(
        Proportional.X()+Integral.X()+Derivative.X(),
        Proportional.Y()+Integral.Y()+Derivative.Y(),
        Proportional.Z()+Integral.Z()+Derivative.Z()
    );

    for(int i=0; i<3; i++) {
        if(values[i]>HSettings::PID::OVERALL_LIMIT) 
            values[i] = HSettings::PID::OVERALL_LIMIT;
        else if(values[i]<-HSettings::PID::OVERALL_LIMIT)
            values[i] = -HSettings::PID::OVERALL_LIMIT;
    }

    Signals::PIDReady.emit(values);
}

void HPID::OnStearingRead(C4DPoint<float> stearing) {
    desiredAngles.X() = stearing.A();
    desiredAngles.Y() = stearing.Z();
    desiredAngles.Z() = stearing.Y();
}

String HPID::toString(){
    return Proportional.toString()+" "+Integral.toString()+" "+Derivative.toString();
}
void HPID::OnRXSwitchesRead(C4DPoint<uint8_t> switches)  {
    if(switches[0]==0) {
        Integral = C3DPoint<double>(0);
    }
}