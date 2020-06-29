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
		frontLeft.Init(HSettings::Pins::Engines::frontLeft);
        frontRight.Init(HSettings::Pins::Engines::frontRight);
        backLeft.Init(HSettings::Pins::Engines::backLeft);
        backRight.Init(HSettings::Pins::Engines::backRight);
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
		SetSpeedAll(HSettings::EngineValues::MIN);
	}
	virtual String toString() {
		return frontLeft.toString()+" "+frontRight.toString()+" "+backLeft.toString()+" "+backRight.toString();
	}
};

#endif