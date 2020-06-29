#ifndef ARITHMETIC_PROG
#define ARITHMETIC_PROG
#include "List.h"

class ArithmeticProgression {
public:
template<class Type>
    static double calcAvg(List<Type> &list);
};

template<class Type>
double ArithmeticProgression::calcAvg(List<Type> &list) {
    double sum = 0;
    for(typename List<Type>::Node *it = list.top(); it!=nullptr; it=it->next) 
        sum += it->val; 
    
    sum /= list.count();
    return static_cast<double>(sum/list.count());
}

#endif