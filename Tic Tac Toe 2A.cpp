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

using namespace std;

//Constants
const int DIM = 3;
const char EMPTY = ' ';
const char TIE = '\0';

//Prototypes
int gameMode();
void inputSymbols(char& playerP, char& otherP);
void initArray(char boardP[][DIM], int size);
void printArray(const char boardP[][DIM], int size);
bool checkArray(const char boardP[][DIM], int size, int rowP, int colP, char sentinel);
void userTurn(char boardP[][DIM], int size, char symbol);
void getPosition(int& rowP, int& colP, int size1, int size2);
char winState(const char boardP[][DIM], int size, char first, char second);
bool fullBoard(const char boardP[][DIM], int size);
bool won(const char boardP[][DIM], int size, char symbol);
bool rowWin(const char boardP[][DIM], int size, char symbol);
bool colWin(const char boardP[][DIM], int size, char symbol);
bool diaWin(const char boardP[][DIM], int size, char symbol);
bool diaBackslash(const char boardP[][DIM], int size, char symbol);
bool diaSlash(const char boardP[][DIM], int size, char symbol);
void randomStupid(char boardP[][DIM], int size, char symbol);
void randomSimple(char boardP[][DIM], int size, char user, char comp);
int winnable(const char boardP[][DIM], int size, char symbol);
int winnablesHelper(char a, char b, char c, char sentinel);
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

	//Seed Random
	srand(time(NULL));

	//Menu
	do
	{
		cout << "\tTic Tac Toe\n\n";

		//Get gamemode and player/opponent symbols
		gamemode = gameMode();
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
				userTurn(board, DIM, player);
			}
			else //even, opponent's turn
			{
				switch (gamemode)
				{
				case 0:
					cout << "Player 2's Turn\n";
					userTurn(board, DIM, other);
					break;
				case 1:
					cout << "Computer's Turn\n";
					randomStupid(board, DIM, other);
					break;
				default:
					//gamemode 2
					cout << "Computer's Turn\n";
					randomSimple(board, DIM, player, other);
				}
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
void userTurn(char boardP[][DIM], int size, char symbol)
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

//Pre: Array of letters boardP is initialized and has been
// printed to the screen. Whole number size is initialized
// to the number of rows in boardP. Letter symbol is initialized to
// the symbol the computer is using as a marker.
//Post: Computer has taken one turn by selecting a random
// empty position.
//Note: While extremely unlikely, in theory this could run infinite
// times if the computer keeps randomly generating already filled positions.
//TODO: Consider fixing Note
void randomStupid(char boardP[][DIM], int size, char symbol)
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
void randomSimple(char boardP[][DIM], int size, char user, char comp)
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
		randomStupid(boardP, size, comp);
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