#include "Arduino.h"

#ifndef ADXL362_h
#define ADXL362_h

#define FILTER_CTL 0x2C

#define RANGE 6
#define ODR 0

#define ADXL362_2G 0
#define ADXL362_4G 1
#define ADXL362_8G 2

#define ADXL362_RATE_12_5 0 // 12.5 Hz
#define ADXL362_RATE_25   1 // 25 Hz
#define ADXL362_RATE_50   2 // 50 Hz
#define ADXL362_RATE_100  3 // 100 Hz (reset default)
#define ADXL362_RATE_200  4 // 200 Hz
#define ADXL362_RATE_400  7 // 400 Hz

class ADXL362
{
public:

	ADXL362();

	//
	// Basic Device control and readback functions
	//
	void begin(int16_t chipSelectPin = 10);
	void beginMeasure();
	int16_t readXData();
	int16_t readYData();
	int16_t readZData();
	void readXYZTData(int16_t &XData, int16_t &YData, int16_t &ZData, int16_t &Temperature);
	int16_t readTemp();
	void setRange(int sense);
	void setODR(int rate);

	//
	// Activity/Inactivity interrupt functions
	//
	void setupDCActivityInterrupt(int16_t threshold, byte time);
	void setupDCInactivityInterrupt(int16_t threshold, int16_t time);
  void setupACActivityInterrupt(int16_t threshold, byte time);
	void setupACInactivityInterrupt(int16_t threshold, int16_t time);

	// TODO:
	// void mapINT1
	// void mapINT2
	// void autoSleep
	// void activityInterruptControl
	//		- Activity, Inactivity, Both
	//		- Referenced, Absolute
	//		- Free Fall, Linked Mode, Loop Mode

	void checkAllControlRegs();

private:
  int16_t slaveSelectPin = 10;

  //  Low-level SPI control, to simplify overall coding
	byte SPIreadOneRegister(byte regAddress);
	void SPIwriteOneRegister(byte regAddress, byte regValue);
	int16_t  SPIreadTwoRegisters(byte regAddress);
	void SPIwriteTwoRegisters(byte regAddress, int16_t twoRegValue);


};

#endif
