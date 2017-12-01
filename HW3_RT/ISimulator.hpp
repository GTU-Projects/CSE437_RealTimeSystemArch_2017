#pragma once
/*
 * File		: ISimulator.hpp
 * Author	: hasan.men
 * Time		: 20.10.17
 */

#include <chrono>

/*
	Please implment this interface.
*/
class ISimulator {
public:
	virtual void triggerADCPressure() = 0;
	virtual void triggerADCTemperature() = 0;
	virtual double readADCPressure() = 0;
	virtual double readADCTemperature() = 0;
	virtual void writeDACPump(const double value) = 0;
	virtual void switchHeater(bool isOn) = 0;	
};

using HRC = std::chrono::high_resolution_clock;