#include "system/HSystem.h"
#include "system/HProcess.h"
#include "system/HDebugger.h"
#include "components/HReceiver.h"
#include "components/HSteering.h"
#include "components/HGyro.h"
#include "components/HAccelerometer.h"
#include "components/HIMU.h"

HSystem hsystem;
HReceiver rx;
HSteering steering;
HGyro gyroscope;
HDebugger debugger;
HAccelerometer accelerometer;
HIMU imu;

void setup(){
    Serial.begin(250000);
    hsystem.addProcess(&rx, 50, "Receiver");
    hsystem.addProcess(&steering, 50, "Steering");
    hsystem.addProcess(&gyroscope, 2000, "Gyro");
    hsystem.addProcess(&accelerometer, 100, "Accelerometer");
    hsystem.addProcess(&debugger, 200, "Debugger");
    hsystem.addProcess(&imu, 1000, "Debugger");
    debugger.addPrintable(&imu);
    imu.debug(true);
    //debugger.addPrintable(&gyroscope);
    //gyroscope.debug(true);
}
void loop(){
    hsystem.operate();
}