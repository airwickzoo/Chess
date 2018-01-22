#include "Pawn.h"
#include <iostream>

using namespace std;

Pawn::Pawn(int x, int y, char p):Piece(x,y,p)
{
	xPos = x;
	yPos = y;
	piece = p;
}
/**
void Pawn::move(int xTar, int yTar)
{
	while(!checkValid(xTar, yTar))
	{
		//get x and y
	}
	xPos = xTar;
	yPos = yTar;
}
*/
bool Pawn::checkValid(int xTar, int yTar, Piece* board[8][8])
{

	int two = 2;
	int one = 1;

	if(isupper(piece))
	{
		two = -2;
		one = -1;
	}
	
	if(xTar - xPos > 2 || xPos - xTar > 2)
	{
		return false;
	}
	if(yPos == yTar)
	{
		cout<< "goh here" << endl;
		if(board[xTar][yTar] != NULL)
		{
			return false;
		}
		if(xTar != xPos + one && xTar != xPos + two)
		{
			return false;
		}
		if(xTar == xPos + two && moved)
		{
			return false;
		}
	}
	else if(yTar == yPos + 1 || yTar == yPos - 1)
	{
		if(xTar != xPos + one)
		{
			return false;
		}
		if(!board[xTar][yTar])
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	xPos = xTar;
	yPos = yTar;
	return true;
}
