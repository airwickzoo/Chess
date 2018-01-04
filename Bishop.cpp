#include "Bishop.h"

Bishop::Bishop(int x, int y, bool b)
{
	xPos = x;
	yPos = y;
	black = b;
}

void Bishop::move(int xTar, int yTar)
{
	while(!checkValid(xTar, yTar))
	{
		//get x and y
	}
	xPos = xTar;
	yPos = yTar;
}

bool Bishop::checkValid(int xTar, int yTar)
{
	if((xPos-xTar)/(yPos-yTar) != -1 || (xPos-xTar)/(yPos-yTar) != 1))
	{
		return False;
	}
	else if(//piece between Bishop and square)
	{
		return False;
	}
	else if(//put own king in check)
	{
		return False;
	}
	else if(//own piece on square)
	{
		return False;
	}
	else
	{
		return True;
	}
}

int Bishop::get_xPos()
{
	return xPos;
}

int Bishop::get_yPos()
{
	return yPos;
}