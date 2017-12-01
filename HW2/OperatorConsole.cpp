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


OperatorConsole::OperatorConsole(int workPeriodInMS)
{
	this->mLastPressure = 0;
	this->mLastTemperature = 0;
	this->workInterval = workPeriodInMS;

	//mLastPressure = new std::atomic<HRC::time_point>;
	//mLastTemperature;

	this->operatorTask = new std::thread(&OperatorConsole::consoleThreadFunc, this);
}


void OperatorConsole::savePressure(double pressure) {
	this->mLastPressure = pressure;
}

void OperatorConsole::saveTemperature(double temperature) {
	this->mLastTemperature = temperature;
}

void OperatorConsole::consoleThreadFunc(void) {

	std::cout << std::fixed << std::setprecision(2);
	while (true) {
		
		std::cout << "Temperature:" << this->mLastTemperature << ", Pressure:" << this->mLastPressure<<std::endl;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	
	}
}


OperatorConsole::~OperatorConsole()
{
	this->operatorTask->join();
	delete this->operatorTask;
}