#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(int x, int y, char p);
	
	//void move(int xTar, int yTar);
	
	virtual bool checkValid(int xTar, int yTar, Piece* board[8][8]);
};

#endif
