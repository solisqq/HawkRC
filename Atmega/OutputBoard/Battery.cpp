#include "Arduino.h"
#include "Battery.h"

Battery::Battery(){}

void Battery::init() {
    delay(20);
}

String Battery::toString() {
    return String(batLevel);
}

void Battery::setLevel(int8_t val) {
    batLevel = val;
    if(batLevel<-60) 
        errorHandler.raise(batError);
     else
        errorHandler.cancel(batError);
    paint();
}

void Battery::paint() {
    if(!isMenuElementActive()) return;
    for (int i=0; i<8; i++) {
        for(int j=0; j<12; j++) {
            //display->getPrimitive().drawLine(0, 11+j, 128, 12+j, SSD1306_BLACK);
            display->getPrimitive().drawLine(0, 10+j, (127+batLevel)/2, 10+j, SSD1306_WHITE);
        }
    }
    display->updateErrorsSection(); 
    display->getPrimitive().display();
    display->writeLine(1,CPoint<uint8_t>(0,0), "Battery level");
}
void Battery::buttonPushed(Pinout::Buttons buttonID) {}

