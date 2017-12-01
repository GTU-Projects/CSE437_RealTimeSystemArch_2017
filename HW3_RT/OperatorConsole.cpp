/*
 * File		: OperatorConsole.cpp
 * Author	: hasan.men
 * Time		: 20.10.17
 * Brief		: Operator console outputs pressure and temperature to console every x ms.
 */
#include "OperatorConsole.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>


OperatorConsole::OperatorConsole()
{
	this->mLastPressure = 0;
	this->mLastTemperature = 0;

	//mLastPressure = new std::atomic<HRC::time_point>;
	//mLastTemperature;

	this->operatorTask = new std::thread(&OperatorConsole::consoleThreadFunc, this);
}

// save latest value of pressure and update time
void OperatorConsole::savePressure(double pressure) {
	this->mLastPressure = pressure;
	mPressLastUpdTime = HRC::now();
}

// save latest value of temperature and update time
void OperatorConsole::saveTemperature(double temperature) {
	this->mLastTemperature = temperature;
	mTempLastUpdTime = HRC::now();
}

void OperatorConsole::consoleThreadFunc(void) {

	int pressUpdateDiff; // store time gap between last pressure update
	int tempUpdateDiff; //store time gap between last temperature update
	int passedTime;

	bool printPressWarning=false;
	bool printTempWarning = false;

	HRC::time_point t0,t1,t3;
	std::cout << std::fixed << std::setprecision(2);

	mPressLastUpdTime = HRC::now();
	mTempLastUpdTime = HRC::now();

	while (true) {
		t0 = HRC::now();
		printPressWarning = true;
		printTempWarning = true;


		// control every 10ms if sensors pass deadline or not
		// 50*10 = 500ms 
		for (int i = 0; i < 49; ++i) {
			t3 = HRC::now();
			pressUpdateDiff = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - mPressLastUpdTime).count();
			pressUpdateDiff -= PRESSURE_C_WORK_INT;
			if (pressUpdateDiff > 0 && printPressWarning) {
				std::cout << "WARNING! PressureController deadline miss by " << pressUpdateDiff << " milliseconds." << std::endl;
				printPressWarning = false;
			}

			tempUpdateDiff = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - mTempLastUpdTime).count();
			tempUpdateDiff -= TEMPERATURE_C_WORK_INT;
			if (tempUpdateDiff > 0 && printTempWarning) {
				std::cout << "WARNING! TemperatureController deadline miss by " << pressUpdateDiff << " milliseconds." << std::endl;
				printTempWarning = false;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		
		std::cout << "Temperature:" << this->mLastTemperature << ", Pressure:" << this->mLastPressure<<std::endl;
		
		t1 = HRC::now();

		passedTime = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
		std::this_thread::sleep_for(std::chrono::milliseconds(OPERATOR_C_WORK_INT - passedTime ));
	
	}
}


OperatorConsole::~OperatorConsole()
{
	this->operatorTask->join();
	delete this->operatorTask;
}