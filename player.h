#ifndef PLAYER_H 
#define PLAYER_H

//Constants
namespace game
{
	const int DIM = 3;
	const char EMPTY = ' ';
	const char TIE = '\0';
};

using namespace std; 
using namespace game; 

class Player
{
public:
	virtual void turn(char board[][DIM], int size, char me, char other)=0;
};

class HumanPlayer : Player
{
public:
	void turn(char board[][DIM], int size, char me, char other);
};

class StupidPlayer : Player
{
public:
	void turn(char board[][DIM], int size, char me, char other);
};

class SimplePlayer : Player
{
public:
	void turn(char board[][DIM], int size, char me, char other);
};

#endif
