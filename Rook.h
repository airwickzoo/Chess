#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(int x, int y, char p);
	
	//void move(int xTar, int yTar);
	
	//virtual bool checkValid(int xTar, int yTar, Piece* board[8][8]);
};

#endif
