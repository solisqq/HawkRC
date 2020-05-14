#include "Menu.h"

CMenu::CMenu(){}

void CMenu::init(Display *disp){
    display = disp;
    for(int i=0; i<4; i++) 
        buttons.pushBack(CButton());
    
    List<CButton>::Node* it = buttons.top();
    it->val.init(Pinout::Buttons::Up);
    it = it->next;
    it->val.init(Pinout::Buttons::Left);
    it = it->next;
    it->val.init(Pinout::Buttons::Right);
    it = it->next;
    it->val.init(Pinout::Buttons::Down);
    it = it->next;

    MenuMain* menuMain = new MenuMain();
    menuMain->initializeElement(display);
    menuElements.pushBack(menuMain);
    activate(menuElements.top());
    refreshTimer.start(50);
}

void CMenu::addMenuElement(CMenuElement* element, bool needsRefresh=false) {
    element->initializeElement(display);
    element->setRefresh(needsRefresh);
    menuElements.pushBack(element);
}
void CMenu::activate(List<CMenuElement*>::Node* nodeToActivate) {
    active->val->deactivateElement();
    active = nodeToActivate;
    active->val->activateElement();
    active->val->paint();
}
void CMenu::updateButtons() {
    if(refreshTimer.isTimeout())
        if(active->val->doesNeedsRefresh())
            active->val->paint();
    
    for(List<CButton>::Node* it = buttons.top(); it!=nullptr; it=it->next) {
        if(it->val.isReleased()) {
            if(it->val.getType()==Pinout::Buttons::Down) {
                display->getPrimitive().clearDisplay();
                if(active->next==nullptr) {
                    activate(menuElements.top());
                }
                else {
                    activate(active->next);
                }
                return;
            }
            active->val->buttonPushed(it->val.getType());
            return;
        }
    }
}