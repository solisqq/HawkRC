#include "system/HSystem.h"
#include "system/HProcess.h"
#include "components/HReceiver.h"
#include "components/HSteering.h"

HSystem hsystem;
HReceiver rx;
HSteering steering;

void setup(){
    Serial.begin(115200);
    hsystem.addProcess(&rx, 50, "Receiver");
    hsystem.addProcess(&steering, 50, "Steering");
}
void loop(){
    hsystem.operate();
}