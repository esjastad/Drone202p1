//Erik Jastad, CS202 Program 1
//The purpose of this program is to get familiar with class derivation and initilization lists.
//This program allows the user to control up to three different kinds of drones each with their own functionality
//This file holds all the derived drones classes including the restricted area
#include "controller.h"


//This class is derived from the controller class
class military : public controller
{
	public:
		military();
		military(const int & ammo, graph *& datastructure, const float & freq, const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling, const int & locationx, const int & locationy);
		void specialone();
		void specialtwo();
		void display();

	protected:
		int ammo;	//ammo quantity

};


//This class is derived from the controller class
class toy : public controller
{
	public:
		toy();
		toy(graph *& datastructure, const float & freq, const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling, const int & locationx, const int & locationy);
		void specialone();
		void specialtwo();
		void display();

};

//This class is derived from the controller class
class delivery : public controller
{
	public:
		delivery();
		delivery(graph *& datastructure, const float & freq, const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling, const int & locationx, const int & locationy);
		void specialone();
		void specialtwo();
		void display();

	protected:
		int x;	//stores the initial starting x location
		int y;  //stores the initial starting y location	
};


//This class is derived from the controller class
class restricted : public controller
{
	public:
		restricted();
		restricted(graph *& datastructure, const float & freq, const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling, const int & locationx, const int & locationy);
		void display();
};
