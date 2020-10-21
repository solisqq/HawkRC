#ifndef HMENU_H
#define HMENU_H
#include "Arduino.h"
#include <HardwareSerial.h>
#include "C:/Users/kamil/Documents/Programming/HawkRC/system/HCallbacks.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/structures/List.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettingsInterface.h"

class HMenu: public HProcess, public AllowPrint, public HCRXSwitchesRead, public HCRXAxisRead {
private:
    String menuString = "";
    SETUP::HSettingsCategory *currentCattegory;
    SETUP::BY_STRING_EDITABLE *currentVal;
    int currentState;
    int currentItem = 0;
    int currentItemInStructure = 0;
    bool prevSwitchState = false;
    bool waitForRelease = false;
    HardwareSerial* serialPort = nullptr;
public:
    HMenu();
    void init() override;
    void setSerial(HardwareSerial* serial);
    String toString() override;
    String getMenuString();
    String convertToDisplayView(String text);
protected:
    bool work() override;
    void OnRXAxisRead(C4DPoint<int8_t>&) override;
    void OnRXSwitchesRead(C4DPoint<uint8_t>&) override;
private:
    void setCategory(SETUP::HSettingsCategory* category);
    void setVariable(SETUP::BY_STRING_EDITABLE* var);
    void setCategoryByID(int);
    int getControl(C4DPoint<int8_t>&);
    void handleSelectedStringID(int);
    void sendToSerial(const String &text);

    void goUp();
    void goDown();
    void goLeft();
    void goRight();
};
#include "HMenu.cpp"

#endif