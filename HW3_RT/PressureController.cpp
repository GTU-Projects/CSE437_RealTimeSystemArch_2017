/*
* File		: PressureController.cpp
* Author	: hasan.men
* Time		: 20.10.17
* Brief		: Pressure Controller reads pressure from ADC Pressure sensor every x ms.
*			  Calculates new pump pressure value according to old pressure value and writes to pump.
*/
#include <iostream>
#include <chrono>
#include "PressureController.hpp"
#include "ISimulator.hpp"


PressureController::PressureController(ISimulator& simulator,OperatorConsole &opConsole,int interval) :
	mRefSimulator(simulator), mRefOpConsole(opConsole) ,workInterval(interval)
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

	HRC::time_point t0,t1;
	while (1) {

		t0 = HRC::now(); // start of do some work area

		// trigger ADC to take pressure value
		this->mRefSimulator.triggerADCPressure();

		// read ADC-pressure value and control it
		this->pressure = this->mRefSimulator.readADCPressure();

		this->mRefOpConsole.savePressure(this->pressure);
		

		if (this->pressure < 0.9000) {
			u = this->A - this->B*this->pressure;
		}
		else {
			u = 0;
		}
		mRefSimulator.writeDACPump(u);

		t1 = HRC::now(); // end of do some work area

		//std::cout << "Pressure Task writed to Pump." << std::endl;
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
		std::this_thread::sleep_for(std::chrono::milliseconds(workInterval-ms));
	}
}
