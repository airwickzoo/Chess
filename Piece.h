#ifndef PIECE_H
#define PIECE_H

#include <cctype>

class Piece
{
public:

	Piece(int x, int y, char p);
	
	int get_xPos();
	
	int get_yPos();
	
	char get_piece();
	
	void set_xPos(int xTar);
	
	void set_yPos(int yTar);

	void set_moved();
	
	virtual bool checkValid(int xTar, int yTar, Piece* board[8][8]);
	
protected:
	int xPos;
	int yPos;
	char piece;
	bool moved;

};

#endif
