#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H
#include "Arduino.h"
#include "C:/Users/kamil/Documents/Arduino/libraries/Adafruit_GFX_Library/Adafruit_GFX.h"
#include <Adafruit_SSD1306.h>
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/Timer.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/ErrorSrc.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/ErrorHandler/Error.h"
#include "Bitmaps.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/Point.h"

class Display: public ErrorSrc {
    Adafruit_SSD1306 display;
    CPoint<uint8_t> errorPos;
    List<CError*>* currentErrors;
    String errorString = "";
public:
    Display();
    bool init();
    virtual void showErrors(List<CError*>& errors);
    void writeLine(uint8_t fontSize, CPoint<uint8_t> position, String line) ;
    void writeLines(uint8_t fontSize, CPoint<uint8_t> position, const List<String>& textLines);
    void updateErrorsSection();
    Adafruit_SSD1306& getPrimitive();
};
#include "Display.cpp"

#endif