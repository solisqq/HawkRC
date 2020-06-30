#ifndef HSETTINGS_INTERFACE
#define HSETTINGS_INTERFACE

#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"

class HVariable;
class HSettingsCategory {
    HSettingsCategory *parent;
    String name;
    List<HVariable*> variables;
public:
    HSettingsCategory(HString name, HSettingsCategory* parentCategory);
    void append(HVariable *variable);
};

template<class Type>
class HVariable {
    Type variable;
    String name;
    HSettingsCategory* parent;
public:
    HVariable(){}
    HVariable(Type value, String name, HSettingsCategory* parent): variable(value), name(name), parent(parent) {parent->append(this);}
    Type& get(){return variable;}
    void set(Type value) {variable=value;}
};

HSettingsCategory::HSettingsCategory(HString name, HSettingsCategory* parentCategory): name(name), parent(parentCategory) {}

String HSettingsCategory::getName() {
    return name;
}

void HSettingsCategory::append(HVariable *variable) {
    variables.pushBack(variable);
}

#endif