#ifndef SHIP
#define SHIP

#include <iostream>
#include <string>
using namespace std;

struct Location
{
	int x;
	int y;
};

class ship
{
private:
	string name;
	int size;
	int health;
	bool alive = true;
	char direction;
	int orientation;

public:
	void setName(string);
	string getName();
	void setLocation(int, int);
	void setHealth(const int);
	void reduceHealth();
	int getHealth();
	bool isAlive();
	void setDeath();
	void setDirection(char);
	char getDirection();
	void setSize();
	int getSize();
	int getOrientation();
	void setAttempts(int, int);
	Location * loc;
	

};


#endif;