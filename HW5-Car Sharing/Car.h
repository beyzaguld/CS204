#ifndef CAR_H
#define CAR_H
#include <iostream>
#include <string>
using namespace std;

class Car
{
  public:
    Car (double, double, int); //constructor
    void display();        //prints a message
	void incrementTotalDistance(int);
	void decreaseFuelLevel(double);
	void increaseInsuranceFee(string);
	void fullFuelLevel();
	double getFuelLevel() const;
	double getInýtFuelLevel() const;
  private:
    double fuelLevel;
    double insuranceFee;
	int totalDistance;
	double newFuelLevel;
};
#endif