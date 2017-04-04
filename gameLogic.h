#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include "Ship.h"
#include <iomanip>
#include <ctime>
#include <list>

struct Game
{
	void validateDirection(string, int &, int &, const int);
	void validatePostion(string, int &, int &, const int, ship[4], int);
	void userTurn(ship[4], char board[][10]);
	void computerTurn(ship[4], char[][10]);
	bool checkWin(ship user[4]);
	void printBoard(char[][10], ship[4], ship[4]);
	void setBoard(ship[4], char[][10], int n);
	void setDefault(char[][10], bool);
	void setComp(ship user[4], char board[][10]);
	void randCompLocation(ship[4], int);
	string randCompDirection();

	list<Location> playerAttempts;
	list<Location> compAttempts;
};