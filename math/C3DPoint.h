#ifndef C3DPOINT_H
#define C3DPOINT_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"

template<class Type>
class C3DPoint: public AllowPrint {
    Type x;
    Type y;
    Type z;
public:
    C3DPoint():x(0),y(0),z(0){}
    C3DPoint(Type x, Type y, Type z): x(x), y(y), z(z){}
    Type& X(){return x;}
    Type& Y(){return y;}
    Type& Z(){return z;}
    Type& operator[](int index) {
        if(index<0) return x;
        if(index>2) return z;
        switch(index) {
            case 0: return x;
            break;
            case 1: return y;
            break;
            case 2: return z;
        }
    }
    virtual String toString() {
        return String(x)+" "+String(y)+" "+String(z);
    }
};

#endif