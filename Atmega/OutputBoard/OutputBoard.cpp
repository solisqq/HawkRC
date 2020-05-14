#include "OutputBoard.h"

OutputBoard::OutputBoard() {}
void OutputBoard::init(){
    BatteryLed.init(Pinout::Leds::BatteryError);
    RxLed.init(Pinout::Leds::RCError);
    IMULed.init(Pinout::Leds::IMUError);
    SOFTLed.init(Pinout::Leds::SOFTError);

    Leds[0] = &BatteryLed;
    Leds[1] = &RxLed;
    Leds[2] = &IMULed;
    Leds[3] = &SOFTLed;

    Buzzer.init(Pinout::Misc::Buzzer);
    TestLeds();
}

void OutputBoard::TurnOffLeds() {
    for(uint8_t i=0; i<4; i++) 
        Leds[i]->turnOff();
}
void OutputBoard::TurnOnLeds(){
    for(uint8_t i=0; i<4; i++) 
        Leds[i]->turnOn();
}
void OutputBoard::TestLeds() {
    TurnOnLeds();
    Buzzer.pwm(100);
    delay(100);
    Buzzer.pwm(180);
    delay(100);
    Buzzer.pwm(100);
    delay(100);
    Buzzer.pwm(140);
    delay(100);
    Buzzer.pwm(200);
    delay(100);
    Buzzer.pwm(220);
    TurnOffLeds();
    delay(100);
    Buzzer.pwm(140);
    delay(100);
    Buzzer.pwm(90);
    delay(100);
    Buzzer.pwm(220);
    delay(100);
    Buzzer.pwm(130);
    delay(100);
    Buzzer.pwm(100);
    delay(100);
    Buzzer.pwm(150);
    TurnOnLeds();
    Buzzer.pwm(170);
    TurnOffLeds();
    Buzzer.pwm(0);
}

void OutputBoard::showErrors(List<CError*>& errors) {
    TurnOffLeds();
    for(List<CError*>::Node* it=errors.top(); it!=nullptr; it=it->next) {
        if(it->val->eled==CError::ErrorLed::BatteryLed) BatteryLed.turnOn();
        else if(it->val->eled==CError::ErrorLed::RXLed) RxLed.turnOn();
        else if(it->val->eled==CError::ErrorLed::IMULed) IMULed.turnOn();
        else if(it->val->eled==CError::ErrorLed::SoftwareLed) SOFTLed.turnOn();
    }
}