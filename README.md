# HawkRC
HawkRC (old: FC_FIN) - flight controller for quadcopter with object oriented features.
- NodeMCU esp32
- MPU9250 (GY-91)
- Atmega 328
- Frsky D4R RX
- 5V Pololu stepdown (up to 20V) voltage regulator
- I2C 0.96" OLED display
- Voltage divider for 3-4S input (pin 4)

Short description:

HSystem and HProcess allow to run task at certain frequency:
```cpp
HIMU imu;
hsystem.addProcess(&imu, 1000, "imu");
```

"addProcess" member functions allows to add any object which inherits from HProcess to system processes. First parameter is an pointer to an object, next one is frequency. Last parameter is for debugging purposes which will be discussed later. For example lets create a HIMU class:
```cpp
class HIMU: public HProcess, public HCGyroRead, public AllowPrint {
	C3DPoint<float> values;
public:
	HIMU();
	void init() override;
	bool work() override;
	String toString() override;
	void OnGyroRead(const C3DPoint<float>&) override;
	bool parseCmd(const String& cmd) override;
}
```

HIMU inherits from HProcess, HCGyroRead and AllowPrint. As it was mentioned HProcess pointer may be passed to HSystem and it will do a task at certain frequency. 
HProcess give access to member functions like init() and work(). Its easy to compare them to setup() and loop() Arduino's functions. init() will be ran once when process is added. work() will be executed X time per second, where X was our frequency.
Inheritance from HCGyroRead gives us access to `OnGyroRead(const C3DPoint<float>&)` member function which will be executed when data from gyroscope was received. There are more callback functions like: OnRXRead (received data from radio), OnAccelRead (accelerometer), OnIMUReady, OnSteerReady (prepared data based on RX) and etc.
AllowPrint toString() member function give access to debugging. We can pass there data as string to be shown in SerialPort when asked. 
```cpp
String HIMU::toString() {
	return values.toString();
}
```
This way we can receive variable 'values' (converted to String) in SerialPort just by sending '/imu' (3rd parameter of addProcess).
 
