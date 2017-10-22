# HW2 - Implementing Plant system

HASAN MEN - 131044009

## HOW TO USE - Requirements:
1. Create your Simulator which implements ISimulator
2. Construct PressureController and TemperatureController with this simulator and their frequency
	PressureController(simulator,frequency)
	TemperatureController(simulator,frequency)
3. Construct OperatorConsole to see results on console. Don't forget to give a pressure controller, temperature controller and work interval to operator console.
4. When you construct OperatorConsole, it will print values to console.
5. Please check main.cpp to see calling orders

### PressureController
1. You can set A,B values which exist in PressureController.hpp to set pressure sensitivity.

### TemperatureController
1. You can set C(min),D(max) values which exist in TemperatureController.hpp to set min, max temperature.

### Test scenarious
1. Temperature: On the start-up temperature is 0. System will check this value and set on state to heater.
   Then temperature will be increased until reach min value of temperature. After that my system will take value between min,max values.

2. Pressure: Pressure is 0 on the start-up. System will calculate new pressure value to save value in range. An simulator will update this value slowly.
