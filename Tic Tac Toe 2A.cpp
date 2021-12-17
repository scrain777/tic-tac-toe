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
int gameMode();
void inputSymbols(char& playerP, char& otherP);
void initArray(char boardP[][DIM], int size);
void printArray(const char boardP[][DIM], int size);
char winState(const char boardP[][DIM], int size, char first, char second);
bool fullBoard(const char boardP[][DIM], int size);
bool won(const char boardP[][DIM], int size, char symbol);
bool rowWin(const char boardP[][DIM], int size, char symbol);
bool colWin(const char boardP[][DIM], int size, char symbol);
bool diaWin(const char boardP[][DIM], int size, char symbol);
bool diaBackslash(const char boardP[][DIM], int size, char symbol);
bool diaSlash(const char boardP[][DIM], int size, char symbol);
char playAgain();
void newLine(int howMany);
string space(int howMany);
string dashes(int howMany);

int main()
{
	//Variables
	char board[DIM][DIM];
	char player, other, again;
	char outcome;
	int gamemode, round;
        Player *a, *b;

	//Seed Random
	srand(time(NULL));

	//Menu
	do
	{
		cout << "\tTic Tac Toe\n\n";

		//Get gamemode and player/opponent symbols
		gamemode = gameMode();
		a = new HumanPlayer();
                switch(gamemode)
		{
 			case 0:
				b = new HumanPlayer();
				break;
 			case 1:
				b = new StupidPlayer();
				break;
 			default:
				b = new SimplePlayer();
				break;
		}

		inputSymbols(player, other);

		//Clear and print board
		initArray(board, DIM);
		printArray(board, DIM);

		//Decide who goes first 50/50 chance
		round = (rand() % 2);

		//Turns
		do
		{
			//User or Opponent Turn
			if ((round % 2) == 1) //odd, player's turn
			{
				cout << "Player 1's Turn\n";
				a->turn(board, DIM, other, player);
			}
			else //even, opponent's turn
			{
				cout << "Player 2's Turn\n";
				b->turn(board, DIM, player, other);
			}

			//Print Board
			printArray(board, DIM);

			//Check for win
			//TODO: Define winState
			outcome = winState(board, DIM, player, other);

			round++;

		} while (outcome == EMPTY);

		//Output message saying who won
		if (outcome == player)
		{
			cout << "Congratulations, Player 1!\n\n";
		}
		else if (outcome == other)
		{
			switch (gamemode)
			{
			case 0:
				// TODO: Fix up to make more general
				cout << "Congratulations, Player 2!\n\n";
				break;
			default:
				cout << "Sorry, you lost. Better luck next time!\n\n";
			}
		}
		else if (outcome == TIE)
		{
			cout << "You tied!\n\n";
		}
		else
		{
			cout << "Oh no! Something went wrong!\n\n";
		}

		again = playAgain();

	} while (again == 'Y');



	delete a;
	delete b;

	return 0;
}

//Functions
//Pre: Program has started.
//Post: Returns game mode: 0 for player vs. player, 
//1 for player vs. random, and 2 for player vs. AI
int gameMode()
{
	int selection;
	cout << "Which mode would you like to play?\n";
	cout << "1- Against another player\n";
	cout << "2- Computer plays randomly\n";
	cout << "3- Against a simple AI\n";
	do
	{
		cin >> selection;
		if ((selection > 3) || (selection < 1))
		{
			cout << "Number must be 1, 2, or 3. Try again:";
		}
	} while ((selection > 3) || (selection < 1));
	selection--;
	return selection;
}

//Pre: Letters playerP and otherP are declared
//Post: playerP and otherP contain letters input by the user
void inputSymbols(char& playerP, char& otherP)
{
	do
	{
		cout << "Enter your symbol (e.g. X or O):\t";
		cin >> playerP;

		cout << "Enter the symbol for your opponent:\t";
		cin >> otherP;

		if (otherP == playerP)
		{
			cout << "Must be a different symbol than yours. Try again.\n";
		}

	} while (otherP == playerP);

	return;
}

//Pre: Array of letters boardP is declared
// and whole number size is initialized to the number of rows
//Post: All elements of boardP are initialized to ' ' 
void initArray(char boardP[][DIM], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			boardP[i][j] = EMPTY;
		}
	}
	return;
}

//Pre: Array of letters boardP is initialized
// whole number size is initialized to the number of rows
//Post: Outputs the array to the screen as a Tic Tac Toe board
void printArray(const char boardP[][DIM], int size)
{
	/*
	For a board that is size rows by DIM columns
	3x3 Example:

		1   2   3

	1   X | O | X
	   -----------
	2   O |   | X
	   -----------
	3   O | X |
	*/

	//Make space above board
	newLine(2);
	//Print the column labels
	cout << space(4);
	for (int rows = 0; rows < size; rows++)
	{
		cout << rows + 1 << space(3);
	}
	newLine(2);
	//Print the board rows
	for (int row = 0; row < size; row++)
	{
		//Print the row labels
		cout << row + 1 << space(3);
		//Print the row contents
		for (int col = 0; col < DIM; col++)
		{
			//Print the elements
			cout << boardP[row][col];
			//Print the vertical lines
			if (!(col == (DIM - 1)))
			{
				cout << " | ";
			}
		}
		cout << endl;
		//Print the horizontal lines
		if (!(row == (size - 1)))
		{
			cout << space(3) << dashes((size * 4) - 1) << endl;
		}
	}
	newLine(2);
	return;
}

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Char first and second
// are initialized to the symbols player and opponent are using.
//Post: Returns the symbol of the winner, if any, otherwise
// returns the value of EMPTY. If tie, returns TIE.
//TODO: THIS IS A STUB
char winState(const char boardP[][DIM], int size, char first, char second)
{
	/* Code for winState to enter value manually
	char todo;
	cout << "Enter char for winState:\t";
	cin >> todo;
	if (todo == '_')
	{
		todo = EMPTY;
	}
	return todo;*/

	//Variables
	char ans;
	bool playerwin, otherwin;

	//Input
	playerwin = won(boardP, size, first);
	otherwin = won(boardP, size, second);

	//Calculations
	if (playerwin)
	{
		if (otherwin)
		{
			ans = TIE;
		}
		else
		{
			ans = first;
		}
	}
	else
	{
		if (otherwin)
		{
			ans = second;
		}
		else
		{
			if (fullBoard(boardP, size))
			{
				ans = TIE;
			}
			else
			{
				ans = EMPTY;
			}
		}
	}

	//Output
	return ans;
}

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP.
//Post: Returns true if board contains no EMPTY spots, else false
bool fullBoard(const char boardP[][DIM], int size)
{
	bool full = true;
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < DIM; col++)
		{
			if (boardP[row][col] == EMPTY)
			{
				full = false;
				col = DIM;
			}
		}
		if (!full)
		{
			row = size;
		}
	}
	return full;
}

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Letter symbol is 
// initialized to the symbol to check for win.
//Post: Returns true if there is a row, column, or diagonal
// that is filled only with symbol.
bool won(const char boardP[][DIM], int size, char symbol)
{
	bool result;
	if (rowWin(boardP, size, symbol))
	{
		result = true;
	}
	else if (colWin(boardP, size, symbol))
	{
		result = true;
	}
	else if (diaWin(boardP, size, symbol))
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Letter symbol is 
// initialized to the symbol to check for win.
//Post: Returns true if there is a row of all symbol
bool rowWin(const char boardP[][DIM], int size, char symbol)
{
	//Assume all rows are not win
	bool win = false;
	//Check if each row is a win
	for (int row = 0; row < size; row++)
	{
		//Check each row
		//Assume row is all symbol (a win)
		bool all = true;
		//Check if each value is !symbol
		for (int col = 0; col < DIM; col++)
		{
			//If value is !symbol, update all
			if (boardP[row][col] != symbol)
			{ //the row is not a win, stop checking it
				all = false;
				col = DIM;
			}
		}
		//If row is win, update win
		if (all)
		{ //found a winning row, stop checking array
			win = true;
			row = size;
		}
	}
	//Return win
	return win;
}

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Letter symbol is 
// initialized to the symbol to check for win.
//Post: Returns true if there is a column of all symbol.
bool colWin(const char boardP[][DIM], int size, char symbol)
{
	//Assume all columns are not win
	bool win = false;
	//Check if each column is a win
	for (int col = 0; col < DIM; col++)
	{
		//Check each column
		//Assume column is all symbol (a win)
		bool all = true;
		//Check if each value is !symbol
		for (int row = 0; row < size; row++)
		{
			//If value is !symbol, update all
			if (boardP[row][col] != symbol)
			{ //the column is not a win, stop checking it
				all = false;
				row = size;
			}
		}
		//If column is win, update win
		if (all)
		{ //found a winning column, stop checking array
			win = true;
			col = DIM;
		}
	}
	//Return win
	return win;
}

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Letter symbol is 
// initialized to the symbol to check for win.
//Post: Returns true if there is a diagonal of all symbol.
bool diaWin(const char boardP[][DIM], int size, char symbol)
{
	bool win;
	if (diaSlash(boardP, size, symbol))
	{
		win = true;
	}
	else if (diaBackslash(boardP, size, symbol))
	{
		win = true;
	}
	else
	{
		win = false;
	}
	return win;
}

//Pre: Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Letter symbol is 
// initialized to the symbol to check for win.
//Post: Returns true if win by '\' diagonal, otherwise false
bool diaBackslash(const char boardP[][DIM], int size, char symbol)
{
	bool all = true;
	for (int b = 0; b < size; b++)
	{
		if (boardP[b][b] != symbol)
		{
			all = false;
			b = size;
		}
	}
	return all;
}

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Letter symbol is 
// initialized to the symbol to check for win.
//Post: Returns true if win by '/' diagonal, otherwise false
bool diaSlash(const char boardP[][DIM], int size, char symbol)
{
	bool all = true;
	for (int s = 0; s < size; s++)
	{
		if (boardP[s][(size - (s + 1))] != symbol)
		{
			all = false;
			s = size;
		}
	}
	return all;
}

//Pre: Program has started
//Post: Returns 'Y' if user wishes to play again, else 'N'
char playAgain()
{
	char response;
	cout << "Do you wish to play Tic Tac Toe again? (Y/N)";
	cin >> response;
	response = toupper(response);
	if (response == 'Y')
	{
		newLine(25);
	}
	else
	{
		response = 'N';
	}
	return response;
}

//Pre: Whole number howMany is initialized
//Post: howMany new lines are output to the screen
void newLine(int howMany)
{
	for (int i = 0; i < howMany; i++)
	{
		cout << endl;
	}
	return;
}

//Pre: Whole number howMany is inititalized
//Post: Returns a string containing howMany spaces
string space(int howMany)
{
	string answer = "";
	for (int i = 0; i < howMany; i++)
	{
		answer = answer + " ";
	}
	return answer;
}

//Pre: Whole number howMany is inititalized
//Post: Returns a string containing howMany dashes
string dashes(int howMany)
{
	string answer = "";
	for (int i = 0; i < howMany; i++)
	{
		answer = answer + "-";
	}
	return answer;
}
