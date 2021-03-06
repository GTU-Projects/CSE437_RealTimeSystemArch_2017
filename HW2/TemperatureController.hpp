/*
 * File		: TemperatureController.hpp
 * Author	: hasan.men
 * Time		: 20.10.17
 * Brief	: Temperature Controller reads temperature from ADC Temperature sensor every x ms.
 *			  Checks temperature with C,D values and sets heater state.
 */
#pragma once
#include <thread>
#include "ISimulator.hpp"

class TemperatureController
{
public:
	TemperatureController(ISimulator& simulator, int interval);
	~TemperatureController();

	double getTemperature() const;
private:
	int workInterval;
	double temperature;

	const double C = 5.0; // temperature min bound
	const double D = 15.0; // temperature max bound

	ISimulator &simulator;

	std::thread *temperatureTask;
	void threadFunc();
};
