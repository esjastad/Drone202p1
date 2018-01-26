//Erik Jastad, CS202 Program 1
//The purpose of this program is to get familiar with class derivation and initilization lists.
//This program allows the user to control up to three different kinds of drones each with their own functionality
//This file is a user application that allows interfacing and testing with the ADT and the heirarchy of classes


#include "deriveddrones.h"

int main()
{
	cls();	//clear screen function 

	int input = 0;
	int x = 0;
	int y = 0;
	int size = 0;

	graph * adt = new graph;	//pointer to ADT
	base * currentdrone = NULL;	//pointer to drones

	while(input != 7)	//runs until the user selects to quit
	{
		cout << "\nWelcome to the drone simulator please make a selection from the menu below."
		     << "\n\n\n1) Add a military drone.\t\t(Special Functions: Fire weapon, Take picture)"
		     << "\n2) Add a delivery drone.\t\t(Special Functions: Goto assigned destintion, Return to original starting location)"
		     << "\n3) Add a toy drone.\t\t\t(Special Functions: Flip, Barrel roll)"
		     << "\n4) Add a restricted area."
		     << "\n5) Play Simulation."
		     << "\n\n6) Clear all drones and restricted areas."
		     << "\n7) Quit the simulator."
		     << "\n\nPlease enter a number choice: ";

		cin >> input;

		if(input == 1)
		{
			cout << "\nPlease enter an integer for the X coordinate for this drone: ";
			cin >> x;
			cin.ignore(100,'\n');
			
			cout << "\nPlease enter an integer for the Y coordinate for this drone: ";
			cin >> y;
			cin.ignore(100,'\n');
			
			cls();
			currentdrone = new military(500,adt,1,3,3,150,3,7500,x,y);	//create a miitary drone

			if(currentdrone->translate(currentdrone))	//check if indicated location for drone is occupied already
			{
				adt->addvertex(currentdrone);	//add vertex if location is valid
				currentdrone = NULL;	
				cout << "\nSuccessfully Added!\n\n";
			}
			else
			{
				cout << "\nThat location is blocked by a restricted area or drone! please try again!" << endl;
				delete currentdrone;	//delete drone if location was invalid
				currentdrone = NULL;
			}

		}

		if(input == 2)
		{

			cout << "\nPlease enter an integer for the X coordinate for this drone: ";
			cin >> x;
			cin.ignore(100,'\n');
			
			cout << "\nPlease enter an integer for the Y coordinate for this drone: ";
			cin >> y;
			cin.ignore(100,'\n');
			
			cls();
			currentdrone = new delivery(adt,2,2,2,250,2,500,x,y);

			if(currentdrone->translate(currentdrone))
			{
				adt->addvertex(currentdrone);
				currentdrone = NULL;	
				cout << "\nSuccessfully Added!\n\n";
			}
			else
			{
				cout << "\nThat location is blocked by a restricted area or drone! please try again!" << endl;
				delete currentdrone;
				currentdrone = NULL;
			}
		}

		if(input == 3)
		{
			cout << "\nPlease enter an integer for the X coordinate for this drone: ";
			cin >> x;
			cin.ignore(100,'\n');
			
			cout << "\nPlease enter an integer for the Y coordinate for this drone: ";
			cin >> y;
			cin.ignore(100,'\n');
			
			cls();
			currentdrone = new toy(adt,3,1,1,50,1,500,x,y);

			if(currentdrone->translate(currentdrone))
			{
				adt->addvertex(currentdrone);
				currentdrone = NULL;	
				cout << "\nSuccessfully Added!\n\n";
			}
			else
			{
				cout << "\nThat location is blocked by a restricted area or drone! please try again!" << endl;
				delete currentdrone;
				currentdrone = NULL;
			}
		}

		if(input == 4)
		{
			cout << "\nPlease enter an integer for the X coordinate for this area: ";
			cin >> x;
			cin.ignore(100,'\n');
			
			cout << "\nPlease enter an integer for the Y coordinate for this area: ";
			cin >> y;
			cin.ignore(100,'\n');

			cout << "\nPlease enter the radius of this restricted area: ";	//Allows the user to create a restricted area and specify the radius to block
			cin >> size;
			cin.ignore(100,'\n');

			cls();
			currentdrone = new restricted(adt,0,0,size,0,0,0,x,y);
			if(currentdrone->translate(currentdrone))
			{
				adt->addvertex(currentdrone);
				currentdrone = NULL;	
				cout << "\nSuccessfully Added!\n\n";
			}
			else
			{
				cout << "\nThat location is blocked by a restricted area or drone! please try again!" << endl;
				delete currentdrone;
				currentdrone = NULL;
			}
				
		}
				

		if(input == 6)
		{
			cls();
			delete adt;		//deletes the current graph
			adt = new graph;
			cout << endl << "All drones and restricted areas have been removed!" << endl << endl;
		}

		if(input == 5)
		{
			if(adt->hasdrones())	
			{
				adt->makeedgelist();	//creates edgelist
				adt->setdrone(currentdrone);	//sets the first specified area to control
				cls();

				cout <<"To Pitch or Yaw you must have a Z value greater than 0\n"			//user instructions
				     <<"Z elevation will increase when the throttle is at or above 55%\n"
				     <<"\nYaw and pitch are in degrees, Yaw: 0 is north, 90 is east, -90 is west, 180 is south\n"
			             <<"Pitch will make you move forward, or backward in the yaw direction, as you increase/decrease pitch you may lose altitude since you are losing upward thrust.\n"
				     <<"\n\nI reccommend not pitching more than 6-7 degrees\n\n\n\n\n\n\n\n";


				while(input != 120)	//when the user presses X quit
				{
					if(!currentdrone->translate(currentdrone))
						cout << "\nCan't Fly here, another drone or a restricted area is in the way\n";

					currentdrone->usebattery(drain);
					instructions();		//prints instructions
					currentdrone->display();	//call display function to display specifics about who is being controlled

					if(input == 119)	//All if statements are checking for ASCII value of key pressed
					{
						if(currentdrone->validfrequency())
						{
							currentdrone->rotate(0,1,0);
							cls();
							instructions();
							currentdrone->display();
							cout << "Pitch Forward" << endl;
						}
						else
							cout << "You are not a drone! You can not move! Press . to switch" << endl;
					}
					else if(input == 115)
					{
						if(currentdrone->validfrequency())
						{
							currentdrone->rotate(0,-1,0);
							cls();
							instructions();
							currentdrone->display();
							cout << "Pitch Backward" << endl;
						}
						else
							cout << "You are not a drone! You can not move! Press . to switch" << endl;
					}
					else if(input == 100)
					{
						if(currentdrone->validfrequency())
						{
							currentdrone->rotate(0,0,-1);
							cls();
							instructions();
							currentdrone->display();
							cout << "Yaw Right" << endl;
						}
						else
							cout << "You are not a drone! You can not move! Press . to switch" << endl;
					}
					else if(input == 97)
					{
						if(currentdrone->validfrequency())
						{
							currentdrone->rotate(0,0,1);
							cls();
							instructions();
							currentdrone->display();
							cout << "Yaw Left" << endl;
						}
						else
							cout << "You are not a drone! You can not move! Press . to switch" << endl;
					}
					else if(input == 101)
					{
						if(currentdrone->validfrequency())
						{
							currentdrone->rotate(0,0,0);
							cls();
							instructions();
							currentdrone->display();
							cout << "Roll Right is Disabled did not finish implementation" << endl;
						}
						else
							cout << "You are not a drone! You can not move! Press . to switch" << endl;
					}
					else if(input == 113)
					{
						if(currentdrone->validfrequency())
						{
							currentdrone->rotate(0,0,0);
							cls();
							instructions();
							currentdrone->display();
							cout << "Roll Left is Disabled did not finish implementation" << endl;
						}
						else
							cout << "You are not a drone! You can not move! Press . to switch" << endl;
					}
					else if(input == 46)
					{
						adt->setdrone(currentdrone);
						cls();
						instructions();
						currentdrone->display();
						cout << "Switch Drones" << endl;
					}
					else if(input == 99)
					{
						if(currentdrone->validfrequency())
						{
							currentdrone->usethrottle(-1);
							cls();
							instructions();
							currentdrone->display();
							cout << "Throttle Down" << endl;
						}
						else
							cout << "You are not a drone! You can not move! Press . to switch" << endl;
					}
					else if(input == 118)
					{
						if(currentdrone->validfrequency())
						{
							currentdrone->usethrottle(1);
							cls();
							instructions();
							currentdrone->display();
							cout << "Throttle Up" << endl;
						}
						else
							cout << "You are not a drone! You can not move! Press . to switch" << endl;

					}
					else if(input == 102)
					{
						cls();
						currentdrone->specialone();
						instructions();
						currentdrone->display();
					}
					else if(input == 103)
					{
						cls();
						currentdrone->specialtwo();
						instructions();
						currentdrone->display();
					}	
					
					input = getch();	//captures what the user presses without the need for the enter key
					cls();
				}
			}
			else
			{
				cls();	//error message if trying to simulate with no drones or area to control
				cout << "You do not have any drones or restricted areas to simulate! Try adding one by selecting option 1,2,3 or 4." << endl << endl;
			}

			currentdrone = NULL;
		}

	}

	cls();
	cout << "Goodbye!" << endl;

	return 0;

}
