#include "Error.h"
CError::CError(ErrorType errorType, String errorText, ErrorLed errorLed): type(errorType), text(errorText), eled(errorLed), showed(false) {}
void CError::active(){
    showed = true;
}
void CError::disactive(){
    showed = false;
}
bool CError::isActive(){
    return showed;
}