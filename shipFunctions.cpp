#include <iostream>
#include <string>
#include "Ship.h"
using namespace std;


	void ship::setName(string g_name)
	{
		name = g_name;
	}

	void ship::setSize()
	{
		size = health;
	}

	int ship::getSize()
	{
		return size; 
	}

	string ship::getName()
	{
		return name;
	}

	void ship::setLocation(int row, int col)
	{
		if (direction == "horizontal")
		{
			loc = new Location[health];

			for (int i = 0; i < health; i++)
			{
				loc[i].y = row; 
				loc[i].x = col;
				col++;
			}

			orientation = row;
		}
		
		if (direction == "vertical")
		{
			loc = new Location[health];

			for (int i = 0; i < health; i++)
			{
				loc[i].x = col;
				loc[i].y = row;
				row++;

				orientation = col;
			}
		}

	}


	void ship::reduceHealth()
	{
		health -= 1;
	}

	int ship::getHealth()
	{
		return health;
	}


	void ship::setHealth(int u_health)
	{
		health = u_health;
	}


	bool ship::isAlive()
	{
		if (alive == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void ship::setDeath()
	{
		alive = false;
	}

	void ship::setDirection(string loc)
	{
		direction = loc;
	}

	string ship::getDirection()
	{
		return direction;
	}

	int ship::getOrientation()
	{
		return orientation;
	}