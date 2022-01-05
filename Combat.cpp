#include "Combat.h"
#include <cstdlib#include <ctime>

using namespace std;
int numBattles = 0;

status gradeCheck(Player p) {	//checks if player's alive or dead
	if (p.health > 0) {
		return alive;
	}
	else {
		return dead;
	}
}

int combat(Player character, Player monster) {	//combat between given 'Players'
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