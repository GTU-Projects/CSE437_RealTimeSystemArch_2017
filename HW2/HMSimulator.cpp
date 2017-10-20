/*
 * File		: HMSimulator.cpp
 * Author	: hasan.men
 * Time		: 20.10.17
 * Brief	: This is a implementation of ISimulator interface. Simulates a
 *			  smart plant pump and heating systems.
 */
#include <iostream>
#include "HMSimulator.hpp"

HMSimulator::HMSimulator()
{

}


void HMSimulator::triggerADCTemperature() {
	std::cout << "ADC Temperature triggered." << std::endl;
}

void HMSimulator::triggerADCPressure()
{
	std::cout << "ADC Pressure triggered." << std::endl;
}


double HMSimulator::readADCPressure()
{
	return std::rand()%20 /10.0;
}

double HMSimulator::readADCTemperature()
{
	return std::rand()%20;
}

void HMSimulator::writeDACPump(const double value)
{
	//std::cout << "Write " << value << " to DAC pump success." << std::endl;
}

void HMSimulator::switchHeater(bool isOn)
{
	//std::cout << "Next heater position:" << isOn << "." << std::endl;
}


HMSimulator::~HMSimulator()
{
}

