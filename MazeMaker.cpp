#include "MazeMaker.h"
#include "Combat.h"
#include <iostream>

using namespace std;

int steps = 0;

enum Room { Entrance, ExtraCredit, Test, Nothing, Exit };
struct Cell {
	bool Marked;
	bool North;
	bool West;
	bool South;
	bool East;
	int X;
	int Y;
	Room Contains;
};

static const int mazeSize = 8;
Player monsters[6];		//Array of Professors
Player p1;				//The actual Player
Player gary;			//Professors in the array
Player nathan;
Player wallace;
Player kesar;
Player borisova;
Player rodriguez;
Player mary;

bool CheckForBlanks(Cell maze[mazeSize][mazeSize]);
void MazeInfo(Cell maze[mazeSize][mazeSize], int X, int Y);

int main()
{
	int currPath = 1;		//Counter for creating the maze
	srand(time(NULL));

	Cell path[mazeSize * mazeSize];					//Array for creating the maze
	path[(mazeSize * mazeSize) - 1].Marked = false;	//The last Cell in the maze is not marked
	enum Direction { N, W, S, E };


	//Pick character name
	cout << "What is your character name" << endl;
	string playerName;
	cin >> playerName;
	p1.name = playerName;

	//Pick character major
	cout << "Pick a major" << endl;
	cout << "cs, is, eet" << endl;
	string playerClass;
	cin >> playerClass;
	p1.degree = selectDegree(playerClass);

	//Other Player stuff
	p1.health = 390;
	p1.strength = 50;
	p1.state = alive;

	//Making an array for the maze
	Cell maze[mazeSize][mazeSize];

	for (int i = 0; i < mazeSize; i++)
	{
		for (int j = 0; j < mazeSize; j++)
		{
			//each cell in the maze gets it's information customized
			maze[i][j].X = i;
			maze[i][j].Y = j;
			maze[i][j].Marked = false;
			maze[i][j].Contains = (Room)((rand() % 3) + 1);

			//All walls are up at first
			maze[i][j].West = true;
			maze[i][j].East = true;
			maze[i][j].North = true;
			maze[i][j].South = true;

			currPath++;
		}
	}

	//Setting Entrance and Exit 
	
	maze[0][0].Contains = Entrance;
	maze[mazeSize - 1][mazeSize - 1].Contains = Exit;

	//Resetting the counter for reuse
	currPath = 0;

	//Carving the maze
	Cell current = maze[0][0];
	bool full = false;

	while (!full)	//while the maze is not full of cells
	{
		maze[current.X][current.Y].Marked = true;

		//choose a random direction
		Direction a = (Direction)(rand() % 4);

		//check for outer walls and already visited rooms
		if ((current.Y == 0 || maze[current.X][current.Y - 1].Marked) &&      //North is blocked
			(current.Y == mazeSize - 1 || maze[current.X][current.Y + 1].Marked) &&      //South is blocked
			(current.X == 0 || maze[current.X - 1][current.Y].Marked) &&      //West is blocked
			(current.X == mazeSize - 1 || maze[current.X + 1][current.Y].Marked))        //East is blocked
		{
			if (!CheckForBlanks(maze))	//If the cell is surrounded, check if the entire array is full
				full = true;
			
			else						// else, retreat and try again
				current = path[currPath - 1];
				currPath--;
		}

		else
		{
			//Based on Random Direction chosen earlier
			//Carving North
			if (a == N && current.Y != 0 && !maze[current.X][current.Y - 1].Marked)
			{
				maze[current.X][current.Y].North = false;
				maze[current.X][current.Y - 1].South = false;
				path[currPath] = current;
				currPath++;
				current = maze[current.X][current.Y - 1];
			}

			//Carving South
			else if (a == S && current.Y != mazeSize - 1 && !maze[current.X][current.Y + 1].Marked)
			{
				maze[current.X][current.Y].South = false;
				maze[current.X][current.Y + 1].North = false;
				path[currPath] = current;
				currPath++;
				current = maze[current.X][current.Y + 1];
			}

			//Carving West
			else if (a == W && current.X != 0 && !maze[current.X - 1][current.Y].Marked)
			{
				maze[current.X][current.Y].West = false;
				maze[current.X - 1][current.Y].East = false;
				path[currPath] = current;
				currPath++;
				current = maze[current.X - 1][current.Y];
			}

			//Carving East
			else if (a == E && current.X != mazeSize - 1 && !maze[current.X + 1][current.Y].Marked)
			{
				maze[current.X][current.Y].East = false;
				maze[current.X + 1][current.Y].West = false;
				path[currPath] = current;
				currPath++;
				current = maze[current.X + 1][current.Y];
			}

			else	//Try the 'next' direction
				a = (Direction)((int)a + 1);
			
		}
	}

	//Make monster stats
	gary.state = alive;
	gary.name = "Gary Cantrell";
	gary.health = 100;
	gary.strength = 10;
	gary.degree = cs;

	nathan.state = alive;
	nathan.name = "Nathan Barker";
	nathan.health = 150;
	nathan.strength = 20;
	nathan.degree = cs;

	wallace.state = alive;
	wallace.name = "Gary Wallace";
	wallace.health = 100;
	wallace.strength = 10;
	wallace.degree = is;

	kesar.state = alive;
	kesar.name = "Shalini Kesar";
	kesar.health = 150;
	kesar.strength = 20;
	kesar.degree = is;

	borisova.state = alive;
	borisova.name = "Isabella Borisova";
	borisova.health = 100;
	borisova.strength = 10;
	borisova.degree = eet;

	rodriguez.state = alive;
	rodriguez.name = "Oscar Rodriguez";
	rodriguez.health = 150;
	rodriguez.strength = 20;
	rodriguez.degree = eet;

	mary.state = alive;
	mary.name = "Mary Gillins";
	mary.health = 500;
	mary.strength = 20;
	if (p1.degree == cs)
		mary.degree = is;
	else if (p1.degree == eet)
		mary.degree == cs;
	else if (p1.degree == is)
		mary.degree == eet; 

	
	//Start the game!!!
	MazeInfo(maze, 0, 0);
}

bool CheckForBlanks(Cell maze[mazeSize][mazeSize])
{
	//checks an array of cells for any that are still not marked
	for (int j = 0; j < mazeSize; j++)
	{
		for (int i = 0; i < mazeSize; i++)
		{
			if (!maze[i][j].Marked)
				return true;
		}
	}

	return false;
}

void MazeInfo(Cell maze[mazeSize][mazeSize], int X, int Y)
{
	char bar = '_';		//This gave us so much trouble
    bool won = false;	//Will be usefull later
	
	for (int s = 0; s < (mazeSize); s++)	//Prints North wall
		cout << ' ' << bar;
	
	cout << endl;
    
	for (int j = 0; j < mazeSize; j++)
	{
		for (int i = 0; i < mazeSize; i++)
		{
		    if (i == X && j == Y)	//Prints character in their location
		    {	
		        if (maze[i][j].West)
				    cout << "|";
			    else
				    cout << " ";
				    
				if (maze[i][j].South)
				    cout << "A";
			    else
				    cout << "A";
		    }
		    
		    else					//Prints South and West walls
		    {
        		if (maze[i][j].West)
        			cout << "|";
        		else
        			cout << " ";
        
        		if (maze[i][j].South)
        			cout << bar;
        		else
        			cout << " ";
		    }
		}
		cout << "|" << endl;		//Prints East Wall
	}


	cout << endl;

	while (!won)
	{
		//Loop for moving around the maze
		steps++;
		
		//Print Character Info
		if (p1.health > 400)
			p1.health = 400;

		cout << "GPA: " << p1.health / 100 << endl;	//
		cout << endl;

		//Print info about the room
		if (maze[X][Y].Contains == Nothing)
			cout << "The Room is Empty..." << endl << endl;

		if (maze[X][Y].Contains == ExtraCredit)		//Extra Credit give you back points!
		{
			cout << "There's a desk in the center of the Room!" << endl;
			cout << "You take a moment to work on an extra credit assignment." << endl;
			double GPAback = (rand() % 40) + 1;
			p1.strength++;
			p1.health += GPAback;
			cout << "Your GPA went up! " << GPAback << " Extra Points!" << endl;
		}

		if (maze[X][Y].Contains == Test)		//Tests are battles with the professors (see combat)
		{
			int prehealth = p1.health;
			cout << "Pop Quiz!" << endl;
			cin;
			int rnd;
			rnd = (rand() % 5) +1; 
			if (rnd == 1) {
				p1.health = combat(p1, gary);
			}
			else if (rnd == 2) {
				p1.health = combat(p1, nathan);
			}
			else if (rnd == 3) {
				p1.health = combat(p1, wallace); 
			}
			else if (rnd == 4) {
				p1.health = combat(p1, kesar);
			}
			else if (rnd == 5) {
				p1.health = combat(p1, borisova);
			}
			else if (rnd == 6) {
				p1.health = combat(p1, rodriguez); 
			}
			
			if (p1.state == dead) //if you die in combat, it's game over.
			{
				cout << "You have died" << endl;
				exit(0);
			}
			
			else
				cout << "You lost " << prehealth - p1.health << " points." << endl;
		}


		if (maze[X][Y].Contains == Exit)		//When you reach the Exit, you face the Final Boss!
		{
			cout << "FINAL BOSS!" << endl;
			p1.health = combat(p1, mary); 
			if (p1.state == dead) //if you die in combat, it's game over.
			{
				cout << "You have died" << endl;
				exit(0);
			}
			
			else
			{
				won = true;
				cout << "You Won!" << endl;
				cout << "Your final GPA is " << p1.health / 100 << endl;
				cout << "You traveled " << steps << " steps." << endl;
				cout << "Congratulations on completing your degree." << endl;
				exit(0);
			}
		}

		//Printing the Directions that are not blocked off
		if (!maze[X][Y].North)
			cout << "There is a door to the North(w)" << endl;

		if (!maze[X][Y].West)
			cout << "There is a door to the West(a)" << endl;

		if (!maze[X][Y].South)
			cout << "There is a door to the South(s)" << endl;

		if (!maze[X][Y].East)
			cout << "There is a door to the East(d)" << endl;

		//Getting a direction from the player
		//if a heading is not open, you hit a wall
		//if you enter nonsense, you get nothing.
		char heading;
		cin >> heading;

		if (heading == 'w' && !maze[X][Y].North)
			MazeInfo(maze, X, Y - 1);

		if (heading == 'w' && maze[X][Y].North)
			cout << "There's a Wall there..." << endl;

		if (heading == 'a' && !maze[X][Y].West)
			MazeInfo(maze, X - 1, Y);

		if (heading == 'a' && maze[X][Y].West)
			cout << "There's a Wall there..." << endl;

		if (heading == 's' && !maze[X][Y].South)
			MazeInfo(maze, X, Y + 1);

		if (heading == 's' && maze[X][Y].South)
			cout << "There's a Wall there..." << endl;

		if (heading == 'd' && !maze[X][Y].East)
			MazeInfo(maze, X + 1, Y);

		if (heading == 'd' && maze[X][Y].East)
			cout << "There's a Wall there..." << endl;

		else
			cout << "I don't Understand..." << endl;
	}
}

