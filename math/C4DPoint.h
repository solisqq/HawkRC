#ifndef C4DPOINT_H
#define C4DPOINT_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"

template<class Type>
class C4DPoint: public AllowPrint {
    Type x;
    Type y;
    Type z;
    Type a;
public:
    C4DPoint():x(0),y(0),z(0),a(0){}
    C4DPoint(Type x, Type y, Type z, Type a): x(x), y(y), z(z), a(a){}
    Type X(){return x;}
    Type Y(){return y;}
    Type& operator[](int index) {
        if(index<0) return x;
        if(index>3) return a;
        switch(index) {
            case 0: return x;
            break;
            case 1: return y;
            break;
            case 2: return z;
            break;
            case 3: return a;
        }
    }
    virtual String toString() {
        return String(x)+", "+String(y)+", "+String(z)+", "+String(a);
    }
};

#endif