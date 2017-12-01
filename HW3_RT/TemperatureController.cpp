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

TemperatureController::TemperatureController(ISimulator& mRefSimulator, OperatorConsole & opConsole):
	mRefSimulator(mRefSimulator), mRefOpConsole(opConsole)
{
	// create temperature controller task
	this->temperatureTask = new std::thread(&TemperatureController::threadFunc, this);
	this->setPriority(SCHED_RR,10); // SCHED raund robin 10 priority

}

void TemperatureController::setPriority(int policy, int prio){

	sched_param schedParams;

	schedParams.sched_priority=prio;

	// get pthread_t object
	auto handlePthread = this->temperatureTask->native_handle();

	if(pthread_setschedparam(handlePthread,policy,&schedParams)){
		std::cerr<<"Temperature Thread scheduling error"<<std::endl;
	}
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

		int passedTime = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
		std::this_thread::sleep_for(std::chrono::milliseconds(TEMPERATURE_C_WORK_INT -passedTime));
	}
}



