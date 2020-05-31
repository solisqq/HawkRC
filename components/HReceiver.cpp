#include "HReceiver.H"
HReceiver::HReceiver():rxSerial(1){}
void HReceiver::init() {
    rxSerial.begin(115200, SERIAL_8N1, HSettings::Pins::Receiver::RX, HSettings::Pins::Receiver::TX);//tu skończone
    rxSerial.println("FC ON");
    Signals::RXConnectionSwitchState.emit(false);
}

void HReceiver::work() {
    List<int8_t> values;
    while(rxSerial.available()) {
        int8_t sign = static_cast<int8_t>(rxSerial.read());
        if(static_cast<char>(sign)==127) break;
        values.pushBack(sign);
    }
    if(values.count()<9) return;
    if(values[8]<HSettings::RadioValues::LOW_RSI_SIGNAL && Signals::RXConnectionSwitchState.getValue()==true) {
        Signals::RXConnectionSwitchState.emit(false);
        return;
    }
    if(Signals::RXConnectionSwitchState.getValue()==false) {
        if(static_cast<uint8_t>(values[8])>HSettings::RadioValues::LOW_RSI_SIGNAL) 
            Signals::RXConnectionSwitchState.emit(true);
        else 
            return;
    }
    Signals::RXSwitchesReady.emit(C4DPoint<uint8_t>(
        getSwitchStateByValue(values[4]),
        getSwitchStateByValue(values[5]),
        getSwitchStateByValue(values[6], true),
        getSwitchStateByValue(values[7], true)
        )
    );
    Signals::RXAxisReady.emit(C4DPoint<int8_t>(values[0],values[1],values[2],values[3]));
    rxSerial.println("FC ON");
}

uint8_t HReceiver::getSwitchStateByValue(int8_t val, bool threeStates) {
    if(val<=HSettings::RadioValues::LOW_STATE) return 0;
    if(threeStates && val<=HSettings::RadioValues::MID_HIGH_STATE && val>=HSettings::RadioValues::MID_LOW_STATE) return 1;
    if(val>=HSettings::RadioValues::HIGH_STATE)
        if(threeStates)
            return 2;

    return 1;
}
