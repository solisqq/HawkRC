#pragma once
#ifndef HPAIR_H
#define HPAIR_H

template <class Type1, class Type2>
class HPair {
public:
    Type1 first;
    Type2 second;
    HPair(Type1 firstElement, Type2 secondElement): first(firstElement), second(secondElement){}
};
#endif