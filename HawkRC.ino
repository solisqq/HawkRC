#include "system/HSystem.h"
#include "system/HProcess.h"
#include "components/HReceiver.h"

HSystem hsystem;
HReceiver rx;
void setup(){
    Serial.begin(115200);
    hsystem.addProcess(&rx, 50, "Receiver");
}
void loop(){
    hsystem.operate();
}