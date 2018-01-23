#include "Knight.h"
#include <cmath>

using namespace std;

Knight::Knight(int x, int y, char p):Piece(x,y,p)
{
	xPos = x;
	yPos = y;
	piece = p;
}