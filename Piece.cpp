#include "Piece.h"

using namespace std;

Piece::Piece(int x, int y, char p)
{
	xPos = x;
	yPos = y;
	piece = p;
}

int Piece::get_xPos()
{
	return xPos;
}

int Piece::get_yPos()
{
	return yPos;
}

char Piece::get_piece()
{
	return piece;
}

void Piece::set_xPos(int xTar)
{
	xPos = xTar;
}

void Piece::set_yPos(int yTar)
{
	yPos = yTar;
}
