#include "Display.h"

Display::Display() {
    errorPos = CPoint<uint8_t>(0,24);
}
bool Display::init() {
    display = Adafruit_SSD1306(128, 32, &Wire, -1);
    if(display.begin(SSD1306_SWITCHCAPVCC, 0x3C)==false) return false;
    display.display();
    display.clearDisplay();
    display.invertDisplay(false);
    display.drawBitmap(0, 0, Bitmaps::Logo::HawkRCLogo, Bitmaps::Logo::width, Bitmaps::Logo::height, 1);
    display.setTextColor(0xFFFF, 0x0000);
    display.display();
    delay(2000);
}

void Display::showErrors(List<CError*>& errors) {
    errorString="ERROR: ";
    currentErrors = &errors;
    for(List<CError*>::Node* it=errors.top(); it!=nullptr; it=it->next) 
        errorString+=it->val->text+" ";
    
    //writeLine(1,errorPos, strings);
    updateErrorsSection();
    display.display();
}

void Display::writeLine(uint8_t fontSize, CPoint<uint8_t> position, String line) {
    
    display.clearDisplay();
    display.display();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(fontSize);
    display.setCursor(position.X(), position.Y());
    display.print(line);
    display.setCursor(0,0);
    display.display();
}

void Display::writeLines(uint8_t fontSize, CPoint<uint8_t> position, const List<String>& textLines) {
    
    display.clearDisplay();
    display.display();
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display.setTextSize(1);
    display.setCursor(position.X(), position.Y());
    for(List<String>::Node *it=textLines.top(); it!=nullptr; it=it->next) {
        display.println(it->val);
        //Serial.println(it->val);
    }
    updateErrorsSection();
    display.display();
}
void Display::updateErrorsSection() {
    display.setCursor(errorPos.X(), errorPos.Y());
    display.print("                        ");
    //display.display();
    display.setCursor(errorPos.X(), errorPos.Y());
    display.print(errorString);
}

Adafruit_SSD1306& Display::getPrimitive() {
    return display;
}