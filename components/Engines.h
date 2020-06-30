#ifndef ENGINES_H
#define ENGINES_H

#include "Engine.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/HSettings.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C4DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Output/AllowPrint.h"

class Engines : public AllowPrint {
public:
	Engine frontLeft, frontRight, backLeft, backRight;
	Engines() {}
	void Init() {
		frontLeft.Init(settings.pins.engines.frontLeft.get());
        frontRight.Init(settings.pins.engines.frontRight.get());
        backLeft.Init(settings.pins.engines.backLeft.get());
        backRight.Init(settings.pins.engines.backRight.get());
	}
	void SetSpeedAll(C4DPoint<int>& values) {
        SetSpeedAll(values.X(),values.Y(),values.Z(),values.A());
	}
    void SetSpeedAll(int value) {
        SetSpeedAll(value,value,value,value);
	}
    void SetSpeedAll(int frontLeftSpeed,int frontRightSpeed,int backLeftSpeed, int backRightSpeed) {
        frontLeft.SetSpeed(frontLeftSpeed);
        frontRight.SetSpeed(frontRightSpeed);
        backLeft.SetSpeed(backLeftSpeed);
        backRight.SetSpeed(backRightSpeed);
	}
	void StopAll() {
		SetSpeedAll(settings.engineValues.MINV.get());
	}
	virtual String toString() {
		return frontLeft.toString()+" "+frontRight.toString()+" "+backLeft.toString()+" "+backRight.toString();
	}
};

#endif