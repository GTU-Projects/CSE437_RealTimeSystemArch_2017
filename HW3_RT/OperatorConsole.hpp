/*
 * File		: OperatorConsole.hpp
 * Author	: hasan.men
 * Time		: 20.10.17
 * Brief		: Operator console outputs pressure and temperature to console every x ms.
 */
#pragma once
#include "ISimulator.hpp"
#include "CONSTANTS.h"

#include <atomic>
#include <thread>
#include <chrono>

class OperatorConsole
{
public:
	OperatorConsole();
	~OperatorConsole();

	void savePressure(double pressure);
	void saveTemperature(double temperature);
private:

	std::thread *operatorTask;

	std::atomic<double> mLastPressure;
	std::atomic<double> mLastTemperature;

	HRC::time_point mPressLastUpdTime;
	HRC::time_point mTempLastUpdTime;

	void consoleThreadFunc();
};

