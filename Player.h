#ifndef PLAYER
#define PLAYER

#pragma once
#include <string>
using namespace std;

enum status { alive, dead };
enum program { cs, eet, is };

struct Player {		//The official 'Player' struct
	status state;
	string name;
	double health;
	int strength;
	program degree;
};

program selectDegree(string deg);

#endif

