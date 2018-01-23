#include "Piece.h"

using namespace std;

//Constructor
Piece::Piece(int x, int y, char p)
{
	xPos = x;
	yPos = y;
	piece = p;
	moved = false;
}

char Piece::get_piece()
{
	return piece;
}

void Piece::set_moved()
{
	moved = true;
}

bool Piece::get_moved()
{
	return moved;
}