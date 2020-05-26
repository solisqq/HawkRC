#include <Arduino.h>
#include <HardwareSerial.h>
#include "Receiver/Receiver.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"
#include "OutputBoard/OutputBoard.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/ErrorHandler.h"
#include "Display/Display.h"
#include "Display/Menu.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/Error.h"

Receiver frskyD4R;
MSTimer mainTimer;
OutputBoard outputBoard;
Display display;
CMenu menu;
CError fcError(CError::ErrorType::Error, "FC", CError::ErrorLed::SoftwareLed);
CError imuError(CError::ErrorType::Error, "IMU", CError::ErrorLed::IMULed);
CError batError(CError::ErrorType::Error, "BAT", CError::ErrorLed::BatteryLed);

bool state = false;
bool FCConnection = true;
unsigned int lastPacketTime = 0;

void setup(){
    Serial.begin(115200);
    frskyD4R.init(3, A1); 
    mainTimer.start(20);
    display.init();
    outputBoard.init();
    menu.init(&display);
    errorHandler.addSource(&outputBoard);
    errorHandler.addSource(&display);
    menu.addMenuElement(&frskyD4R,true);
    lastPacketTime = millis();
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
        frskyD4R.sendData();
        Serial.write(static_cast<char>(127));
    }
    if(Serial.available()) {
        if(FCConnection==false) {
            FCConnection=true;
            errorHandler.cancel(imuError);
            errorHandler.cancel(fcError);
            errorHandler.cancel(batError);
        }
        lastPacketTime = millis();
    } 
    if(FCConnection==true && lastPacketTime+2000<millis()) {
        FCConnection = false;
        errorHandler.raise(imuError);
        errorHandler.raise(fcError);
        errorHandler.raise(batError);
    }
    
    menu.updateButtons();
    frskyD4R.updateRSSI();
}