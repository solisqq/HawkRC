#include <Arduino.h>
#include <ESP.h>
#include <WiFi.h>
#include "C:/Users/kamil/Documents/Programming/HawkRC/math/C3DPoint.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/handlers/Timer/FrequencyCounter.h"
#include "C:/Users/kamil/Documents/Programming/HawkRC/components/mpu/MPU9250.h"

hw_timer_t* timer = NULL;

FrequencyCounter loop0freq;
FrequencyCounter loop1freq;

void IRAM_ATTR onTimer() {
    mpu.run();
}

void loop0(void* unused) {
    
    mpu.start(16000, "mpu", false);
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 100, true);
    timerAlarmEnable(timer);
    for (;;) {vTaskDelay(100);}
}

void setup(){
    setCpuFrequencyMhz(240);
    Serial.begin(500000);
    WiFi.mode(WIFI_OFF);
    btStop();
    
    xTaskCreatePinnedToCore(loop0, "MPUThreading", 8192, nullptr, 5, nullptr, 0);
    //loop0(nullptr);
    loop0freq.enablePrinting(true, "Stressed:");
}


void loop() {
    delay(1);
    Serial.println(mpu.getGyro().toString());
}