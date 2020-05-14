#include <Arduino.h>
#include <HardwareSerial.h>
#include "Receiver/Receiver.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"
#include "OutputBoard/OutputBoard.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/ErrorHandler.h"
#include "Display/Display.h"
#include "Display/Menu.h"

Receiver frskyD4R;
MSTimer mainTimer;
OutputBoard outputBoard;
Display display;
CMenu menu;

bool state = false;
void setup(){
    Serial.begin(115200);
    frskyD4R.init(3, A1); 
    mainTimer.start(100);
    display.init();
    outputBoard.init();
    menu.init(&display);
    errorHandler.addSource(&outputBoard);
    errorHandler.addSource(&display);
    menu.addMenuElement(&frskyD4R,true);
}
void loop(){
    //eventHandler.update();
    if(mainTimer.isTimeout()) {
        if(state) {
            //outputBoard.TurnOffLeds();
            state=true;
        } else {
            //outputBoard.TurnOnLeds();
            state=false;
        }
        if(frskyD4R.isActive()) {
            //frskyD4R.sendData();
            //Serial.write('\n');
            Serial.println(frskyD4R.toString());
        }
    }
    menu.updateButtons();
    frskyD4R.updateRSSI();
}