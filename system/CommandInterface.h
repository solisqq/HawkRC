#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H
#include <Arduino.h>
#include <String.h>

class CommandInterface {
public:
	virtual void parseCmd(const String& cmd) {};
};

#endif