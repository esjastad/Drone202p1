//Erik Jastad, CS202 Program 1
//The purpose of this program is to get familiar with class derivation and initilization lists.
//This program allows the user to control up to three different kinds of drones each with their own functionality
//The purpose of this file is to define the functions that are a part of the graph class, the prototyped functions of dronadt.h are also defined here
#include "droneadt.h"


//Default constructor set data members to NULL or 0
graph::graph()
{
	vertex = NULL;
	count = 0;
}


//copy constructor for graph needed due to dynamic memory
graph::graph(const graph & source)
{
	vertex = new base*[source.count];
	count = source.count;

	for(int i = 0; i < count; ++i)
	{
		vertex[i] = source.vertex[i];
	}		
}


//deconstructor deletes all drones then self
graph::~graph()
{
	for(int i = 0; i < count; ++i)
	{
		delete vertex[i];
	}
	
	delete [] vertex;

}

//INPUTS: none
//OUTPUTS: 0 if vertex is NULL, 1 if not NULL
//This function checks if the vertex has any memory
int graph::hasdrones()
{
	if(vertex == NULL)
		return 0;
	else
		return 1;
}


//INPUTS: base pointer by ref
//OUTPUTS: 0 if the vhere are no vertices, 1 if successfully assigned to vertice
//This function is used to set mains pointer to a drone to control, this is called when te user wants to switch drones they have craeted
int graph::setdrone(base *& user)
{
	if(!vertex)
		return 0;

	if(!user)	//if user has no current vertex
	{
		user = vertex[0];
		return 1;
	}
	else if(count == 1)	
		return 0;

	for(int i = 0; i < count; ++i)	//used to find the next vertex to assign
	{
		if(user == vertex[i])
		{
			if(i == count - 1)
				user = vertex[0];
			else
				user = vertex[i+1];

			i = count + 1;
		}
	}

	return 1;
		
}


//INPUTS: base pointer by reference of the vertex to add
//OUTPUTS: returns a 1 when successful
//This function adds the incoming pointer to the vertex array, a new sized array is created and all the data is copied over.
int graph::addvertex(base *& toadd)
{
	if (!vertex)	//creates a new vertex array
	{

		vertex = new base*[1];	
		vertex[0] = toadd;
		++count;
	}
	else	//if the vertex array exists, make a new copy and add the incoming
	{
		base ** temp = vertex;
		vertex = new base*[count+1];	

		for(int i = 0; i < count; ++i)
		{
			vertex[i] = temp[i];
		}
		delete temp;	
		vertex[count] = toadd;
		++count;
	}

	return 1;
}


//INPUTS: none
//OUTPUTS:  0 for failure, 1 for success
//This function sets the next pointers in each vertex to the other members in the vertex array so that a traversal checking locations can be done
int graph::makeedgelist()
{
	if(!vertex)
		return 0;

	for (int i = 0; i < count ; ++i)
	{
		if(i == (count - 1))
			vertex[i]->setpointer(vertex[0]);
		else
			vertex[i]->setpointer(vertex[i+1]);
	}

	return 1;
}


//INPUTS: integer array and a base pointer
//OUTPUTS: 0 if the location is not valid, 1 if it is valid
//This function loops through the vertex to compare locations for valid drone movement
int graph::validlocation(int loc[], base * self)
{
	int result = 0;

	for(int i = 0;i < count; ++i)
	{
		if(vertex[i] != self)
		{
			if(vertex[i]->compareloc(loc))
			{
				result = 1;
				i = count+1;
			}		
		}

	}

	return result;
}


//INPUTS: none
//OUTPUTS: none
//This function displays text instructions to the user
void instructions()
{
	cout <<"To pass time hold the spacebar!\n\n";

	cout <<"Drone Controls:\n";
	cout << "W = Pitch Forward \t S = Pitch Backward\t\t\t F = DroneFunction1 \t G = DroneFunction2\n"
		"A = Yaw Left \t\t D = Yaw Right\t\t\t\t C = Throttle Down \t V = Throttle Up\n"
		"Q = Roll Left \t\t E = Roll Right\t\t\t\t X = Quit \t\t . = Next Drone\n\n" << endl;
}


//INPUTS: none
//OUPUTS: char
//This function is used to hide the user input that is current pressed and it allows the capture of user input without the need for the neter key
char getch()
{
	char buffer = 0;
	struct termios old = {0};

	if (tcgetattr(0, &old) < 0)
		cout << ("tcsetattr()");

	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;

	if (tcsetattr(0, TCSANOW, &old) < 0)
		cout << ("tcsetattr ICANON");

	if (read(0, &buffer, 1) < 0)
		cout << ("read()");

	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;

	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		cout << ("tcsetattr ~ICANON");

	return (buffer);
}


//INPUTS: none
//OUPUTS: none
//This function prints a bunch of new lines to the screen to clear it of text
void cls()
{
	for(int i = 0; i < 100; ++i)
		cout << endl;
}

