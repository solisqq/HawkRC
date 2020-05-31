#pragma once
#ifndef OFFSET_H
#define OFFSET_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/Filter.h"

template<class Type>
class Offset : public Filter<Type>
{
private:
    Type offset=0;
public:
    Offset(Type _offset): offset(_offset) {}
    void set(Type val) {offset = val;}
    virtual void update(Type newVal) {Filter<Type>::filtered = newVal-offset;}
    virtual Filter<Type>* clone() const {
        return new Offset<Type>(offset);
    }
};


#endif