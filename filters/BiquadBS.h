#pragma once
#ifndef BIQUAD_C_H
#define BIQUAD_C_H

#include "stock/BiquadCustom.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"

template<class Type>
class BiquadBS : public Filter<Type> {
    BiquadCustom* biquad = nullptr;
    float centerFreq = 0, widthFreq = 0, rippleDb = 0, freq = 0;
public:
    BiquadBS(float _freq, float _centerFreq, float _widthFreq, float _rippleDb) :
        freq(_freq),
        centerFreq(_centerFreq),
        widthFreq(_widthFreq),
        rippleDb(_rippleDb)
    {
        biquad = new BiquadCustom(bq_type_notch, centerFreq / freq, _widthFreq/centerFreq, _rippleDb);
    }

    virtual void update(Type newVal) {
        Filter<Type>::filtered = biquad->process(static_cast<double>(newVal));
    }
    Filter<Type>* clone() override {
        return new BiquadBS<Type>(freq, centerFreq, widthFreq, rippleDb);
    }
};

#endif