#include "Knight.h"
#include <cmath>

using namespace std;

Knight::Knight(int x, int y, char p):Piece(x,y,p)
{
	xPos = x;
	yPos = y;
	piece = p;
}

bool Knight::checkValid(int xTar, int yTar, Piece* board[8][8])
{
	if(abs(xPos-xTar) == 2 && abs(yPos-yTar) == 1)
	{
		return true;
	}
	else if(abs(xPos-xTar) == 1 && abs(yPos-yTar) == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
	
	xPos = xTar;
	yPos = yTar;
	return true;
}