#include "ErrorHandler.h"

List<CError*>& ErrorHandler::getErrors() {
    return errors;
}
bool ErrorHandler::raise(CError &error) {
    if(error.isActive()) return false;
    error.active();
    errors.pushFront(&error);
    update();
    return true;
}
bool ErrorHandler::cancel(CError &error) {
    if(!error.isActive()) return false;
    error.disactive();
    errors.remove(&error);
    update();
    return true;
}

void ErrorHandler::update() {
    for(List<ErrorSrc*>::Node* it = sources.top(); it!=nullptr; it=it->next) 
        it->val->showErrors(errors);
}

void ErrorHandler::addSource(ErrorSrc *err_src) {
    sources.pushFront(err_src);
}