#ifndef CPOINT_H
#define CPOINT_H

template<class Type>
class CPoint {
    Type x;
    Type y;
public:
    CPoint():x(0),y(0){}
    CPoint(Type x, Type y): x(x), y(y){}
    Type X(){return x;}
    Type Y(){return y;}
};

#endif