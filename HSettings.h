#ifndef HSETTINGS_H
#define HSETTINGS_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "HSettingsInterface.h"
/*
Engines:
12,14,23,19
Bat:
D4
*/

INIT_MAIN_CATEGORY(HSettings)
    INIT_CATEGORY(Pins)
        SETUP::SU8INT battery;
        INIT_CATEGORY(Receiver)
            SETUP::SU8INT RX;SETUP::SU8INT TX;
            BUILD_CATEGORY(Receiver)
                SET_VAR(RX,16),
                SET_VAR(TX,17)
        END_CATEGORY

        INIT_CATEGORY(Engines)
            SETUP::SU8INT frontLeft;SETUP::SU8INT frontRight;SETUP::SU8INT backLeft;SETUP::SU8INT backRight;
            BUILD_CATEGORY(Engines)
                SET_VAR(frontLeft,12),
                SET_VAR(frontRight,14),
                SET_VAR(backLeft,23),
                SET_VAR(backRight,19)
        END_CATEGORY

        ADD_SUBCATEGORY(Receiver, receiver)
        ADD_SUBCATEGORY(Engines, engines)
        BUILD_CATEGORY(Pins)
            INIT_SUBCATEGORY(receiver),
            INIT_SUBCATEGORY(engines),
            SET_VAR(battery, 4)
    END_CATEGORY


    INIT_CATEGORY(RadioValues)
        SETUP::S8INT lowState; SETUP::S8INT midState; SETUP::S8INT midHighState; SETUP::S8INT midLowState; SETUP::S8INT highState;SETUP::S8INT deadZone;SETUP::S8INT maxVal;SETUP::S8INT minVal;SETUP::SU8INT lowRSI;
        BUILD_CATEGORY(RadioValues)
            SET_VAR(lowState, -90),
            SET_VAR(midState, 0),
            SET_VAR(midHighState, 5),
            SET_VAR(midLowState, -5),
            SET_VAR(highState, 90),
            SET_VAR(deadZone, 2),
            SET_VAR(lowRSI, 0),
            SET_VAR(maxVal, 105),
            SET_VAR(minVal, -105)
    END_CATEGORY


    INIT_CATEGORY(Filtering)
        INIT_CATEGORY(Receiver)
            SETUP::SFLOAT axisSmoothing;SETUP::SFLOAT yawMult;
            BUILD_CATEGORY(Receiver)
                SET_VAR(axisSmoothing,0.87),
                SET_VAR(yawMult,0.15)
        END_CATEGORY

        INIT_CATEGORY(IMU)
            SETUP::SDOUBLE accStrength;
            BUILD_CATEGORY(IMU)
                SET_VAR(accStrength,0.035)
        END_CATEGORY

        ADD_SUBCATEGORY(Receiver, receiver)
        ADD_SUBCATEGORY(IMU, imu)
        BUILD_CATEGORY(Filtering)
            INIT_SUBCATEGORY(receiver),
            INIT_SUBCATEGORY(imu)
    END_CATEGORY


    INIT_CATEGORY(Calibrating)
        INIT_CATEGORY(Gyro)
            SETUP::SINT precision;SETUP::SFLOAT threshold;
            BUILD_CATEGORY(Gyro)
                SET_VAR(precision,3000),
                SET_VAR(threshold,40)
        END_CATEGORY

        ADD_SUBCATEGORY(Gyro, gyro)
        BUILD_CATEGORY(Calibrating)
            INIT_SUBCATEGORY(gyro)
    END_CATEGORY

    
    INIT_CATEGORY(PID)
        C3DPoint<double> P;C3DPoint<double> I;C3DPoint<double> D;C3DPoint<double> Limits;SETUP::SDOUBLE OverallLimits;
        BUILD_CATEGORY(PID)
            SET_3DPOINT(P, 4.0, 4.0, 2.5),
            SET_3DPOINT(I, 0.5, 0.5, 0.3),
            SET_3DPOINT(D, 2.0, 2.0, 1.5),
            SET_3DPOINT(Limits, 300, 150, 500),
            SET_VAR(OverallLimits, 700)
    END_CATEGORY


    INIT_CATEGORY(EngineValues)
        SETUP::SINT MINV;SETUP::SINT MAXV;SETUP::SINT STARTV;SETUP::SINT PWMFreq;
        BUILD_CATEGORY(EngineValues)
            SET_VAR(MINV, 1148),
            SET_VAR(MAXV, 1840),
            SET_VAR(STARTV, 1250),
            SET_VAR(PWMFreq, 12000)
    END_CATEGORY



    ADD_SUBCATEGORY(Pins,pins)ADD_SUBCATEGORY(RadioValues, radioValues)ADD_SUBCATEGORY(Filtering, filtering)ADD_SUBCATEGORY(Calibrating, calibrating)ADD_SUBCATEGORY(PID, pid)ADD_SUBCATEGORY(EngineValues, engineValues)

    BUILD_MAIN_CATEGORY(HSettings)INIT_SUBCATEGORY(pins),INIT_SUBCATEGORY(radioValues),INIT_SUBCATEGORY(filtering),INIT_SUBCATEGORY(calibrating),INIT_SUBCATEGORY(pid), INIT_SUBCATEGORY(engineValues)
    {}
    

    String getValueByName(const String& name) {
        SETUP::BY_STRING_EDITABLE* result = getValuePointerByName(name,this);
        if(result!=nullptr) return result->toString();
        else return "Command not found.";
    }
    bool setValueByName(const String& name, const String& value) {
        SETUP::BY_STRING_EDITABLE* result = getValuePointerByName(name,this);
        if(result!=nullptr) {result->setByString(value); return true;}
        return false;
    }
    String walk() {
        return walkByNode(this->childs.top());
    }
private:
    void init() override {}
    void work() override {
        if(Serial.available()){
            String cmd="";
            while(Serial.available()) {
                char c = Serial.read();
                cmd += c;
            }
            List<String> splited = UTILS::split(cmd, ' ');
            if(splited.count()==1) 
                Serial.println(getValueByName(cmd));
            else if(splited.count()>1) 
                if(setValueByName(splited[0],splited[1])) 
                    Serial.print("$");
                else 
                    Serial.print("!");
        }
    }

    SETUP::BY_STRING_EDITABLE* getValuePointerByName(const String& name, HSettingsCategory* category) {
        
        for(List<HSettingsCategory*>::Node *currentCategory = category->childs.top(); currentCategory!=nullptr; currentCategory=currentCategory->next) {
            for(List<SETUP::BY_STRING_EDITABLE*>::Node* currentVariable = currentCategory->val->variables.top(); currentVariable!=nullptr; currentVariable=currentVariable->next) {
                //Serial.println(currentCategory->val->getPrefix()+currentVariable->val->getName());
                if(currentCategory->val->getPrefix()+currentVariable->val->getName()==name) 
                    return currentVariable->val;
            }
            for(List<HSettingsCategory*>::Node *secondCategory = currentCategory->val->childs.top(); secondCategory!=nullptr; secondCategory=secondCategory->next) {
                for(List<SETUP::BY_STRING_EDITABLE*>::Node* currentVariable = secondCategory->val->variables.top(); currentVariable!=nullptr; currentVariable=currentVariable->next) {
                    //Serial.println(secondCategory->val->getPrefix()+currentVariable->val->getName());
                    if(secondCategory->val->getPrefix()+currentVariable->val->getName()==name) 
                        return currentVariable->val;
                }
            }
            
        }
        return nullptr;
    }
    String walkByNode(List<HSettingsCategory*>::Node* current) {
        String result="";
        while(current!=nullptr) {
            for(List<SETUP::BY_STRING_EDITABLE*>::Node* variable = current->val->variables.top(); variable!=nullptr; variable=variable->next) {
                result+=current->val->getPrefix()+variable->val->getName()+" "+variable->val->toString()+"\n";
            }
            //if(current->val->childs.count()>0) 
            result+=walkByNode(current->val->childs.top());
            current = current->next;
        }
        return result;
    }
};

HSettings settings;



#endif