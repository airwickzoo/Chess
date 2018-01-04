#include "Queen.h"

Queen::Queen(int x, int y, char p)
{
	xPos = x;
	yPos = y;
	piece = p;
}

void Queen::move(int xTar, int yTar)
{
	while(!checkValid(xTar, yTar))
	{
		//get x and y
	}
	xPos = xTar;
	yPos = yTar;
}

bool Queen::checkValid(int xTar, int yTar)
{
	if((xPos != xTar && yPos != yTar) || (xPos-xTar)/(yPos-yTar) != -1 || (xPos-xTar)/(yPos-yTar) != 1)
	{
		return False;
	}
	else if(//piece between Queen and square)
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

int Queen::get_xPos()
{
	return xPos;
}

int Queen::get_yPos()
{
	return yPos;
}