#include "HReceiver.H"
HReceiver::HReceiver():rxSerial(1){}
void HReceiver::init() {
    rxSerial.begin(115200, SERIAL_8N1, settings.pins.receiver.RX.get(), settings.pins.receiver.TX.get());//tu skończone
    rxSerial.println("FC ON");
    Signals::RXConnectionSwitchState.emit(false);
}

HardwareSerial& HReceiver::getSerial() {
    return rxSerial;
}

void HReceiver::work() {
    List<int8_t> values;
    if(rxSerial.available()) {
        while(rxSerial.available()) {
            int8_t sign = static_cast<int8_t>(rxSerial.read());
            if(static_cast<char>(sign)==127) break;
            values.pushBack(sign);
        }
    } else return;
    
    if(values.count()<9) {
        return;
    }
    if(values[8]<settings.radioValues.lowRSI.get() && Signals::RXConnectionSwitchState.getValue()==true) {
        Signals::RXConnectionSwitchState.emit(false);
        return;
    }
    if(Signals::RXConnectionSwitchState.getValue()==false) {
        if(static_cast<uint8_t>(values[8])>settings.radioValues.lowRSI.get() && static_cast<uint8_t>(values[8])<245) 
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
}

uint8_t HReceiver::getSwitchStateByValue(int8_t val, bool threeStates) {
    if(val<=settings.radioValues.lowState.get()) return 0;
    if(threeStates && val<=settings.radioValues.midHighState.get() && val>=settings.radioValues.midLowState.get()) return 1;
    if(val>=settings.radioValues.highState.get())
        if(threeStates)
            return 2;

    return 1;
}
