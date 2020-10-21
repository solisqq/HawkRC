#include "HMenu.h"

HMenu::HMenu() {}
void HMenu::init() {
    currentCattegory = &settings;
    currentVal = nullptr;
}

String HMenu::toString() {
    return "";
}

bool HMenu::work() {
    return true;
}

void HMenu::setCategory(SETUP::HSettingsCategory* category) {
    currentItem = 0;
    currentCattegory = category;
    //menuString = settings.flatWalk(currentCattegory);
    currentState = 0;
}

void HMenu::handleSelectedStringID(int id) {
    if(id>=currentCattegory->childs.count()) {
        id -= currentCattegory->childs.count();
        setVariable(currentCattegory->variables[id]);
    }
    else 
        setCategory(currentCattegory->childs[id]);
}

void HMenu::setVariable(SETUP::BY_STRING_EDITABLE* var) {
    if(var->getTypeName()=="C3DPoint") {
        currentState = 2;
    } else {
        currentState = 1;
    }
    currentVal = var;
}

void HMenu::OnRXSwitchesRead(C4DPoint<uint8_t>& switches) {
    if(!prevSwitchState && switches[2]==1) {
        prevSwitchState = true;
        sendToSerial(convertToDisplayView(getMenuString()));
    } else if(prevSwitchState && switches[2]!=1) {
        prevSwitchState = false;
        settings.saveSettings();
    }
}
void HMenu::OnRXAxisRead(C4DPoint<int8_t>& axis) {
    if(prevSwitchState==true) {
        if(waitForRelease==true) {
            for(int i=1; i<4; i++)
                if(axis[i]>settings.radioValues.menuSelect.get() || axis[i]<-settings.radioValues.menuSelect.get())
                    return;
            waitForRelease = false;
        } else {
            int control = getControl(axis);//LEFT descending RIGHT ascending UP ascending DOWN descending
            if(control==0) return;
            waitForRelease = true;
            
            if(control==1) {//YAW RIGHT
            }           
            else if(control==-1) {//YAW LEFT
            }
            else if(control==2) {//PITCH UP
                goUp();
            }
            else if(control==-2) {//PITCH DOWN
                goDown();
            }
            else if(control==3) {//ROLL RIGHT
                goRight();
            }
            else if(control==-3) {//ROLL LEFT
                goLeft();
            }
            sendToSerial(convertToDisplayView(getMenuString()));
        }
    }
}

void HMenu::goUp() {
    if(currentState==0) {
        if(currentItem<=0) return;
        currentItem--;
        return;
    }
    if(currentState==1) {
        currentVal->swipe(true,0);
        settings.commitNeeded=true;
        return;
    }
    if(currentState==2) {
        currentVal->swipe(true, currentItemInStructure);
        settings.commitNeeded=true;
        return;
    }
}

void HMenu::goDown() {
    if(currentState==0) {
        if(currentItem>=currentCattegory->childs.count()+currentCattegory->variables.count()-1) return;
        currentItem++;
        return;
    }
    if(currentState==1) {
        currentVal->swipe(false,0);
        settings.commitNeeded=true;
        return;
    }
    if(currentState==2) {
        currentVal->swipe(false, currentItemInStructure);
        settings.commitNeeded=true;
        return;
    }
}

void HMenu::goLeft() {
    if(currentState==0) {
        if(currentCattegory->getParent()==nullptr) return;
        setCategory(currentCattegory->getParent());
        return;
    }
    if(currentState==1) {
        setCategory(currentCattegory);
        return;
    }
    if(currentState==2) {
        if(currentItemInStructure<=0) {
            setCategory(currentCattegory);
            currentItemInStructure=0;
            return;
        }
        currentItemInStructure--;
    }
}

void HMenu::goRight() {
    if(currentState==0) {
        handleSelectedStringID(currentItem);
        return;
    }
    if(currentState==1) {
        setCategory(currentCattegory);
        return;
    }
    if(currentState==2) {
        if(currentItemInStructure>=2) {
            currentItemInStructure=2;
            return;
        }
        currentItemInStructure++;
    }
}
//void HMenu::lowerValue() {if(currentState==1) {} if(currentState==2) {}}
//void HMenu::higherValue() {}

int HMenu::getControl(C4DPoint<int8_t>& axis) {
    for(int i=1; i<4; i++) {
        if(axis[i]>settings.radioValues.menuSelect.get()) {
            return i;
        } else if(axis[i]<-settings.radioValues.menuSelect.get()) {
            return -i;
        }
    }
    return 0;
}

String HMenu::getMenuString() {
    if(currentState==0) {
        return settings.flatWalk(currentCattegory, currentItem);
    } else if(currentState==1) {
        String toRet="";
        if(currentVal->getName().length()>14) 
            toRet = currentVal->getName().substring(0,14);
        else 
            toRet = currentVal->getName();
        
        String valueString = currentVal->toString();
        int rightStartPos = 21-valueString.length();
        for(int i=toRet.length(); i<rightStartPos; i++) toRet+=" ";
        toRet+=valueString;
        return toRet;
    } 
    String toRet="";
    if(currentVal->getName().length()>20) 
        toRet = currentVal->getName().substring(0,20);
    else 
        toRet = currentVal->getName();

    toRet+="\n"+currentVal->toString();
    return toRet;
}

String HMenu::convertToDisplayView(String text) {
    if(currentState>0) return text;
    String toRet="";
    List<String> lines = UTILS::split(text, '\n');
    if(currentItem==0) {
        toRet+=lines[0];
        if(lines.count()>1) {
            toRet+="\n"+lines[1];
        }
        if(lines.count()>2)
            toRet+="\n"+lines[2];
    }
    else if(currentItem==lines.count()-1) {
        if(lines.count()>2) {
            toRet+=lines[currentItem-2]+"\n";
        } 
        if(lines.count()>1) {
            toRet+=lines[currentItem-1]+"\n";
        }
        toRet+=lines[currentItem];
    }
    else toRet=lines[currentItem-1]+"\n"+lines[currentItem]+"\n"+lines[currentItem+1];
    
    return toRet;
}

void HMenu::setSerial(HardwareSerial* serial) {
    serialPort = serial;
}

void HMenu::sendToSerial(const String &text) {
    if(serialPort!=nullptr) {
        serialPort->print('@');
        serialPort->print(text);
        serialPort->print('@');
    }
}