#ifndef C3DPOINT_H
#define C3DPOINT_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Filter/FilterableType.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"

template<class Type>
class C3DPoint: public AllowPrint, public FilterableType<Type> {
    Type x;
    Type y;
    Type z;
public:
    C3DPoint(bool filterable=false):x(0),y(0),z(0){
        if(!filterable) return;
        FilterableType<Type>::addValueReference(x);
        FilterableType<Type>::addValueReference(y);
        FilterableType<Type>::addValueReference(z);
    }
    C3DPoint(Type x, Type y, Type z, bool filterable=false): x(x), y(y), z(z){
        if(!filterable) return;
        FilterableType<Type>::addValueReference(x);
        FilterableType<Type>::addValueReference(y);
        FilterableType<Type>::addValueReference(z);
    }
    void setAll(Type val) {
        x = y = z = val;
    }
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
    void updateFilters(C3DPoint<Type> updateVal) {
        FilterableType<Type>::_updateFilters(updateVal.toList());
    }
    void addFilter(Type& valToAdd, Filter<Type> *newFilter) {
        FilterableType<Type>::_addFilter(&valToAdd, newFilter);
    }
    void addFilters(Filter<Type> *newFilter) {
        FilterableType<Type>::_addFilters(newFilter);
    }
    List<Type> toList() {
        List<Type> toRet;
        toRet.pushBack(x);
        toRet.pushBack(y);
        toRet.pushBack(z);
        return toRet;
    }
    C3DPoint<Type> operator/(Type divider) {
        return C3DPoint<Type>(x/divider,y/divider,z/divider);
    } 
    C3DPoint<Type> operator+(const C3DPoint<Type>& other) {
        return C3DPoint<Type>(x+other.x,y+other.y,z+other.z);
    }
    C3DPoint<Type> operator-(const C3DPoint<Type>& other) {
        return C3DPoint<Type>(x-other.x,y-other.y,z-other.z);
    }
    C3DPoint<Type> operator*(Type divider) {
        return C3DPoint<Type>(x*divider,y*divider,z*divider);
    } 
    C3DPoint<Type> operator+(Type toAdd) {
        return C3DPoint<Type>(x+toAdd,y+toAdd,z+toAdd);
    }
    C3DPoint<Type> operator-(Type toSub) {
        return C3DPoint<Type>(x-toSub,y-toSub,z-toSub);
    }
    C3DPoint<Type> operator/(const C3DPoint<Type> &divider) {
        return C3DPoint<Type>(x/divider.x,y/divider.y,z/divider.z);
    }
    C3DPoint<Type> operator*(const C3DPoint<Type> &mult) {
        return C3DPoint<Type>(x*mult.x,y*mult.y,z*mult.z);
    }
    Type sumUp() {return x+y+z;}
    C3DPoint<int> toInt() {
        return C3DPoint<int>(
            static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(z)
        );
    }
    C3DPoint<float> toFloat() {
        return C3DPoint<float>(
            static_cast<float>(x),
            static_cast<float>(y),
            static_cast<float>(z)
        );
    }
    C3DPoint<double> toDouble() {
        return C3DPoint<double>(
            static_cast<double>(x),
            static_cast<double>(y),
            static_cast<double>(z)
        );
    }
};

#endif