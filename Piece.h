#ifndef PIECE_H
#define PIECE_H

class Piece
{
public:
	//Constructor
	Piece(int x, int y, char p);
	
	char get_piece();
	
	bool get_moved();

	void set_moved();
	
protected:
	int xPos;
	int yPos;
	char piece;
	bool moved;

};
#endif