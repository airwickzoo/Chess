#include "Queen.h"
#include <iostream>

using namespace std;

Queen::Queen(int x, int y, char p):Piece(x,y,p)
{
	xPos = x;
	yPos = y;
	piece = p;
}
/**
void Queen::move(int xTar, int yTar)
{
	while(!checkValid(xTar, yTar))
	{
		//get x and y
	}
	xPos = xTar;
	yPos = yTar;
}


bool Queen::checkValid(int xTar, int yTar, Piece* board[8][8])
{
	cout << "theshit";
	if(xPos == xTar)
	{
		cout << "kms";
		cout << xPos << " " << xTar;
		cout << yPos << " " << yTar;
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
	}
	else if(yPos == yTar)
	{
		cout << "kys";
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
	}
	else if((yTar != yPos) && ((double)(xTar-xPos))/(double)(yTar-yPos) == 1.0)
	{
		cout << "virts ship wallys shit";
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
	else if((yTar != yPos) && ((double)(xTar-xPos))/(double)(yTar-yPos) == -1.0)
	{
		cout << "kill hoffman";
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
		cout << "????????";
		return false;
	}

	xPos = xTar;
	yPos = yTar;
	return true;
}*/
