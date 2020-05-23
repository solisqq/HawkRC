#ifndef C4DPOINT_H
#define C4DPOINT_H

template<class Type>
class C4DPoint {
    Type x;
    Type y;
    Type z;
    Type a;
public:
    CPoint():x(0),y(0),z(0),a(0){}
    CPoint(Type x, Type y, Type z, Type a): x(x), y(y), z(z), a(a){}
    Type X(){return x;}
    Type Y(){return y;}
    Type operator[](int index) {
        if(index>3 || index<0) return 0;
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
};

#endif