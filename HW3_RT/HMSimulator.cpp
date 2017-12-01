/*
 * File		: HMSimulator.cpp
 * Author	: hasan.men
 * Time		: 20.10.17
 * Brief	: This is a implementation of ISimulator interface. Simulates a
 *			  smart plant pump and heating systems.
 */
#include <iostream>
#include <random>
#include "HMSimulator.hpp"

HMSimulator::HMSimulator()
{
	testTemperature = 0;
	testPressure = 0;
}


void HMSimulator::triggerADCTemperature()
{
	// std::cout << "Trigger ADC Temperature" << std::endl;
	// Function will take a little time in real usage
}

void HMSimulator::triggerADCPressure()
{
	// std::cout << "Trigger ADC Pressure" << std::endl;
	// Function will take a little time in real usage
}


double HMSimulator::readADCPressure()
{
	// block 100ms for this status
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return testPressure;
}

double HMSimulator::readADCTemperature()
{
	// block 100ms for this status
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return testTemperature;
}

void HMSimulator::writeDACPump(const double value)
{
	std::uniform_real_distribution<double> randDist(-0.2,0.2);
	std::default_random_engine randEng;
	//std::cout << "Write " << value << " to DAC pump success." << std::endl;

	// simulate pumping mechanism. Pump can't set pressude directly in real world. Will increase or decrase slowly
	testPressure += value/10.0+randDist(randEng);

}

void HMSimulator::switchHeater(bool isOn)
{
	//std::cout << "Next heater position:" << isOn << "." << std::endl;

	// to simulate real world, update temperature slowly
	if (isOn) { // if switch open, increase temperature
		testTemperature += 0.3;
	}
	else { // make plant area cooler
		testTemperature -= 0.3;
	}
}


HMSimulator::~HMSimulator()
{
	// No item to destruct
}

