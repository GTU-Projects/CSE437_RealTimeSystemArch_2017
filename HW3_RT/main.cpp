#include <iostream>
#include "CONSTANTS.h"
#include "PressureController.hpp"
#include "TemperatureController.hpp"
#include "OperatorConsole.hpp"
#include "ISimulator.hpp"
#include "HMSimulator.hpp"

using namespace std;


int main(int argc, char *argv[]) {

	//NOTE: Each module reads work interval from CONSTANT.H file


	ISimulator *mySimulator = new HMSimulator();

	// create operator console, which outputs the values every 500ms(2Hz)
	OperatorConsole * operatorConsole = new OperatorConsole();

	// create pressure controller which works every 100ms(10Hz)
	PressureController pressController(*mySimulator,*operatorConsole);

	// create temperature controller which works every 333ms(3Hz)
	TemperatureController temperatureController(*mySimulator,*operatorConsole);

	
	while (true);

	return 0;
}