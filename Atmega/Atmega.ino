#include <Arduino.h>
#include <HardwareSerial.h>
#include "Receiver/Receiver.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"
#include "OutputBoard/OutputBoard.h"
#include "OutputBoard/Battery.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/ErrorHandler.h"
#include "Display/Display.h"
#include "Display/Menu.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/Error.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"

Receiver frskyD4R;
MSTimer mainTimer;
OutputBoard outputBoard;
Display display;
CMenu menu;
Battery battery;
CError fcError(CError::ErrorType::Error, "FC", CError::ErrorLed::SoftwareLed);
CError imuError(CError::ErrorType::Error, "IMU", CError::ErrorLed::IMULed);


bool state = false;
bool FCConnection = true;
unsigned long long lastPacketTime = 0;

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
    menu.addMenuElement(&battery,true);
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
        List<int8_t> values;
        while(Serial.available()) {
            int8_t sign = static_cast<int8_t>(Serial.read());
            if(static_cast<char>(sign)==-126) {
                while(Serial.available()) {
                    delay(1);
                    sign = static_cast<int8_t>(Serial.read());
                    values.pushBack(sign);
                    if(static_cast<char>(sign)==-127) break;
                }
            }
        }
        /*for(int i=0; i<values.count(); i++) {
            Serial.print(String(values[i])+" ");
        }
        Serial.println(" ");
        Serial.println(values.count());*/

        if(values.count()==4 && values[3]==-127) {
            if(values[1]!=3) errorHandler.raise(imuError);
            else errorHandler.cancel(imuError);

            if(values[2]!=3) errorHandler.raise(fcError);
            else errorHandler.cancel(fcError);

            battery.setLevel(values[0]);

            if(FCConnection==false) {
                FCConnection=true;
                errorHandler.cancel(imuError);
                errorHandler.cancel(fcError);
            }
            lastPacketTime = millis();
        }
    } 
    if(FCConnection==true && lastPacketTime+2000<millis()) {
        FCConnection = false;
        errorHandler.raise(imuError);
        errorHandler.raise(fcError);
        battery.setLevel(-127);
    }
    
    menu.updateButtons();
    frskyD4R.updateRSSI();
}