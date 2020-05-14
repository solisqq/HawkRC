#ifndef CMENU_ELEMENT
#define CMENU_ELEMENT

#include "Arduino.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/Atmega/OutputBoard/Pinout.h"
#include "Display.h"

class CMenuElement {
protected:
    Display *display=nullptr;
    bool active=false;
    bool needsRefresh=false;
public:
    void initializeElement(Display *disp) {
        display = disp;
    }
    void activateElement() {
        active=true;
    }
    void deactivateElement() {
        active=false;
    }
    bool isMenuElementActive() {
        return active;
    }
    void setRefresh(bool val) {
        needsRefresh = true;
    }
    bool doesNeedsRefresh() {
        return needsRefresh;
    }
    virtual void paint()=0;
    virtual void buttonPushed(Pinout::Buttons buttonID)=0;
};
#endif