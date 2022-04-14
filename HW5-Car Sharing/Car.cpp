#include "Car.h"



//constructor
Car::Car(double fuelLevel, double insuranceFee, int totalDistance)
 :	fuelLevel(fuelLevel),
	insuranceFee(insuranceFee),
	totalDistance(totalDistance)
{ 
	newFuelLevel = fuelLevel;
}



//Message printed
void Car::display()
{   
	cout << "Fuel Level: " << newFuelLevel << endl;
	cout << "Insurance Fee: " << insuranceFee << endl;
	cout << "Total distance that the car has travelled: " << totalDistance << endl;
}

//take kilometer and increment total distance of car
void Car::incrementTotalDistance(int km) {
	totalDistance += km;
}

//accoring to fuel used, decrease fuel level
void Car::decreaseFuelLevel(double fuel) {
	newFuelLevel -= fuel;
}

//according to accident type, increase insurance fee of the car
void Car::increaseInsuranceFee(string accidentType) {
	if (accidentType == "SMALL") {
		insuranceFee = insuranceFee*(1.05);
	}
	else if (accidentType == "MEDIUM") {
		insuranceFee = insuranceFee*(1.1);

	}
	else if (accidentType == "LARGE") {
		insuranceFee = insuranceFee*(1.2);
	}
	cout << "Yearly insurance fee is increased to " << insuranceFee << " because of the " << accidentType << " accident" << endl;

}

//full fuel level (equalize it to initial fuel level value)
void Car::fullFuelLevel() {
	newFuelLevel = fuelLevel;
}

// get current fuel level
double Car::getFuelLevel() const {
	return newFuelLevel;
}

// get initial fuel level
double Car::getInýtFuelLevel() const {
	return fuelLevel;
}