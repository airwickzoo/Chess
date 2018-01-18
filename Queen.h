#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(int x, int y, char p);
	
	//void move(int xTar, int yTar);
	
	//virtual bool checkValid(int xTar, int yTar, Piece* board[8][8]);
};

#endif
