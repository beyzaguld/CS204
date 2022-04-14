#include <iostream>
#include <string>
#include "Driver.h"
using namespace std;

//constructor
Driver::Driver(Car & sharedCar, double budget)
 :  sharedCar(sharedCar),
	budget(budget)
{ }

//take kilometer that is driven and increment total distance of car, decrease fuel level.
void Driver::drive(int km) {
	sharedCar.incrementTotalDistance(km);
	sharedCar.decreaseFuelLevel(double(km)/4);
}

//according to accident type, decrease budget and increase insurance fee of shared car.
void Driver::repairCar(string accidentType) {
	int loss;
	if (accidentType == "SMALL") {
		loss = 50;
		budget -= loss;
	}
	else if (accidentType == "MEDIUM") {
		loss = 150;
		budget -= loss;
	}
	else if (accidentType == "LARGE") {
		loss = 300;
		budget -= loss;
	}
	cout << loss << "$ is reduced from the driver's budget because of the " << accidentType << " accident" << endl;
	sharedCar.increaseInsuranceFee(accidentType);
}

//display budget
void Driver::display() {
	cout << endl << "Driver Budget: " << budget << endl;
}

//full fuel level and according to used fuel, decrease budget
void Driver::fullFuel() {	
	double usedFuel = sharedCar.getInýtFuelLevel() - sharedCar.getFuelLevel();
	budget -= usedFuel;
	sharedCar.fullFuelLevel();
	cout << endl << "Fuel is full" << endl;
}