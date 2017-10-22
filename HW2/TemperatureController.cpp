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
#include "ISimulator.hpp"

using HRC = std::chrono::high_resolution_clock;

TemperatureController::TemperatureController(ISimulator& simulator,int interval):
	simulator(simulator),workInterval(interval)
{
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
	double u;
	HRC::time_point t0, t1;
	
	while (1) {
		t0 = HRC::now();
		this->simulator.triggerADCTemperature();
		// read ADC-pressure value and control it
		this->temperature = this->simulator.readADCTemperature();
		// check temperature, set next state
		if (this->temperature < C) {
			this->simulator.switchHeater(true);
		}
		else {
			this->simulator.switchHeater(false);
		}

		t1 = HRC::now();

		auto passedTime = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
		std::this_thread::sleep_for(std::chrono::milliseconds(workInterval-passedTime));
	}
}



