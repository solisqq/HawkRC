#ifndef CMENU_MAIN
#define CMENU_MAIN

#include "Arduino.h"
#include "MenuElement.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/Atmega/OutputBoard/Pinout.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/Point.h"
#include "C:/Users/kamil/Documents/Arduino/libraries/Adafruit_GFX_Library/Adafruit_GFX.h"
#include <Adafruit_SSD1306.h>
#include "Display.h"

class MenuMain: public CMenuElement {
public:
    MenuMain(){}
    virtual void paint(){
        if(display==nullptr) return;
        List<String> linesToPrint = List<String>();
        linesToPrint.pushBack("HawkRC by Solis V0.1");
        linesToPrint.pushBack("                    ");
        linesToPrint.pushBack("Down btn to navigate");
        display->writeLines(1, CPoint<uint8_t>(0,0), linesToPrint);
        /*display->clearDisplay();
        display->display();
        display->setTextColor(SSD1306_WHITE);
        display->setTextSize(1);
        display->setCursor(0,0);
        display->println("HawkRC Atmega V0.1");
        display->println("       By SolisQQ");
        display->print("Use down button to navigate");
        display->setCursor(0,0);
        display->display();*/
    }
    virtual void buttonPushed(Pinout::Buttons buttonID) {

    }
};
#endif