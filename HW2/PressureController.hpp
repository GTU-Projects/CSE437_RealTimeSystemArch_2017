/*
 * File		: PressureController.hpp
 * Author	: hasan.men
 * Time		: 20.10.17
 * Brief	: Pressure Controller reads pressure from ADC Pressure sensor every x ms.
 *			  Calculates new pump pressure value according to old pressure value.	
*/
#pragma once

#include <thread>
#include "ISimulator.hpp"



class PressureController
{
public:
	PressureController(ISimulator &simulator,int interval);
	~PressureController();


	double getPressure() const;
	
private:
	int workInterval; // 10Hz = 100ms
	double pressure; // calculated pressure value

	// Pressure calc. ratio values
	const  double A = 1.2;
	const  double B = 1.0;

	std::thread *pressureTask;
	ISimulator &simulator;

	void pressTaskFunc();

};
