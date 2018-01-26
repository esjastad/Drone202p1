//Erik Jastad, CS202 Program 1
//The purpose of this program is to get familiar with class derivation and initilization lists.
//This program allows the user to control up to three different kinds of drones each with their own functionality
//This file implements the member functions of the clases defined in deriveddrones.h
#include "deriveddrones.h"

//default constructor 
military::military()
{
	ammo = 0;	
}

//constructor with initialization list
military::military(const int & ammo, graph *& datastructure, const float & freq, const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling, const int & locationx, const int & locationy) : ammo(ammo), controller(datastructure, freq, mass, size, battery, motorsize, ceiling, locationx, locationy)
{
}

//default constructor
toy::toy()
{
}

//constructor with initialization list
toy::toy(graph *& datastructure, const float & freq, const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling, const int & locationx, const int & locationy) : controller(datastructure, freq, mass, size, battery, motorsize, ceiling, locationx, locationy)
{
}

//default constructor
delivery::delivery()
{
	x = 0;
	y = 0;
}

//destructor with initialization list
delivery::delivery(graph *& datastructure, const float & freq, const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling, const int & locationx, const int & locationy) : x(locationx), y(locationy), controller(datastructure, freq, mass, size, battery, motorsize, ceiling, locationx, locationy)
{
}

//default constructor
restricted::restricted()
{
}

//constructor with initialization list
restricted::restricted(graph *& datastructure, const float & freq, const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling, const int & locationx, const int & locationy) : controller(datastructure, freq, mass, size, battery, motorsize, ceiling, locationx, locationy)
{
}


//INPUTS: none
//OUTPUTS: none
//This function fires the drones weapon if elevation is > 0 and ammo is greater than 0
void military::specialone()
{
	if (location[2] > 0 && ammo > 0)
	{
		cout << "Weapons Fired!" << endl;
		ammo -= 1;
	}
	else if(!location[2] > 0)
		cout << "You need a higher altitude to fire your weapons!" << endl;
	else
		cout << "Out of Ammo!" << endl;
}


//INPUTS: none
//OUTPUTS: none
//Prints the message that a image was taken
void military::specialtwo()
{
	cout << "Surveillance Image Taken!" << endl;
}


//INPUTS: none
//OUTPUTS: none
//display what drone is controlled and its ammo, calls parent display
void military::display()
{
	cout << "Current Drone: Military\t\t";
	cout << "Ammo: " << ammo << endl;
	controller::display();
}


//INPUTS: none
//OUTPUTS: none
//This function display that a flip was done
void toy::specialone()
{
	cout << "You did a flip!" << endl;
}


//INPUTS: none
//OUTPUTS: none
//This function display that a barrel roll was done
void toy::specialtwo()
{
	cout << "You did a barrel roll!" << endl;
}


//INPUTS: none
//OUTPUTS: none
//display what drone is controlled, calls parent display
void toy::display()
{
	cout << "Current Drone: Toy" << endl;
	controller::display();
}


//INPUTS: none
//OUTPUTS: none
//This function asks the user for an X Y destination to goto, A check is done to see if the location is valid
void delivery::specialone()
{
	int temp = 0;
	int prevx = location[0];	//captures previous X loc
	int prevy = location[1];	//captures previous Y loc

	cout << "Please Enter an X location to goto: ";
	cin >> temp;
	location[0] = temp;
	cout << "Please enter a Y location to goto: ";
	cin >> temp;
	location[1] = temp;
	if(translate(this))
	{
		cout << "You have arrived!" << endl << endl;
	}
	else	//reset location back to original if new location is occupied
	{
		cout << "You can not fly there because a drone or restricted area is blocking that location!\n\n" << endl;
		location[0] = prevx;
		location[1] = prevy;
	}
}


//INPUTS: none
//OUTPUTS: none
//This function returns the drone back to its original start location
void delivery::specialtwo()
{
	cout << "You have returned to your starting location!" << endl << endl;
	location[0] = x;
	location[1] = y;	
	location[2] = 0;
}


//INPUTS: none
//OUTPUTS: none
//display what drone is controlled, calls parent display
void delivery::display()
{
	cout << "Current Drone: Delivery" << endl;
	controller::display();
}

//INPUTS: none
//OUTPUTS: none
//display the area blocked by the restricted area, call parents display
void restricted::display()
{
	cout << "You are viewing a restricted area that covers " << location[0] - size << " to " << location[0] + size << " X, " << location[1] - size << " to " << location[1] + size << " Y, " << location[2] << " to " << location[2] + size << " Y." << endl;

}
