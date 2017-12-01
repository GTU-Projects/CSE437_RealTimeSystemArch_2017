/*
 * File		: TemperatureController.hpp
 * Author	: hasan.men
 * Time		: 01.12.2017
 * Brief	: Temperature Controller reads temperature from ADC Temperature sensor every x ms.
 *			  Checks temperature with C,D values and sets heater state.
 */
#pragma once
#include <thread>
#include "CONSTANTS.h"
#include "OperatorConsole.hpp"
#include "ISimulator.hpp"

class TemperatureController
{
public:
	TemperatureController(ISimulator& mRefSimulator,OperatorConsole &opConsole);
	~TemperatureController();
	double getTemperature() const;
private:
	double temperature;

	const double C = 4.0; // temperature min bound
	const double D = 12.0; // temperature max bound

	ISimulator &mRefSimulator;
	
	OperatorConsole &mRefOpConsole;

	std::thread *temperatureTask;

	void threadFunc();
	void setPriority(int policy, int prio);
};
