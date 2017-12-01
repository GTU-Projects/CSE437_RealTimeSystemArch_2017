/*
 * File		: TemperatureController.cpp
 * Author	: hasan.men
 * Time		: 20.10.17
 * Brief	: Temperature Controller reads temperature from ADC Temperature sensor every x ms.
 *			  Checks temperature with C,D values and sets heater state.
*/

#include <iostream>
#include <chrono>
#include "TemperatureController.hpp"

using HRC = std::chrono::high_resolution_clock;

TemperatureController::TemperatureController(ISimulator& mRefSimulator, OperatorConsole & opConsole, int interval):
	mRefSimulator(mRefSimulator), mRefOpConsole(opConsole)
{
	this->workInterval = interval;

	// create temperature controller task
	this->temperatureTask = new std::thread(&TemperatureController::threadFunc, this);
}


TemperatureController::~TemperatureController()
{
	temperatureTask->join();
	delete temperatureTask;
}

double TemperatureController::getTemperature() const
{
	return this->temperature;
}

void TemperatureController::threadFunc() {
	bool switchStatus = false;
	HRC::time_point t0, t1;

	
	while (1) {
		t0 = HRC::now();
		this->mRefSimulator.triggerADCTemperature();
		// read ADC-pressure value and control it
		this->temperature = this->mRefSimulator.readADCTemperature();

		// save/print temperature on the console
		this->mRefOpConsole.saveTemperature(this->temperature);

		// check temperature, set next state
		if (this->temperature >D) {
			switchStatus = false;
		}
		else if (this->temperature<C){
			switchStatus = true;
		}

		this->mRefSimulator.switchHeater(switchStatus);

		t1 = HRC::now();

		auto passedTime = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
		std::this_thread::sleep_for(std::chrono::milliseconds(workInterval-passedTime));
	}
}



