#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include "Ship.h"
#include <iomanip>
#include <ctime>

struct Game
{
	void validateDirection(string direction, int & row, int & col, const int health);
	void validatePostion(string direction, int & row, int & col, const int health, ship user[4], int n);
	void userTurn(ship comp[4], char board[][10]);
	void computerTurn(ship user[4], char board[][10]);
	bool checkWin(ship user[4]);
	void printBoard(char board[][10]);
	void setBoard(ship user[4], char board[][10], int n);
	void setDefault(char board[][10], bool game);
	void setComp(ship user[4]);
};