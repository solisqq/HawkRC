#ifndef HSETTINGS_INTERFACE
#define HSETTINGS_INTERFACE

#include <Arduino.h>

#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HProcess.h"

namespace CREATOR {

#define GET_VAR_NAME(Variable) (#Variable)
#define SET_VAR(var, value) var(#var,value,this)
#define SET_3DPOINT(var, value1, value2, value3) var(value1,value2,value3,false,#var,this)

#define INIT_CATEGORY(name) class name: public SETUP::HSettingsCategory{ private: using HSettingsCategory::childs; using HSettingsCategory::variables; using HSettingsCategory::getParent; using HSettingsCategory::getName; using HSettingsCategory::getPrefix; public:
#define BUILD_CATEGORY(name) name(SETUP::HSettingsCategory *parent): SETUP::HSettingsCategory(#name, parent),
#define ADD_SUBCATEGORY(className, instanceName) className instanceName;
#define INIT_SUBCATEGORY(instanceName) instanceName(this)
#define END_CATEGORY {}};

#define BUILD_MAIN_CATEGORY(name) name(): SETUP::HSettingsCategory("", nullptr),
#define INIT_MAIN_CATEGORY(name) class name: public HProcess, public SETUP::HSettingsCategory{ private: using HSettingsCategory::childs; using HSettingsCategory::variables; using HSettingsCategory::getParent; using HSettingsCategory::getName; using HSettingsCategory::getPrefix; public:
}

namespace UTILS {
List<String> split(const String &toSplit, char separator) {
    List<String> result;
    int lastOcc = 0;
    for(int i=0; i<toSplit.length(); i++) {
        if(separator==toSplit.charAt(i)) {
            result.pushBack(toSplit.substring(lastOcc,i));
            i++;
            lastOcc = i;
        }
    }
    result.pushBack(toSplit.substring(lastOcc,toSplit.length()));
    return result;
} 
}

namespace SETUP {

class BY_STRING_EDITABLE;
class HSettingsCategory {
    HSettingsCategory *parent;
    String name;
public:
    List<HSettingsCategory*> childs;
    List<BY_STRING_EDITABLE*> variables;
    HSettingsCategory(String name, HSettingsCategory* parentCategory);
    void append(BY_STRING_EDITABLE* variable);
    HSettingsCategory* getParent();
    String getName();
    String getPrefix();
};

class BY_STRING_EDITABLE: public AllowPrint {
    HSettingsCategory *parent=nullptr;
    String name="";
protected:
    BY_STRING_EDITABLE() {}
public:
    BY_STRING_EDITABLE(const String &name, HSettingsCategory *parent=nullptr):parent(parent),name(name) { if(parent!=nullptr) parent->append(this);}
    virtual void setByString(const String& valueInString){};
    String toString() override {return "";}
    String getName() {return name;}
};

HSettingsCategory::HSettingsCategory(String name, HSettingsCategory* parentCategory): name(name), parent(parentCategory) {if(parent!=nullptr) parent->childs.pushBack(this);}
void HSettingsCategory::append(BY_STRING_EDITABLE* variable) {variables.pushBack(variable);}
HSettingsCategory* HSettingsCategory::getParent(){return parent;}
String HSettingsCategory::getName(){return name;}
String HSettingsCategory::getPrefix() {
    HSettingsCategory* current = this;
    String result="";
    while(current!=nullptr) {
        result = current->getName()+"::"+result;
        current = current->getParent();
    }
    return result.substring(2,result.length());
}

class SDOUBLE: public BY_STRING_EDITABLE {
    double value=0;
public:
    SDOUBLE(String name, double val, HSettingsCategory* parent): BY_STRING_EDITABLE(name, parent), value(val){}
    void setByString(const String& valueInString) override {
        double result = valueInString.toDouble();
        if(result!=0) 
            value = result;
        else if(valueInString=="0") 
            value = result;
    }
    String toString() {return String(value);}
    double& get() {return value;}
};

class SFLOAT: public BY_STRING_EDITABLE {
    float value=0;
public:
    SFLOAT(String name, float val, HSettingsCategory* parent): BY_STRING_EDITABLE(name, parent), value(val){}
    void setByString(const String& valueInString) override {
        float result = valueInString.toFloat();
        if(result!=0) 
            value = result;
        else if(valueInString=="0") 
            value = result;
    }
    String toString() {return String(value);}
    float& get() {return value;}
};

class SINT: public BY_STRING_EDITABLE {
    int value=0;
public:
    SINT(String name, int val, HSettingsCategory* parent): BY_STRING_EDITABLE(name, parent), value(val){}
    void setByString(const String& valueInString) override {
        int result = valueInString.toInt();
        if(result!=0) 
            value = result;
        else if(valueInString=="0") 
            value = result;
    }
    String toString() {return String(value);}
    int& get() {return value;}
};

class SU8INT: public BY_STRING_EDITABLE {
    uint8_t value=0;
public:
    SU8INT(String name, uint8_t val, HSettingsCategory* parent): BY_STRING_EDITABLE(name, parent), value(val){}
    void setByString(const String& valueInString) override {
        uint8_t result = valueInString.toInt();
        if(result!=0) 
            value = result;
        else if(valueInString=="0") 
            value = result;
    }
    String toString() {return String(value);}
    uint8_t& get() {return value;}
};

class S8INT: public BY_STRING_EDITABLE {
    int8_t value=0;
public:
    S8INT(String name, int8_t val, HSettingsCategory* parent): BY_STRING_EDITABLE(name, parent), value(val){}
    void setByString(const String& valueInString) override {
        int8_t result = valueInString.toInt();
        if(result!=0) 
            value = result;
        else if(valueInString=="0") 
            value = result;
    }
    String toString() {return String(value);}
    int8_t& get() {return value;}
};
}

/*#define propDouble(x) static_cast<HTypedVariable<double>*>(x)->get()
#define prop

template<class Type>
class HVariable;


class HVariable {
    HSettingsCategory* parent;
    String name;
public:
    HVariable(){}
    HVariable(String name, HSettingsCategory* parent): name(name), parent(parent) {parent->append(this);}
};

template<class Type>
class HTypedVariable: public HVariable {
private:
    Type variable;
public:
    HTypedVariable(Type value, String name, HSettingsCategory* parent): variable(value), name(name), parent(parent) {parent->append(this);}
    Type& get(){return variable;}
    void set(Type value) {variable=value;}
};



HSettingsCategory::HSettingsCategory(String name, HSettingsCategory* parentCategory): name(name), parent(parentCategory) {}

String HSettingsCategory::getName() {
    return name;
}

void HSettingsCategory::append(HVariable *variable) {
    variables.pushBack(variable);
}
*/
#endif