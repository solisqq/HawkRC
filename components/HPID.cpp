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

    Proportional = cerror * settings.pid.P;
    Integral = Integral + ((cerror*deltaTime)*settings.pid.I);
    Derivative = ((cerror-prevError)/deltaTime) * settings.pid.D;

    for(int i=0; i<3; i++) {
        
        if(Integral[i]>settings.pid.Limits.Y()) 
            Integral[i] = settings.pid.Limits.Y();
        else if(Integral[i]<-settings.pid.Limits.Y())
            Integral[i] = -settings.pid.Limits.Y();

        if(Proportional[i]>settings.pid.Limits.X()) 
            Proportional[i] = settings.pid.Limits.X();
        else if(Proportional[i]<-settings.pid.Limits.X())
            Proportional[i] = -settings.pid.Limits.X();

        if(Derivative[i]>settings.pid.Limits.Z()) 
            Derivative[i] = settings.pid.Limits.Z();
        else if(Derivative[i]<-settings.pid.Limits.Z())
            Derivative[i] = -settings.pid.Limits.Z();
    }

    values = C3DPoint<double>(
        Proportional.X()+Integral.X()+Derivative.X(),
        Proportional.Y()+Integral.Y()+Derivative.Y(),
        Proportional.Z()+Integral.Z()+Derivative.Z()
    );
    for(int i=0; i<3; i++) {
        if(values[i]>settings.pid.OverallLimits.get()) 
            values[i] = settings.pid.OverallLimits.get();
        else if(values[i]<-settings.pid.OverallLimits.get())
            values[i] = -settings.pid.OverallLimits.get();
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