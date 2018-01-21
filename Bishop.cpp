#include "Bishop.h"
#include <iostream>

using namespace std;

Bishop::Bishop(int x, int y, char p):Piece(x,y,p)
{
	xPos = x;
	yPos = y;
	piece = p;
	//moved = False;
}
/**
void Bishop::move(int xTar, int yTar)
{
	while(!checkValid(xTar, yTar))
	{
		//get x and y
	}
	xPos = xTar;
	yPos = yTar;
}
*/
bool Bishop::checkValid(int xTar, int yTar, Piece* board[8][8])
{
	if(xTar-xPos == 0 || yTar-yPos == 0)
		{
			return false;
		}
	else if(((double)(xTar-xPos))/(yTar-yPos) == 1.0)
	{
		if(xTar > xPos)
		{
			for(int i = 1; i < xTar-xPos; i++)
			{
				if(board[xPos+i][yPos+i] != NULL)
				{
					return false;
				}
			}
		}
		else
		{
			for(int i = -1; i > xTar-xPos; i--)
			{
				if(board[xPos+i][yPos+i] != NULL)
				{
					return false;
				}
			}
		}
	}
	else if(((double)(xTar-xPos))/(yTar-yPos) == -1.0)
	{
		if(xTar > xPos)
		{
			for(int i = 1; i < xTar-xPos; i++)
			{
				if(board[xPos+i][yPos-i] != NULL)
				{
					return false;
				}
			}
		}
		else
		{
			for(int i = -1; i > xTar-xPos; i--)
			{
				if(board[xPos+i][yPos-i] != NULL)
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}
