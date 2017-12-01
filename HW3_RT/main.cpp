#include <iostream>
#include "PressureController.hpp"
#include "TemperatureController.hpp"
#include "OperatorConsole.hpp"
#include "ISimulator.hpp"
#include "HMSimulator.hpp"

using namespace std;


int main(int argc, char *argv[]) {

	ISimulator *mySimulator = new HMSimulator();


	OperatorConsole * operatorConsole = new OperatorConsole(500);

	// create pressure controller which works every 100ms(10Hz)
	PressureController pressController(*mySimulator,*operatorConsole, 100);

	// create temperature controller which works every 333ms(3Hz)
	TemperatureController temperatureController(*mySimulator,*operatorConsole,333);

	// create operator console, which outputs the values every 500ms(2Hz)
	

	while (true);

	return 0;
}