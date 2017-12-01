CXX=g++
CXXFLAGS=-std=c++11

all: clean PressureCon TemperatureCon OperatorCon HMSimulator Main GenerateExec


clean:
	rm -rf *.o main

Main:
	${CXX} ${CXXFLAGS} main.cpp -c

HMSimulator:
	${CXX} ${CXXFLAGS} HMSimulator.cpp -c

TemperatureCon:
	${CXX} ${CXXFLAGS} TemperatureController.cpp -c

OperatorCon:
	${CXX} ${CXXFLAGS} OperatorConsole.cpp -c

PressureCon:
	${CXX} ${CXXFLAGS} PressureController.cpp -c

GenerateExec:
	${CXX} main.o OperatorConsole.o PressureController.o TemperatureController.o HMSimulator.o -lpthread -lrt -o  main
