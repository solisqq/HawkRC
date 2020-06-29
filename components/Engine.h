#ifndef ENGINE_H
#define ENGINE_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"

int channelPinAvailable = 2;

class Engine : public AllowPrint {
public:
	int pinID, speed=HSettings::EngineValues::MIN;
	int myChannel;
	Engine() {}
	void Init(int pin) {
		pinID = pin;
		myChannel = channelPinAvailable;
		ledcSetup(myChannel, HSettings::EngineValues::PWMFreq, 11);
		ledcAttachPin(pin, myChannel);
		channelPinAvailable++;
		SetSpeed(HSettings::EngineValues::MIN);
	}
	void SetSpeed(int newSpeed) {
		if(newSpeed<HSettings::EngineValues::MIN) 
			speed = HSettings::EngineValues::MIN;
		else if(newSpeed>HSettings::EngineValues::MAX)
			speed = HSettings::EngineValues::MAX;
		else
			speed=newSpeed;
		
		ledcWrite(myChannel,speed);
	}
	void Stop() {
		SetSpeed(HSettings::EngineValues::MIN);
	}
	virtual String toString() {
		return static_cast<String>(speed);
	}
};

#endif