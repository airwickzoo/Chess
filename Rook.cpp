#include "Rook.h"
#include <iostream>

using namespace std;

Rook::Rook(int x, int y, char p):Piece(x,y,p)
{
}
/**
void Rook::move(int xTar, int yTar)
{
	while(!checkValid(xTar, yTar))
	{
		//get x and y
	}
	xPos = xTar;
	yPos = yTar;
}


bool Rook::checkValid(int xTar, int yTar, Piece* board[8][8])
{
	if(xPos == xTar)
	{
		if(yTar > yPos)
		{
			for(int i = yPos + 1; i < yTar; i++)
			{
				if(board[xPos][i] != NULL)
				{
					return false;
				}
			}
		}
		else
		{
			for(int i = yTar + 1; i < yPos; i++)
			{
				if(board[xPos][i] != NULL)
				{
					return false;
				}
			}
		}
		return true;
	}
	else if(yPos == yTar)
	{
		if(xTar > xPos)
		{
			for(int i = xPos + 1; i < xTar; i++)
			{
				if(board[i][yPos] != NULL)
				{
					return false;
				}
			}
		}
		else
		{
			for(int i = xTar + 1; i < xPos; i++)
			{
				if(board[i][yPos] != NULL)
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
	
	xPos = xTar;
	yPos = yTar;
	return true;
}*/
