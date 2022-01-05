#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <conio.h>

using namespace std;

int steps = 0;
int numBattles = 0;
bool won = false;

enum status { alive, dead};
enum program { cs, eet, is};
enum Room { Entrance, ExtraCredit, Test, Nothing, Exit};

struct Player {		//The official 'Player' struct
	status state;
	string name;
	double health;
	int strength;
	program degree;
};

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

Player p1;				//The actual Player
Player gary;			//Professors
Player nathan;
Player wallace;
Player kesar;
Player borisova;
Player rodriguez;
Player mary;

status gradeCheck(Player p) {	//checks if player's alive or dead
	if (p.health > 0) {
		return alive;
	}
	else {
		return dead;
	}
}

int popQuiz(Player character, Player monster) {	//popQuiz between given 'Players'
	numBattles++;
	double damageMod;

	while (character.state == alive && monster.state == alive) {
		int attack = 0;
		//degree advantage check 

		//Player is neutral
		if (character.degree == monster.degree) {
			damageMod = 1;
		}//Player is greater
		else if (character.degree == cs && monster.degree == eet) {
			damageMod = 2;
		}
		else if (character.degree == eet && monster.degree == is) {
			damageMod = 2;
		}
		else if (character.degree == is && monster.degree == cs) {
			damageMod = 2;
		}//player is weak
		else {
			damageMod = 0.5;
		}

		//Monster hits player
		attack = rand() % monster.strength;
		character.health = character.health - attack;
		cout << "	" << monster.name << " Attacked! " << attack << " points!" << endl;
		
		//check players grades
		character.state = gradeCheck(character);

		if (character.state == alive) {
			//Player hits monster
			attack = rand() % character.strength;
			monster.health = monster.health - attack;
			cout << "	" << character.name << " Attacked! " << attack << " points!" << endl;

			monster.state = gradeCheck(monster);
			if (monster.state == alive)
			cout << "	" << monster.name << " has " << monster.health << " points left." << endl;
			else
			{
				cout << "You won!" << endl;
				cout << endl;
			}
		}

	}
	return character.health;
}

bool CheckForBlanks(Cell maze[mazeSize][mazeSize]){
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

void PrintMaze(Cell maze[mazeSize][mazeSize], int X, int Y){
	for (int s = 0; s < (mazeSize); s++)	//Prints North wall
		cout << ' ' << '_';
	
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
        			cout << '_';
        		else
        			cout << " ";
		    }
		}
		cout << "|" << endl;		//Prints East Wall
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
}

void RoomInfo(Cell maze[mazeSize][mazeSize], int X, int Y){
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

	if (maze[X][Y].Contains == Test)		//Tests are battles with the professors (see popQuiz)
	{
		int prehealth = p1.health;
		cout << "Pop Quiz!" << endl;
		cin;
		int rnd;
		rnd = (rand() % 5) +1; 
		if (rnd == 1) {
			p1.health = popQuiz(p1, gary);
		}
		else if (rnd == 2) {
			p1.health = popQuiz(p1, nathan);
		}
		else if (rnd == 3) {
			p1.health = popQuiz(p1, wallace); 
		}
		else if (rnd == 4) {
			p1.health = popQuiz(p1, kesar);
		}
		else if (rnd == 5) {
			p1.health = popQuiz(p1, borisova);
		}
		else if (rnd == 6) {
			p1.health = popQuiz(p1, rodriguez); 
		}
		
		if (p1.state == dead) //if you die in popQuiz, it's game over.
		{
			cout << "You have died" << endl;
			exit(0);
		}
		
		else
			cout << "You lost " << prehealth - p1.health << " points." << endl;
		
		cout << endl;
	}

	if (maze[X][Y].Contains == Exit)		//When you reach the Exit, you face the Final Boss!
	{
		cout << "FINAL BOSS!" << endl;
		p1.health = popQuiz(p1, mary); 
		if (p1.state == dead) //if you die in popQuiz, it's game over.
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
}

void CharacterInfo(Player p1){
	//Print Character Info
	cout << p1.name << endl;
	
		if (p1.health > 400)
			p1.health = 400;

	cout << "GPA: " << p1.health / 100 << endl;	//
	cout << endl;
}

void MoveOn(Cell maze[mazeSize][mazeSize], int X, int Y){
	bool answ = false;
	bool headed = false;

	while (!won)
	{
		steps++;
		
		//TODO: Print the Room Image

		CharacterInfo(p1);
		RoomInfo(maze, X, Y);
		
		while (!answ)
		{
			char choice;
			cout << "What now?\n" << "Check the Map(1).\n" << "Study(2).\n" << "Move on(3).\n" << endl;
			choice = getch();
			switch (choice)
			{
				case'0': 
					exit(0);
				case '1': 
					PrintMaze(maze, X, Y); break;
				case '2':
					cout << "You cannot study here..." << endl; break;
				case '3':
					answ = true; break;
				default: 
					cout << "I'm Sorry, I didn't Understand." << endl; break;
			}
			
			cout << endl;
		}

		//Getting a direction from the player
		while(!headed)
		{
			cout << "Which way?(w,a,s,d)" << endl;
			char heading;
			heading = getch();

			if(heading == '0')
				exit(0);

			if (heading == 'w' && !maze[X][Y].North)
				MoveOn(maze, X, Y - 1);

			if (heading == 'w' && maze[X][Y].North)
				cout << "There's a Wall there..." << endl;

			if (heading == 'a' && !maze[X][Y].West)
				MoveOn(maze, X - 1, Y);

			if (heading == 'a' && maze[X][Y].West)
				cout << "There's a Wall there..." << endl;

			if (heading == 's' && !maze[X][Y].South)
				MoveOn(maze, X, Y + 1);

			if (heading == 's' && maze[X][Y].South)
				cout << "There's a Wall there..." << endl;

			if (heading == 'd' && !maze[X][Y].East)
				MoveOn(maze, X + 1, Y);

			if (heading == 'd' && maze[X][Y].East)
				cout << "There's a Wall there..." << endl;

			else
				cout << "I don't Understand..." << endl;
			
			cout << endl;
		}
	}
}

int main(){
	int currPath = 1;		//Counter for creating the maze
	srand(time(NULL));

	Cell path[mazeSize * mazeSize];					//Array for creating the maze
	path[(mazeSize * mazeSize) - 1].Marked = false;	//The last Cell in the maze is not marked
	enum Direction { N, W, S, E };


	//Pick character name
//	cout << "What is your character name" << endl;
//	string playerName;
//	cin >> playerName;
//	p1.name = playerName;
	p1.name = "TEST NAME";

	//Pick character major
//	cout << "Pick a major" << endl;
//	cout << "cs, is, eet" << endl;
//	string deg;
//	cin >> deg;
//	if (deg == "cs")
//		p1.degree = cs;
//	if (deg == "is")
//		p1.degree = is;
//	if(deg == "eet")
//		p1.degree = eet;
//	else
		p1.degree = cs;

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
	MoveOn(maze, 0, 0);
}




