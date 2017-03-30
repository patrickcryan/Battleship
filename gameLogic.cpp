#include <iostream>
#include <string>
#include <ctime>
#include "Ship.h"
#include "gameLogic.h"
#include <iomanip>
#include <ctime>

void Game::userTurn(ship comp[4], char board[][10])
{
	bool hit = false;
	bool new_turn = false;
	int row, col;
	cout << "Enter an x and y coordinate: ";
	cin >> col >> row;
	cout << endl;
	row--;
	col--;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < comp[i].getSize(); j++)
		{
			if (comp[i].loc[j].x == col && comp[i].loc[j].y == row && comp[i].isAlive() != true)
			{
				cout << "The computer's " << comp[i].getName() << " is already destroyed, enter a different set of corrdinates" << endl;
				new_turn = true;

				if (new_turn == true)
				{
					userTurn(comp, board);
				}
			}
			else if (comp[i].loc[j].x == col && comp[i].loc[j].y == row && comp[i].isAlive() == true)
			{
				comp[i].reduceHealth();
				board[row][col] = 'x';
				hit = true;
				if (comp[i].getHealth() != 0)
				{
					cout << "Hit! The computer's " << comp[i].getName() << "'s health is now: " << comp[i].getHealth() << endl;
				}

				if (comp[i].getHealth() == 0 && comp[i].isAlive() == true)
				{
					cout << "The computer's " << comp[i].getName() << " is destroyed!" << endl;
					comp[i].setDeath();
				}
			}
			else
			{

			}
		}
	}

	if (hit != true)
	{
		cout << "Miss" << endl;
		board[row][col] = 'O';
	}
}

//checks game state after player move
bool Game::checkWin(ship user[4])
{
	bool win = false;
	int count_wins = 0;
	for (int i = 0; i < 4; i++)
	{
		if (user[i].getHealth() == 0)
		{
			count_wins++;
			if (count_wins == 4)
			{
				win = true;
			}
		}
	}

	return win;
}

void Game::setBoard(ship user[4], char board[][10], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < user[i].getSize(); j++)
		{
			int row, col;
			col = user[i].loc[j].x;
			row = user[i].loc[j].y;
			board[row][col] = '*';
		}
	}
}


void Game::printBoard(char board[][10])
{

	int row = 10;
	for (int j = 9; j >= 0; j--)
	{
		cout << left << setw(3) << row;
		row--;
		for (int k = 0; k < 10; k++)
		{
			cout << left << setw(3) << board[j][k];
		}
		cout << endl;
	}

	cout << "   ";

	for (int i = 1; i < 11; i++)
	{
		cout << left << setw(3) << i;
	}

	cout << endl;
	cout << endl;
}

void Game::validatePostion(string direction, int & row, int & col, const int health, ship user[4], int n)
{
	bool valid = true;
	for (int i = 0; i <= n; i++)
	{
		if (i != n)
		{
			if (user[i].getDirection() == "h")
			{
				for (int j = 0; j < user[i].getSize(); j++)
				{
					if (user[i].getOrientation() == col && user[i].loc[j].y == row)
					{
						cout << "Invalid coordinate, please try another" << endl;
						valid = false;
						validateDirection(direction, row, col, health);
					}
				}
			}
			if (user[i].getDirection() == "v")
			{
				for (int j = 0; j <= user[i].getSize(); j++)
				{
					if (user[j].getOrientation() == col && user[i].loc[j].y == row)
					{
						cout << "Invalid coordinate, please try another" << endl;
						valid = false;
						validateDirection(direction, row, col, health);
					}

				}
			}
		}
	}
	if (valid == true)
	{
		user[n].setLocation(row, col);
	}
}


void Game::setDefault(char board[][10], bool game)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (game == false)
			{
				board[i][j] = ' ';
			}
			else
			{
				board[i][j] = '.';
			}
		}
	}
}

void Game::validateDirection(string direction, int & row, int & col, const int health)
{
	if (direction == "v")
	{
		cout << "Enter an x coordinate (1-10) and a y coordinate(1-" << 10 - health + 1 << ")" << endl;
		cin >> col >> row;
		while (col > 10 || col < 0)
		{
			cout << "Enter an x coordinate for you ship from 1 to 10" << endl;
			cin >> col;
		}
		while (row>(10 - health + 1) || row < 0)
		{
			cout << "Enter an y coordinate for you ship from 1 to " << 10 - health + 1 << endl;
			cin >> row;
		}
	}
	if (direction == "h")
	{
		cout << "Enter an x coordinate (1-" << 10 - health + 1 << ") and a y coordinate(1-10)" << endl;
		cin >> col >> row;
		while (col >(10 - health + 1) || col < 0)
		{
			cout << "Enter an x coordinate for you ship from 1 to " << 10 - health + 1 << endl;
			cin >> col;
		}
		while (row> 10 || row < 0)
		{
			cout << "Enter an y coordinate for you ship from 1 to 10" << endl;
			cin >> row;
		}
	}

	row--;
	col--;
	cout << endl;


}

void Game::computerTurn(ship user[4], char board[][10])
{
	int row, col;
	bool hit = false;

	srand(time(0));

	row = rand() % 10;
	col = rand() % 10;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < user[i].getSize(); j++)
		{
			if (user[i].loc[j].x == col && user[i].loc[j].y == row && user[i].isAlive() == true)
			{
				user[i].reduceHealth();
				board[row][col] = 'x';
				hit = true;

				if (user[i].getHealth() != 0)
				{
					cout << "Hit! Your " << user[i].getName() << "'s health is now: " << user[i].getHealth() << endl;
				}
				if (user[i].getHealth() == 0 && user[i].isAlive() == true)
				{
					cout << user[i].getName() << " is destroyed!" << endl;
					user[i].setDeath();
				}
			}
		}
	}
	if (hit != true)
	{
		cout << "Computer has missed" << endl;
	}
}


void Game::setComp(ship computer[4], char board[][10])
{

	string direction = "";

	direction = randCompDirection();
	

	computer[0].setDirection(direction);
	computer[0].setName("Carrier");
	computer[0].setHealth(5);
	computer[0].setSize();
	computer[0].setLocation(0, 0);

	direction = randCompDirection();
	

	computer[1].setDirection(direction);
	computer[1].setName("Battleship");
	computer[1].setHealth(4);
	computer[1].setSize();
	computer[1].setLocation(1, 3);

	direction = randCompDirection();

	computer[2].setDirection(direction);
	computer[2].setName("Destroyer");
	computer[2].setHealth(3);
	computer[2].setSize();
	computer[2].setLocation(3, 6);

	direction = randCompDirection();

	computer[3].setDirection(direction);
	computer[3].setName("Submarine");
	computer[3].setHealth(2);
	computer[3].setSize();
	computer[3].setLocation(4, 8);

}

void Game::randCompLocation(ship comp[4], int count)
{
	int randX = 0;
	int randY = 0;

	srand(time(NULL));

	randX = rand()% 11;

	srand(time(NULL));

	randY = rand() % 11;

	if (comp[count].getDirection() == "v")
	{

		while (randY>(10 - comp[count].getHealth() + 1))
		{
			randY = rand() % 11;
		}
	}
	if (comp[count].getDirection() == "h")
	{
		while (randX >(10 - comp[count].getHealth() + 1))
		{
			randX = rand() % 11;
		}
		while (randY> 10)
		{
			randY = rand() % 11;
		}
	}

	comp[count].setLocation(randY, randX);

}

string Game::randCompDirection()
{
	string shipDirection;
	int randomValue;

	srand(time(NULL));

	randomValue = rand() % 100;

	randomValue = randomValue % 2;

	if(randomValue == 0)
	{
		shipDirection = "v";
	}
	else
	{
		shipDirection = "h";
	}


	return shipDirection;
}
