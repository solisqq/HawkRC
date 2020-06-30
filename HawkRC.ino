#include "system/HSystem.h"
#include "system/HProcess.h"
#include "system/HDebugger.h"
#include "components/HReceiver.h"
#include "components/HSteering.h"
#include "components/HGyro.h"
#include "components/HAccelerometer.h"
#include "components/HIMU.h"
#include "components/HPID.h"
#include "components/HBattery.h"
#include "handlers/Timer/Timer.h"
#include "components/HController.h"

HSystem hsystem;
HReceiver rx;
HSteering steering;
HGyro gyroscope;
HDebugger debugger;
HAccelerometer accelerometer;
HIMU imu;
HPID pid;
HBattery battery;
HController controller;

MSTimer sendDataToVisualizer_Timer;

void setup(){
    Serial.begin(250000);
    Serial.print("INIT{");
    hsystem.addProcess(&rx, 100, "Receiver");
    hsystem.addProcess(&steering, 50, "Steering");
    hsystem.addProcess(&gyroscope, 1000, "Gyro");
    hsystem.addProcess(&accelerometer, 100, "Accelerometer");
    hsystem.addProcess(&debugger, 200, "Debugger");
    hsystem.addProcess(&imu, 1000, "IMU");
    hsystem.addProcess(&pid, 1000, "PID");
    hsystem.addProcess(&battery, 100, "Battery");
    hsystem.addProcess(&controller, 500, "Controller");
    hsystem.addProcess(&settings, 10, "Settings");
    Serial.println("}");

    Serial.println("SETTINGS{");
    Serial.print(settings.walk());
    Serial.println("}");

    //debugger.addPrintable(&rx, "rx");
    debugger.addPrintable(&steering, "stear");
    debugger.addPrintable(&gyroscope, "gyro");
    debugger.addPrintable(&accelerometer, "accel");
    debugger.addPrintable(&imu, "imu");
    debugger.addPrintable(&pid, "pid");
    debugger.addPrintable(&controller, "control");

    //controller.debug(true);
    sendDataToVisualizer_Timer.start(200);

    //battery.debug(true);
    //debugger.addPrintable(&gyroscope);
    //gyroscope.debug(true);
}
void loop(){
    hsystem.operate();
    if(sendDataToVisualizer_Timer.isTimeout()) {
        rx.getSerial().write(static_cast<int8_t>(-126));
        rx.getSerial().write(static_cast<int8_t>(battery.getLevel()));
        rx.getSerial().write(static_cast<int8_t>(imu.state));
        rx.getSerial().write(static_cast<int8_t>(3));
        rx.getSerial().write(static_cast<int8_t>(-127));
    }
}