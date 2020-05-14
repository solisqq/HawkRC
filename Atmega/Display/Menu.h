#ifndef CMENU_H
#define CMENU_H

#include "Arduino.h"
#include "Button.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/Atmega/OutputBoard/Pinout.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"
#include "C:/Users/kamil/Documents/Arduino/libraries/Adafruit_GFX_Library/Adafruit_GFX.h"
#include <Adafruit_SSD1306.h>
#include "MenuElement.h"
#include "ManuMain.h"
#include "Display.h"

class CMenu {
private:
    Display *display;
    List<CButton> buttons;
    List<CMenuElement*> menuElements;
    List<CMenuElement*>::Node* active;
    MSTimer refreshTimer;
public:
    CMenu();
    void init(Display *disp);
    void updateButtons();
    void addMenuElement(CMenuElement* element, bool needsRefresh=false);
    void activate(List<CMenuElement*>::Node* nodeToActivate);
};
#include "Menu.cpp"

#endif