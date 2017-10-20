# HW2 - Implementing Plant system

HASAN MEN - 131044009

## HOW TO USE:
1. Create your Simulator which implements ISimulator
2. Construct PressureController and TemperatureController with this simulator and their frequency
	PressureController(simulator,frequency)
	TemperatureController(simulator,frequency)
3. Construct OperatorConsole to see results on console. Don't forget to give a pressure controller, temperature controller and work interval to operator console.
4. When you construct OperatorConsole, it will print values to console.
5. Please check main.cpp to see calling orders


### PressureController
1. You can set A,B values which exist in PressureController.hpp to set pressure sensitivity.

### Temperature
1. You can set C(min),D(max) values which exist in TemperatureController.hpp to set min, max temperature.
