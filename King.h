#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece
{
public:
	King(int x, int y, char p);
	
	//void move(int xTar, int yTar);
	
	//virtual bool checkValid(int xTar, int yTar, Piece* board[8][8]);
};

#endif
