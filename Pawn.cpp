#include "Pawn.h"

Pawn::Pawn(int x, int y, bool b){
	xPos = x;
	yPos = y;
	black = b;
}

void Pawn::move(int xTar, int yTar)
{
	while(!checkValid(xTar, yTar))
	{
		//get x and y
	}
	xPos = xTar;
	yPos = yTar;
}

bool Pawn::checkValid(int xTar, int yTar)
{
	if(yTar !== yPos + 1)
	{
		return False;
	}
	else if(xTar == xPos && //piece on square)
	{
		return False;
	}
	else if((xTar == xPos + 1 || xTar == xPos - 1) && //opposing piece not on square)
	{
		return False;
	}
	else
	{
		return True;
	}
}
