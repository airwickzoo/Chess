#include "Rook.h"

Rook::Rook(int x, int y, char p)
{
	xPos = x;
	yPos = y;
	piece = p;
	moved = False;
}

void Rook::move(int xTar, int yTar)
{
	while(!checkValid(xTar, yTar))
	{
		//get x and y
	}
	xPos = xTar;
	yPos = yTar;
}

bool Rook::checkValid(int xTar, int yTar)
{
	if(xPos != xTar && yPos != yTar)
	{
		return False;
	}
	else if(//piece between rook and square)
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
