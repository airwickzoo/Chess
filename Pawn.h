#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece
{
	public:
	
	Pawn(int x, int y, char p);
	
	//void move(int xTar, int yTar);
	
	//bool checkValid(int xTar, int yTar);
	
	private:
		int xPos;
		int yPos;
		char piece;
};

#endif
