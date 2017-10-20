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

	this->simulator.triggerADCTemperature();
	while (1) {

		// read ADC-pressure value and control it
		this->temperature = this->simulator.readADCTemperature();
		// check temperature, set next state
		if (this->temperature < C) {
			this->simulator.switchHeater(true);
		}
		else {
			this->simulator.switchHeater(false);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(workInterval));
	}
}



