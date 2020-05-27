#include "system/HSystem.h"
#include "system/HProcess.h"
#include "system/HDebugger.h"
#include "components/HReceiver.h"
#include "components/HSteering.h"
#include "components/HGyro.h"

HSystem hsystem;
HReceiver rx;
HSteering steering;
HGyro gyroscope;
HDebugger debugger;

void setup(){
    Serial.begin(250000);
    hsystem.addProcess(&rx, 50, "Receiver");
    hsystem.addProcess(&steering, 50, "Steering");
    hsystem.addProcess(&gyroscope, 2000, "Gyro");
    hsystem.addProcess(&debugger, 200, "Debugger");
    debugger.addPrintable(&gyroscope);
    gyroscope.debug(true);
}
void loop(){
    hsystem.operate();
}