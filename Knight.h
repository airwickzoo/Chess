#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(int x, int y, char p);
	
	//void move(int xTar, int yTar);
	
	//virtual bool checkValid(int xTar, int yTar, Piece* board[8][8]);
};

#endif
