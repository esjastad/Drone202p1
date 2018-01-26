//Erik Jastad, CS202 Program 1
//The purpose of this program is to get familiar with class derivation and initilization lists.
//This program allows the user to control up to three different kinds of drones each with their own functionality
//This file implements the functions that are prototyped in the base class header file.
#include "basedrone.h"

//default constructor initializes all data members to 0
base::base()
{
	mass = 0;
	size = 0;
	battery = 0;
	cbattery = 0;
	motorsize = 0;
	throttle = 0;
	ceiling = 0;
	
	rotation = new int[3];	//array of 3 integers for Roll, Pitch, Yaw
	location = new int[3];  //array of 3 integers for x,y,z location
	
	for(int i = 0; i < 3; ++i)
	{
		rotation[i]=0;
		location[i]=0;
	}
}


//copy constructor, copies all data members from source
base::base(const base & source)
{
	mass = source.mass;
	size = source.size;
	battery = source.battery;
	motorsize = source.motorsize;
	throttle = source.throttle;
	ceiling = source.ceiling;
	cbattery = source.cbattery;

	rotation = new int[3];
	location = new int[3];

	for(int i = 0; i < 3; ++i)
	{
		rotation[i]= source.rotation[i];
		location[i]= source.location[i];
	}
	
}

//base class constructor uses an initilization list to set some members and the rest are set in the body of code
base::base(const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling, const int & locationx, const int & locationy) : mass(mass), size(size),battery(battery),cbattery(battery),motorsize(motorsize),throttle(0),ceiling(ceiling)
{
	rotation = new int[3];
	location = new int[3];

	for(int i = 0; i < 3; ++i)
	{
		rotation[i]= 0; 
		location[i]= 0; 
	}

	location[0] = location[0] + locationx;
	location[1] = location[1] + locationy;

}


//default deconstructor for base class
base::~base()
{
	delete [] rotation;
	delete [] location;
}


//The following functions are virtual functions with no code for the base class they are used to access child functions
void base::specialone() {}
void base::specialtwo() {}
int base::validlocation(int loc[], base * self) {}
bool base::validfrequency(){}


//INPUTS: integer array containining a location
//OUTPUTS: a 0 if the location is already occupied by something, 1 if the location is open
//This function compares the passed in location with the location of the base object to determine if a drone can move there.
int base::compareloc(int loc[])
{
	if(loc[0] >= (location[0] - size) && loc[0] <= (location[0] + size)) //checks X coordinate using size to add additional area occupied
	{
		if(loc[1] >= (location[1] - size) && loc[1] <= (location[1] + size))	//checks Y coord
		{
			if(loc[2] >= (location[2] - size) && loc[2] <= (location[1] + size))	//checks Z coord
				return 1;
		}
	}

	return 0;
}

//INPUTS: base drone pointer by reference
//OUTPUTS: none
//This function is used to set the next pointer data member in base and is used in building the adjaceny list
void base::setpointer(base *& drone)
{
	next = drone;	
}


//INPUTS: none
//OUTPUTS: none
//This function is used to display the drones current data member values so the user can navigate the virtual space with text feedback
void base::display()
{
	cout.precision(4);
	cout << "Throttle: " << throttle << "%\t\t" << "Battery: " << (cbattery/battery)*100 << "%" << endl << endl;
	cout << "Location:" << endl;
	cout << "X:" << location[0] << " Y:" << location[1] << " Z:" << location[2] << endl << endl;
	cout << "Rotation:" << endl;
	cout << "R:" << rotation[0] << " P:" << rotation[1] << " Y:" << rotation[2] << endl << endl;
}


//INPUTS: A base pointer of itself
//OUPUTS: 0 for a failure to move because the location to move to is invalid, or 1 if the move was successful
//This function uses the drones current data member settings to adjust its X,Y,Z location values, first a check is made if the location is occupied, if the location is valid to move to the X,Y,Z location values will be adjusted based off the throttle and yaw and pitch.
int base::translate(base * self)
{
	if(validlocation(location, self))
	{
		location[0] -= (sin(rotation[2] * (pi/180)) * sin(rotation[1] * (pi/180))) * (throttle * 0.2);

		location[1] -= (cos(rotation[2] * (pi/180)) * sin(rotation[1] * (pi/180))) * (throttle * 0.20);

		location[2] -= (cos(rotation[1] * (pi/180)) * (throttle * 0.20)) - 10;
		return 0;

	}

	if (cbattery == 0) //no battery sets throttle to 0
		throttle = 0;

	location[0] += (sin(rotation[2] * (pi/180)) * sin(rotation[1] * (pi/180))) * (throttle * 0.2);

	location[1] += (cos(rotation[2] * (pi/180)) * sin(rotation[1] * (pi/180))) * (throttle * 0.20);

	location[2] += (cos(rotation[1] * (pi/180)) * (throttle * 0.20)) - 10;


	if(location[2] > ceiling) //if trying to fly higher than ceiling limit
		location[2] = ceiling;

	if(location[2] < 0) //if u hit the ground reset rotations 
	{
		location[2] = 0;
		rotation[0] = 0;
		rotation[1] = 0;
	}

	return 1;
}


//INPUTS: an integer value to increase or decrease the current throttle
//OUTPUTS: 1 for successful update 0 if failed
//This function uses some battery power and check if the throttle can be adjusted up or down and makes the adjustment if applicable
int base::usethrottle(const int & toadd)
{
	usebattery(drain * throttle);

	if(cbattery > 0 && (throttle + toadd <= 100 && throttle + toadd >= 0))
		throttle += toadd;
	else
		return 0;

	return 1;
}


//INPUTS: a float number 
//OUTPUTS: none
//This function reduces the currenty batter % by the passed in value
void base::usebattery(const float & toadd)
{
	if(cbattery > 0)
	{
		cbattery -= toadd;

		if(cbattery < 0)
			cbattery = 0;
	}

	return;	
}


//INPUTS:  three integers, one for each rotation, roll, pitch, yaw
//OUTPUTS: returns a 1 if a successful rotation update was made, otherwise returns a 0 for failed rotation
//This function updates the drones rotation and adding the passed in value to the current rotation.  A check is made to see if the battery is not 0 and if we are in the air.
int base::rotate(const int & one, const int & two, const int & three)
{
	usebattery(drain * throttle);

	if(cbattery > 0 && location[2] >= 1)
	{
		rotation[0] += one;
		rotation[1] += two;
		rotation[2] += three;
	
		for(int i = 0; i < 3; ++i)
			adjustrotation(rotation[i]);	
		
		return 1;
	}

	else
		 return 0;

}

//INPUTS: an integer
//OUTPUTS: none
//This function is used to check if a rotation value has gone beyond 180 degrees and makes the adjustment to a negative or positive as needed per rotation
void base::adjustrotation(int & value)
{
		if(value > 180)
			value = -179;
		if(value < -180)
			value = 179;
}
