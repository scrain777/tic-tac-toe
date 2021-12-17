/******************************************************************************
//	Jay Crain
//	12-16-21
//	Tic Tac Toe (3x3) with an Array and Functions
******************************************************************************/

#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <string>

#include "player.h"

using namespace std;
using namespace game;

//Prototypes
bool checkArray(const char boardP[][DIM], int size, int rowP, int colP, char sentinel);
void getPosition(int& rowP, int& colP, int size1, int size2);
int winnable(const char boardP[][DIM], int size, char symbol);
int winnablesHelper(char a, char b, char c, char sentinel);

//Pre: Array of letters boardP and its number of rows, whole number size, 
// are initialized. Whole numbers rowP and colP are initialized
// to the indices of the board to be checked. Letter sentinel is initialized.
//Post: Returns true if the element of the array in the specified position
//is the same as the specified sentinel value, else false.
bool checkArray(const char boardP[][DIM], int size, int rowP, int colP, char sentinel)
{
	bool ans;
	if (boardP[rowP][colP] == sentinel)
	{
		ans = true;
	}
	else
	{
		ans = false;
	}
	return ans;
}

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Letter symbol is initialized to
// the symbol the player is using as a marker.
//Post: The player has taken one turn and boardP has beeen updated accordingly.
void HumanPlayer::turn(char boardP[][DIM], int size, char me, char symbol)
{
	//Variables
	bool valid;
	int row, col;

	//Get a valid position
	do
	{
		//Get player's turn
		getPosition(row, col, size, DIM);

		//Convert row and col to indices
		row--;
		col--;

		//Check that position is blank
		valid = checkArray(boardP, size, row, col, EMPTY);

		//Error message if position is taken
		if (!valid)
		{
			cout << "That position is already filled with a(n) \'"
				<< boardP[row][col] << "\'. Please try again.\n";
		}
	} while (!valid);

	//Fill board
	boardP[row][col] = symbol;

	return;
}

//Pre: Whole numbers rowP and colP are declared.
// Whole numbers size1 and size2 are initialized to
// the dimensions of the board. 
//Post: Sets rowP and colP to where the user would like to play. 
// Will only return a value for row between 1 and size1 
// inclusive and for colP between 1 and size2 inclusive. 
//Note: These values are still 1 greater than the actual index
void getPosition(int& rowP, int& colP, int size1, int size2)
{
	//Get row
	do
	{
		cout << "Enter the row you wish to play in (numbers on the left):\t";
		cin >> rowP;
		if ((rowP < 1) || (rowP > size1))
		{
			cout << "Invalid input. Try again.\n";
		}
	} while ((rowP < 1) || (rowP > size1));
	//Get column
	do
	{
		cout << "Enter the column you wish to play in"
			<< " (numbers across the top):\t";
		cin >> colP;
		if ((colP < 1) || (colP > size2))
		{
			cout << "Invalid input. Try again.\n";
		}
	} while ((colP < 1) || (colP > size2));
	return;
}

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Letter symbol is initialized to
// the symbol the computer is using as a marker.
//Post: Computer has taken one turn by selecting a random
// empty position.
//Note: While extremely unlikely, in theory this could run infinite
// times if the computer keeps randomly generating already filled positions.
//TODO: Consider fixing Note
void StupidPlayer::turn(char boardP[][DIM], int size, char me, char symbol)
{
	//Variables
	bool valid;
	int row, col;

	//Get a valid position
	do
	{
		//Get a random position
		//Get row
		row = (rand() % size);
		//Get col
		col = (rand() % DIM);

		//Check that position is blank
		valid = checkArray(boardP, size, row, col, EMPTY);

	} while (!valid);

	//Fill board
	boardP[row][col] = symbol;

	return;
}

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Letter symbol is initialized to
// the symbol the computer is using as a marker.
//Post: Computer has taken one turn using a very simple AI that
// is slightly better than randomStupid alone.
//Note: This uses winnable, which currently only works for 3x3
void SimplePlayer::turn(char boardP[][DIM], int size, char user, char comp)
{
	bool done = false;
	int row, col, smash;
	//Can computer win?
	smash = winnable(boardP, size, comp);
	if (smash != -1)
	{
		//Calculate row and col
		row = smash / 10;
		col = smash % 10;

		//Prevent exceeding array
		if (row >= size)
		{
			cout << "Attempted to play in a wrong row- error code computerwin\n\n";
			exit(1);
		}
		if (col >= DIM)
		{
			cout << "Attempted to play in a wrong column- error code computerwin\n\n";
			exit(1);
		}

		//Check that position is really empty
		if (checkArray(boardP, size, row, col, EMPTY))
		{
			//Play there
			boardP[row][col] = comp;
			//Set done to true
			done = true;
		}
		else
		{
			cout << "Attempted to play in an already filled space- error code computerwin\n\n";
			exit(1);
		}
	}

	//Can player win (and we need to block)?
	if (!done)
	{
		smash = winnable(boardP, size, user);
		if (smash != -1)
		{
			//Calculate row and col
			row = smash / 10;
			col = smash % 10;

			//Prevent exceeding array
			if (row >= size)
			{
				cout << "Attempted to play in a wrong row- error code playerwin\n\n";
				exit(1);
			}
			if (col >= DIM)
			{
				cout << "Attempted to play in a wrong column- error code playerwin\n\n";
				exit(1);
			}

			//Check that position is really empty
			if (checkArray(boardP, size, row, col, EMPTY))
			{
				//Play there
				boardP[row][col] = comp;
				//Set done to true
				done = true;
			}
			else
			{
				cout << "Attempted to play in an already filled space- error code playerwin\n\n";
				exit(1);
			}
		}
	}

	//If nobody can win immediately, then call randomStupid
	if (!done)
	{
		StupidPlayer::turn(boardP, size, user, comp);
	}

	return;
}

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Letter symbol is initialized to
// the symbol of the entity to check if can win on next turn.
//Post: If the entity using symbol cannot win in 1 turn, returns -1.
// If the entity can win in 1 turn, returns a position they could win
// with, as one smashed together number (ex. (1, 1) becomes 11)
//TODO: Consider whether this would benefit from a different branching.
//Note: Assumes 3x3! If you want to use a different board, rewrite!
int winnable(const char boardP[][DIM], int size, char symbol)
{
	int answer = -1, helper;
	//rows
	for (int row = 0; row < size; row++)
	{
		helper = winnablesHelper(boardP[row][0], boardP[row][1], boardP[row][2], symbol);
		helper--;
		if (helper != -1)
		{
			answer = (row * 10) + helper;
			row = size;
		}
	}

	//columns
	if (answer == -1)
	{
		for (int col = 0; col < DIM; col++)
		{
			helper = winnablesHelper(boardP[0][col], boardP[1][col], boardP[2][col], symbol);
			helper--;
			if (helper != -1)
			{
				answer = (helper * 10) + col;
				col = DIM;
			}
		}
	}

	//dia '\'
	if (answer == -1)
	{
		helper = winnablesHelper(boardP[0][0], boardP[1][1], boardP[2][2], symbol);
		helper--;
		if (helper != -1)
		{
			answer = (helper * 10) + helper;
		}
	}

	//dia '/'
	if (answer == -1)
	{
		helper = winnablesHelper(boardP[0][2], boardP[1][1], boardP[2][0], symbol);
		helper--;
		switch (helper)
		{
		case 0:
			answer = 2;
			break;
		case 1:
			answer = 11;
			break;
		case 2:
			answer = 20;
			break;
		default:
			answer = -1;
		}
	}

	return answer;
}

//Pre: 3 letters to check and a sentinel letter are initialized
//Post: If the 3 letters contain two sentinels and an EMPTY, 
// returns 1 if a was EMPTY, 2 if b, 3 if c. 
// Otherwise, returns 0.
int winnablesHelper(char a, char b, char c, char sentinel)
{
	int answer;
	if (a == sentinel)
	{
		if (b == sentinel)
		{
			if (c == EMPTY)
			{
				answer = 3;
			}
			else
			{
				answer = 0;
			}
		}
		else if (b == EMPTY)
		{
			if (c == sentinel)
			{
				answer = 2;
			}
			else
			{
				answer = 0;
			}
		}
		else
		{
			answer = 0;
		}
	}
	else if (a == EMPTY)
	{
		if (b == sentinel)
		{
			if (c == sentinel)
			{
				answer = 1;
			}
			else
			{
				answer = 0;
			}
		}
		else
		{
			answer = 0;
		}
	}
	else
	{
		answer = 0;
	}
	return answer;
}
