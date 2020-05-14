#include "Receiver.h"

Receiver::Receiver(){}

void Receiver::init(uint8_t interruptPin, uint8_t RSSIPin) {
    this->RSSI_PIN = RSSIPin;
    pinMode(interruptPin, INPUT_PULLUP);
    pinMode(RSSI_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), CPPM_ISR, RISING);
    delay(20);
}

bool Receiver::isActive()
{
    if (getRSSI()>160)
        return true;
        
    return false;
}

void Receiver::sendData() {
    String toRet = "";
    for(int i=0; i<8; i++)
        Serial.write((char)((channel_length[i]-1500)/5));
    Serial.write((char)getRSSI());
}

uint8_t Receiver::getRSSI() {
    return RSSI_VAL;
}

String Receiver::toString() {
    String toRet = "";
    for (int i=0; i<8; i++) 
        toRet += String(channel_length[i])+", ";
    toRet += String(getRSSI());
    return toRet;
}

void Receiver::updateRSSI() {
    if(RSSI_TIME !=0 ) {
        RSSI_AVG += analogRead(this->RSSI_PIN);
        RSSI_COUNTER++;
        if(RSSI_COUNTER>100) {
            RSSI_VAL = (RSSI_VAL*0.95) + (RSSI_AVG / 350)*0.05;
            if(RSSI_VAL>255) RSSI_VAL = 255;
            RSSI_AVG = 0;
            RSSI_COUNTER = 0;
        }
    }
    RSSI_TIME = micros();
    if(isActive()) {
        if(errorHandler.cancel(noRX_Error)) 
            paint();
    }
    else {
        if(errorHandler.raise(noRX_Error)) 
            paint();
    }
}

void Receiver::paint() {
    if(!isMenuElementActive()) return;
    List<String> strings = List<String>();
    
    if(isActive()) {
        //display->getPrimitive().clearDisplay();
        for (int i=0; i<8; i++) {
            int val = channel_length[i]-1000;
            val /= 41;
            if(val<=0) val = 1;
            display->getPrimitive().drawLine(4+(i*14), 24, 4+(i*14), 24, SSD1306_BLACK);
            display->getPrimitive().drawLine(4+(i*14), 24, 4+(i*14), 24-val, SSD1306_WHITE);
            // 
        }
        display->updateErrorsSection(); 
        display->getPrimitive().display();
    } else {
        strings.pushBack("Problem with receiver");
        strings.pushBack(" Check RX connection");
        strings.pushBack("Down btn to navigate");
    }
    
    display->writeLines(1, CPoint<uint8_t>(0,0), strings);
}
void Receiver::buttonPushed(Pinout::Buttons buttonID) {

}