#ifndef ENGINE_H
#define ENGINE_H

#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"

int channelPinAvailable = 2;

class Engine : public AllowPrint {
public:
	int pinID, speed=settings.engineValues.MINV.get(); 
	int myChannel;
	Engine() {}
	void Init(int pin) {
		pinID = pin;
		myChannel = channelPinAvailable;
		ledcSetup(myChannel, settings.engineValues.PWMFreq.get(), 11);
		ledcAttachPin(pin, myChannel);
		channelPinAvailable++;
		SetSpeed(settings.engineValues.MINV.get());
	}
	void SetSpeed(int newSpeed) {
		if(newSpeed<settings.engineValues.MINV.get()) 
			speed = settings.engineValues.MINV.get();
		else if(newSpeed>settings.engineValues.MAXV.get())
			speed = settings.engineValues.MAXV.get();
		else
			speed=newSpeed;
		
		ledcWrite(myChannel,speed);
	}
	void Stop() {
		SetSpeed(settings.engineValues.MINV.get());
	}
	virtual String toString() {
		return static_cast<String>(speed);
	}
};

#endif