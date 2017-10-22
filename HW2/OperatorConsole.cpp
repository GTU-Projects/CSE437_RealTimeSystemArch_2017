/*
 * File		: OperatorConsole.cpp
 * Author	: hasan.men
 * Time		: 20.10.17
 * Brief		: Operator console outputs pressure and temperature to console every x ms.
 */
#include "OperatorConsole.hpp"
#include <iostream>
#include <chrono>


OperatorConsole::OperatorConsole(PressureController& pressCont, TemperatureController& tempCont, int workInterval) :
	pressCont(pressCont), tempCont(tempCont), workInterval(workInterval)
{
	this->operatorTask = new std::thread(&OperatorConsole::threadFunc, this);
}

void OperatorConsole::run(void) {

}

void OperatorConsole::threadFunc()
{
	double pressure, temperature;
	while (true) {

		pressure = pressCont.getPressure();
		temperature = tempCont.getTemperature();

		std::cout << "Pressure:" <<pressure << " Temperature:" << temperature << std::endl;

		// work every x ms
		std::this_thread::sleep_for(std::chrono::milliseconds(this->workInterval));

	}
}

OperatorConsole::~OperatorConsole()
{
	this->operatorTask->join();
	delete this->operatorTask;
}
