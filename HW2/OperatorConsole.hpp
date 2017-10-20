/*
 * File		: OperatorConsole.hpp
 * Author	: hasan.men
 * Time		: 20.10.17
 * Brief		: Operator console outputs pressure and temperature to console every x ms.
 */
#pragma once
#include <thread>
#include "PressureController.hpp"
#include "TemperatureController.hpp"

class OperatorConsole
{
public:
	OperatorConsole(PressureController& pressCont, TemperatureController& tempController, int workInterval);
	~OperatorConsole();

	void run(void);
private:
	std::thread *operatorTask;

	PressureController& pressCont;
	TemperatureController& tempCont;

	int workInterval;

	void threadFunc();
};

