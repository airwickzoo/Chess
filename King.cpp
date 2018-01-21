#include "King.h"
#include <cmath>

using namespace std;

King::King(int x, int y, char p):Piece(x,y,p)
{
	//xPos = x;
	//yPos = y;
	//piece = p;
}
bool King::checkValid(int xTar, int yTar, Piece* board[8][8])
{
	if(abs(xTar-xPos) == 1 && abs(yTar-yPos) == 0){
		return true;
	}else if(abs(xTar-xPos) == 0 && abs(yTar-yPos) == 1){
		return true;
	}else if(abs(xTar-xPos) == 1 && abs(yTar-yPos) == 1){
		return true;
	}else{
		return false;
	}
	
	xPos = xTar;
	yPos = yTar;
	return true;
}