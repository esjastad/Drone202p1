//Erik Jastad, CS202 Program 1
//The purpose of this program is to get familiar with class derivation and initilization lists.
//This program allows the user to control up to three different kinds of drones each with their own functionality
//This file defines the functions that are part of the controller class
#include "controller.h"

//default constructor for controller class
controller::controller()
{
	frequency = 0;
	adt = NULL;
}


//constructor for controller class with initilization list
controller::controller(graph *& datastructure, const float & freq, const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling, const int & locationx, const int & locationy) : adt(datastructure), frequency(freq), base(mass, size, battery, motorsize, ceiling, locationx, locationy)
{
}


//INPUTS: none
//OUTPUTS: none
//This function is used to start the base class display function
void controller::display()
{
	base::display();
}


//INPUTS: integer array for location, base pointer with a self reference passed into a sub function call
//OUTPUTS: returns a 0 for an invalid location trying to be moved to, and 1 for a valid location
//This function is used to access the member pointer for the ADT
int controller::validlocation(int loc[], base * self)
{
	return adt->validlocation(loc, self);
}


//INPUTS: none
//OUPUTS: 0 if the frequency is 0, 1 if the frequency is not 0
//This function is used to determine if an instance has a valid frequency to receive movement input
bool controller::validfrequency()
{
	if (frequency == 0)
		return 0;
	else
		return 1;
}


