#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include "Ship.h"
#include <iomanip>
#include <list>

struct Game
{
	void validateDirection(char, int &, int &, const int);
	void validatePostion(char, int &, int &, const int, ship[4], int);
	void userTurn(ship[4], char board[][10]);
	void computerTurn(ship[4], char[][10]);
	bool checkWin(ship user[4]);
	void printBoard(char[][10], ship[4], ship[4], bool, int);
	void setBoard(ship[4], char[][10], int n);
	void setDefault(char[][10], bool);
	void setComp(ship user[4], char board[][10]);
	void randCompLocation(ship[4], int);
	char randCompDirection();

	bool seekMode = false;
	bool huntMode = true;

	list<Location> playerAttempts;
	list<Location> compAttempts;
};