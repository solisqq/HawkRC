#include "HReceiver.H"
HReceiver::HReceiver():rxSerial(1){}
void HReceiver::init() {
    rxSerial.begin(115200, SERIAL_8N1, HSettings::Pins::Receiver::RX, HSettings::Pins::Receiver::TX);//tu skończone
    rxSerial.println("FC ON");
}
void HReceiver::OnRXAxisRead(C4DPoint<float>& channels){    }
void HReceiver::OnRXSwitchesRead(C4DPoint<uint8_t>& channels) {}

void HReceiver::work() {
    List<int8_t> values;

    while(rxSerial.available()) {
        int8_t sign = static_cast<int8_t>(rxSerial.read());
        if(static_cast<char>(sign)=='\n') break;
        values.pushBack(sign);
    }
    if(values.count()<4) return;
    Signals::RXAxisReady.emit(C4DPoint<float>(
        static_cast<float>(values[0]),
        static_cast<float>(values[1]),
        static_cast<float>(values[2]),
        static_cast<float>(values[3])
        )
    );
    if(values.count()<8) return;
    Signals::RXSwitchesReady.emit(C4DPoint<uint8_t>(
        getSwitchStateByValue(values[4]),
        getSwitchStateByValue(values[5]),
        getSwitchStateByValue(values[6], true),
        getSwitchStateByValue(values[7], true)
        )
    );
}

uint8_t HReceiver::getSwitchStateByValue(int8_t val, bool threeStates) {
    if(val<=HSettings::RadioValues::LOW_STATE) return 0;
    if(threeStates && val<=HSettings::RadioValues::MID_HIGH_STATE && val>=HSettings::RadioValues::MID_LOW_STATE) return 1;
    if(val>=HSettings::RadioValues::HIGH_STATE)
        if(threeStates)
            return 2;

    return 1;
}
