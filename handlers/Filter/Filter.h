#pragma once
#ifndef FILTER_H
#define FILTER_H
#define ABSOLUTE_DIFFERENCE(A,B) ((A-B)<0 ? (-(A-B)): (A-B))
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"


template <class Type>
class Filter {
protected:
	
public:
	Type filtered;
	void setVal(Type *_val) {filtered = _val;}
	Type getVal() {return filtered;}
	virtual void update(Type newVal) = 0;
	void reset() {filtered=0.0;}
	List<Filter<Type>*> operator+(const Filter<Type> &b) {
		List<Filter<Type>*> list;
		list.pushBack(this);
		list.pushBack(b);
		return list;
	}
	virtual Filter* clone() const = 0;
};




#endif