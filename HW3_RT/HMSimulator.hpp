/*
 * File		: HMSimulator.hpp
 * Author	: hasan.men
 * Time		: 20.10.17
 * Brief	: This is a implementation of ISimulator interface. Simulates a 
			  smart plant pump and heating systems. 
 */
#pragma once

#include "ISimulator.hpp"
#include "OperatorConsole.hpp"

class HMSimulator :
	public ISimulator
{
public:
	HMSimulator();
	~HMSimulator();

	// direct access to hw
	void triggerADCPressure();
	void triggerADCTemperature();
	double readADCPressure();
	double readADCTemperature();
	void writeDACPump(const double value);
	void switchHeater(bool isOn);

private:
	double testTemperature; // temperature value to test simulator. Value will be increased and decreased
	double testPressure; // pressure value will be increased and decreased for testing
};

