//Erik Jastad, CS202 Program 1
//The purpose of this program is to get familiar with class derivation and initilization lists.
//This program allows the user to control up to three different kinds of drones each with their own functionality
//This file holds the base class definition, libraries and global constants.
#include <iostream>
#include <cctype>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <math.h> 

using namespace std;

const float drain = 0.0001; //This constant is used to drain drone batteries
const double pi = 3.1415926535897; //this is the value of pi, used when computing translation


//This is the base class which all classes in this program are derived from, except the graph class.  This class uses dynamic binding so that you can swap drones during run time and access their individual functionalities.
class base
{
	public:
		base();	
		base(const base & source);
		base(const int & mass, const int & size, const float & battery, const int & motorsize, const int & ceiling, const int & locationx, const int & locationy);
		virtual ~base();
		virtual void display();
		int translate(base * self);
		int rotate(const int & one, const int & two, const int & three);
		void adjustrotation(int & value);
		int usethrottle(const int & toadd);
		void usebattery(const float & toadd);
		void setpointer(base *& drone);
		virtual int validlocation(int loc[], base * self);
		virtual	void specialone();
		virtual void specialtwo();
		int compareloc(int loc[]);
		virtual bool validfrequency();

	protected:
		int mass; //not implemented in a significant way but was inteneded to be
		int size;	//used to determine if too close to drone or restricted area
		float battery; //max battery power, used to give % value
		float cbattery; //current battery power
		int motorsize; //not implemented but was inteded to be 
		float throttle; //How fast your rotors are spiniing to make lift
		int ceiling; //how high the drone can fly
		int * rotation; //current rotation
		int * location; //current location
		base * next; //used with adjacency list
};

