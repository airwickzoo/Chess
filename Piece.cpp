#include "Piece.h"

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