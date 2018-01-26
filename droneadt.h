//Erik Jastad, CS202 Program 1
//The purpose of this program is to get familiar with class derivation and initilization lists.
//This program allows the user to control up to three different kinds of drones each with their own functionality
//Thi file holds the graph ADT class and the prototypes to functions used by a possible user appplication
#include "basedrone.h"
 
void instructions();	//prototype for instructions
char getch();		//prototype for capturing input
void cls();		//prototype for clear screen


//This class is the ADT graph and edgelist
class graph
{
	public:
		graph();
		graph(const graph & source);
		~graph();
		int addvertex(base *& toadd);
		int makeedgelist();
		int validlocation(int loc[], base * self);	
		int setdrone(base *& user);
		int hasdrones();

	private:
		base ** vertex;	//pointer to pointer for making array of pointers
		int count;	//keeps trck of vertex array size
};


