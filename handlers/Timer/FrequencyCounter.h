#ifndef FREQUENCY_COUNTER_H
#define FREQUENCY_COUNTER_H

#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"

class FrequencyCounter: public AllowPrint {
protected:
    unsigned long int prevTime = 0;
    int counter = 0;
    int value = 0;
    bool printing = false;
    String adnotation="";
public:
    FrequencyCounter() {}
    void calc(){
        if(prevTime+1000<millis()) {
            prevTime = millis();
            value = counter;
            counter = 0;
            if(printing) Serial.println(adnotation+toString());
        }
        counter++;
    }
    int get() {
        return value;
    }
    void enablePrinting(bool print=true, const String& adnotate="") {
        printing = print;
        adnotation = adnotate;
    }
    String toString() {
        return String(get());
    }
};

#endif