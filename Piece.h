#ifndef PIECE_H
#define PIECE_H

class Piece
{
public:

	Piece(int x, int y, char p);
	
	int get_xPos();
	
	int get_yPos();
	
	char get_piece();
	
	void set_xPos(int xTar);
	
	void set_yPos(int yTar);
	
protected:
	int xPos;
	int yPos;
	char piece;
	//bool moved;
};

#endif
