#ifndef DRIVER_H
#define DRIVER_H
#include "Car.h"

class Driver
{
  public:
    Driver (Car & sharedCar, double budget); //constructor
    void drive (int);
	void repairCar(string);
	void display();
	void fullFuel();
	
  private:
    double budget;		
    Car & sharedCar;	//reference variable for an external Car object
};
#endif