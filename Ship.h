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
	string direction;
	int orientation;

public:
	void setName(string g_name);
	string getName();
	void setLocation(int row, int col);
	void setHealth(const int u_health);
	void reduceHealth();
	int getHealth();
	bool isAlive();
	void setDeath();
	void setDirection(string loc);
	string getDirection();
	void setSize();
	int getSize();
	int getOrientation();
	Location * loc;
	

};


#endif;