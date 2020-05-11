#include <Arduino.h>
#include <HardwareSerial.h>
#include "Receiver/Receiver.h"
#include "Timer/Timer.h"

Receiver frskyD4R;
MSTimer mainTimer;

void setup(){
    Serial.begin(115200);
    frskyD4R.init(2, A1); 
    mainTimer.start(100);
}
void loop(){
    if(frskyD4R.isActive() && mainTimer.isTimeout()) {
        frskyD4R.sendData();
        Serial.write('\n');
    }

    frskyD4R.updateRSSI();
}