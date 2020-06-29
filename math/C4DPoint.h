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
    C4DPoint(Type valForAll): x(valForAll), y(valForAll), z(valForAll), a(valForAll){}
    Type& X(){return x;}
    Type& Y(){return y;}
    Type& Z(){return z;}
    Type& A(){return a;}
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
    C4DPoint<int> toInt() {
        return C4DPoint<int>(static_cast<int>(x),static_cast<int>(y),static_cast<int>(z),static_cast<int>(a));
    }
    C4DPoint<float> toFloat() {
        return C4DPoint<float>(
            static_cast<float>(x),
            static_cast<float>(y),
            static_cast<float>(z),
            static_cast<float>(a)
        );
    }
    C4DPoint<double> toDouble() {
        return C4DPoint<double>(
            static_cast<double>(x),
            static_cast<double>(y),
            static_cast<double>(z),
            static_cast<double>(a)
        );
    }
};

#endif