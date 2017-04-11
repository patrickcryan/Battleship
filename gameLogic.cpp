#include "Ship.h"
#include "gameLogic.h"
#include <iostream>




void Game::userTurn(ship comp[4], char board[][10])
{
	bool hit = false;
	bool new_turn = false;
	bool validShot = true;
	int row, col;
	cout << "Enter an x and y coordinate: ";
	cin >> col >> row;
	cout << endl;
	row--;
	col--;

	for (list<Location>::iterator i = playerAttempts.begin(); i != playerAttempts.end(); i++)
	{
		if (row == i->y && col == i->x)
		{
			validShot = false;
		}
		while (validShot == false)
		{
			i = playerAttempts.begin();
			cout << "You already tried this coordinate, please try agian: ";
			cin >> col >> row;
			row--;
			col--;
			validShot = true;
			for (list<Location>::iterator i = playerAttempts.begin(); i != playerAttempts.end(); i++)
			{
				if (row == i->y && col == i->x)
				{
					validShot = false;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < comp[i].getSize(); j++)
		{
			if (comp[i].loc[j].x == col && comp[i].loc[j].y == row && comp[i].isAlive() == true)
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

				Location temp;
				temp.x = col;
				temp.y = row;

				playerAttempts.push_front(temp);
			}
			else
			{

			}
		}
	}

	if (hit != true)
	{
		Location temp;
		temp.x = col;
		temp.y = row;

		playerAttempts.push_front(temp);
		cout << "Miss" << endl;
		board[row][col] = 'O';
	}
}

//checks game state after player move
bool Game::checkWin(ship user[4])
{
	int count_wins = 0;
	for (int i = 0; i < 4; i++)
	{
		if (user[i].getHealth() == 0)
		{
			count_wins++;
			if (count_wins == 4)
			{
				return true;
			}
		}
	}

	return false;
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


void Game::printBoard(char board[][10], ship user[4], ship comp[4], bool setup, int shipCount)
{
	int compShipCount = 0;
	int playerShipCount = 0;
	int row = 10;
	for (int j = 9; j >= 0; j--)
	{
		cout << left << setw(3) << row;
		row--;
		for (int k = 0; k < 10; k++)
		{
			cout << left << setw(3) << board[j][k];
		}

		if (setup == true && row >= 5)
		{
			if (row == 9)
			{
				cout << "Computer's Health";

			}
			if (row == 8)
			{
				if (comp[compShipCount].isAlive() == true)
				{
					cout << "Carrier: " << comp[compShipCount].getHealth();
				}
				compShipCount++;
				
			}
			else if (row == 7)
			{
				if (comp[compShipCount].isAlive() == true)
				{
					cout << "Battleship: " << comp[compShipCount].getHealth();
				}
				compShipCount++;
			}
			else if (row == 6)
			{
				if (comp[compShipCount].isAlive() == true)
				{
					cout << "Destroyer: " << comp[compShipCount].getHealth();
				}
				compShipCount++;
			}
			else if (row == 5)
			{
				if (comp[compShipCount].isAlive() == true)
				{
					cout << "Submarine: " << comp[compShipCount].getHealth();
				}
			}
		}
		if (row == 4)
		{
			
		}
		else if (row == 3)
		{
			cout << "Your Health";
		}
		else if (row == 2)
		{
			cout << user[playerShipCount].getName() << ": " << user[playerShipCount].getHealth();
			playerShipCount++;
		}
		else if (row == 1 && shipCount >= 1)
		{
			cout << user[playerShipCount].getName() << ": " << user[playerShipCount].getHealth();
			playerShipCount++;
		}
		else if (row == 0 && shipCount >= 2)
		{
			cout << user[playerShipCount].getName() << ": " << user[playerShipCount].getHealth();
			playerShipCount++;
		}
		
		cout << endl;
	}

	cout << "   ";

	for (int i = 1; i < 11; i++)
	{
		cout << left << setw(3) << i;
	}
	if (shipCount >= 3)
	{
		cout << user[playerShipCount].getName() << ": " << user[playerShipCount].getHealth();
	}
	

	cout << endl;
	cout << endl;
}

void Game::validatePostion(char direction, int & row, int & col, const int health, ship user[4], int n)
{
	bool valid = true;
	for (int i = 0; i <= n; i++)
	{
		if (i != n)
		{
			if (user[i].getDirection() == 'h"')
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
			if (user[i].getDirection() == 'v')
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

void Game::validateDirection(char direction, int & row, int & col, const int health)
{
	if (direction == 'v')
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
	if (direction == 'h')
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
	bool hit = false;
	bool validShot = true;

	int row = 0;
	int col = 0;

	if (seekMode == true)
	{
		row = rand() % 10;
		col = rand() % 10;


		for (list<Location>::iterator i = compAttempts.begin(); i != compAttempts.end(); i++)
		{
			if (row == i->y && col == i->x)
			{
				validShot = false;
			}
			while (validShot == false)
			{
				i = compAttempts.begin();

				row = rand() % 10;
				col = rand() % 10;

				validShot = true;
				for (list<Location>::iterator i = compAttempts.begin(); i != compAttempts.end(); i++)
				{
					if (row == i->y && col == i->x)
					{
						validShot = false;
					}
				}
			}
		}
	}
	else if (huntMode == true)
	{

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < user[i].getSize(); j++)
			{
				if (user[i].loc[j].x == col && user[i].loc[j].y == row && user[i].isAlive() == true)
				{
					user[i].reduceHealth();
					board[row][col] = 'x';
					hit = true;

					Location temp;
					temp.x = col;
					temp.y = row;
					compAttempts.push_front(temp);

					if (user[i].getHealth() != 0)
					{
						cout << "Hit! Your " << user[i].getName() << "'s health is now: " << user[i].getHealth() << endl;
					}
					if (user[i].getHealth() == 0 && user[i].isAlive() == true)
					{
						cout << user[i].getName() << " is destroyed!" << endl;
						user[i].setDeath();
						seekMode = true;
						huntMode = false;
					}
				}
			}
		}
		if (hit != true)
		{
			cout << "Computer has missed" << endl;
			Location temp;
			temp.x = col;
			temp.y = row;
			compAttempts.push_front(temp);
		}
	}
}


void Game::setComp(ship computer[4], char board[][10])
{
	int compShipCount = 0;

	computer[compShipCount].setDirection(randCompDirection());
	computer[compShipCount].setName("Carrier");
	computer[compShipCount].setHealth(5);
	computer[compShipCount].setSize();
	randCompLocation(computer, compShipCount);
	compShipCount++;
	setBoard(computer, board, compShipCount);
	_sleep(100);

	computer[compShipCount].setDirection(randCompDirection());
	computer[compShipCount].setName("Battleship");
	computer[compShipCount].setHealth(4);
	computer[compShipCount].setSize();
	randCompLocation(computer, compShipCount);
	compShipCount++;
	setBoard(computer, board, compShipCount);
	_sleep(100);


	computer[2].setDirection(randCompDirection());
	computer[2].setName("Destroyer");
	computer[2].setHealth(3);
	computer[2].setSize();
	randCompLocation(computer, compShipCount);
	compShipCount++;
	setBoard(computer, board, compShipCount);
	_sleep(100);



	computer[3].setDirection(randCompDirection());
	computer[3].setName("Submarine");
	computer[3].setHealth(2);
	computer[3].setSize();
	randCompLocation(computer, compShipCount);
	compShipCount++;
	setBoard(computer, board, compShipCount);


}

void Game::randCompLocation(ship comp[4], int count)
{
	bool valid = true;

	int maxY = (10 - comp[count].getHealth() + 1);
	int randY = rand() % maxY;


	int maxX = (10 - comp[count].getHealth() + 1);
	int randX = rand() % maxX;


	if (comp[count].getDirection() == 'h')
	{
		for (int i = 0; i < count; i++)
		{

			for (int j = 0; j < comp[i].getSize(); j++)
			{
				if (comp[i].loc[j].x == randX && comp[i].loc[j].y == randY)
				{
					valid = false;

				}
				if (valid == false)
				{
					i = 0;
					j = 0;

					randY = rand() % 11;
					maxX = (10 - comp[count].getHealth() + 1);
					randX = rand() % maxX;
					
					valid = true;
				}
			}
		}
	}

	if (comp[count].getDirection() == 'v')
	{
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < comp[i].getSize(); j++)
			{
				if (comp[i].loc[j].x == randX && comp[i].loc[j].y == randY)
				{
					valid = false;

				}
				if (valid == false)
				{
					i = 0;
					j = 0;

					maxY = (10 - comp[count].getHealth() + 1);
					randX = rand() % 11;

					

					valid == true;
				}

			}
		}
	}


	comp[count].setLocation(randY, randX);
	cout << "Computer's " << comp[count].getName() << " position's is set" << endl;

}


char Game::randCompDirection()
{	
	srand(time(NULL));	
	int randomValue = rand() % 100;


	if(randomValue % 2 == 0)

	{
		return 'v';
	}
	else
	{
		return 'h';
	}
}
