//Erik Jastad, CS202 Program 1
//The purpose of this program is to get familiar with class derivation and initilization lists.
//This program allows the user to control up to three different kinds of drones each with their own functionality
//This file identifies the controller class as a derived class of base
#include "droneadt.h"

//This class is derived from base it containes no copy constructor even though it has a pointer, this is because the pointer in this class and all classes like it are all pointing to the same ADT and a shallow copy will work as intended with a default copy constructor.
class controller : public base
{
	public:
		controller();		
		controller(graph *& datastructure, const float & freq, const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling,  const int & locationx, const int & locationy);
		void display();
		int validlocation(int loc[], base * self);
		bool validfrequency();

	protected:
		float frequency;
		graph * adt;	
};

