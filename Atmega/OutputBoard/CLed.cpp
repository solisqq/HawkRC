#include "CLed.h"

CLed::CLed() {}
void CLed::init(uint8_t pinID, bool invertLogic=false){
    pin = pinID;
    invertedLogic = invertLogic;
    pinMode(pin, OUTPUT);
    turnOff();
}
void CLed::turnOn(){
    digitalWrite(pin, HIGH);
}
void CLed::turnOff() {
    digitalWrite(pin, LOW);
}

void CLed::pwm(uint8_t pwmValue) {
    analogWrite(pin, pwmValue);
}