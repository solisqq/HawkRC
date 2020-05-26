#include "system/HSystem.h"
#include "system/HProcess.h"
#include "components/HReceiver.h"
#include "components/HSteering.h"

HSystem hsystem;
HReceiver rx;
HSteering steering;

void setup(){
    Serial.begin(115200);
    hsystem.addProcess(&rx, 20, "Receiver");
    hsystem.addProcess(&steering, 20, "Steering");
}
void loop(){
    hsystem.operate();
}