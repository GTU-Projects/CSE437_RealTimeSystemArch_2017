#include <iostream>
#include "ISimulator.hpp"
#include "HMSimulator.hpp"

using namespace std;


int main(int argc, char *argv[]) {

	ISimulator *simulator = new HMSimulator();

	// create pressure controller which works every 100ms(10Hz)
	PressureController pressController(*simulator, 100);

	// create temperature controller which works every 333ms(3Hz)
	TemperatureController temperatureController(*simulator, 333);

	// create operator console, which outputs the values every 500ms(2Hz)
	OperatorConsole operatorConsole(pressController, temperatureController, 500);

	return 0;
}