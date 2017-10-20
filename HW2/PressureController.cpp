/*
* File		: PressureController.cpp
* Author	: hasan.men
* Time		: 20.10.17
* Brief		: Pressure Controller reads pressure from ADC Pressure sensor every x ms.
*			  Calculates new pump pressure value according to old pressure value and writes to pump.
*/
#include <iostream>
#include "PressureController.hpp"
#include "ISimulator.hpp"



PressureController::PressureController(ISimulator& simulator,int interval) :
	simulator(simulator),workInterval(interval)
{
	// create pressure controller/calculator task
	pressureTask = new std::thread(&PressureController::pressTaskFunc,this);
}



PressureController::~PressureController()
{
	// wait until task done
	pressureTask->join();
	delete pressureTask;
}

double PressureController::getPressure() const
{
	return this->pressure;
}


void PressureController::pressTaskFunc() {
	double u;

	this->simulator.triggerADCPressure();
	while (1) {

		// read ADC-pressure value and control it
		this->pressure = this->simulator.readADCPressure();
		if (this->pressure < 0.9) {
			u = this->A - this->B*this->pressure;
		}
		else {
			u = 0;
		}

		simulator.writeDACPump(u);

		//std::cout << "Pressure Task writed to Pump." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(workInterval));
	}
}
