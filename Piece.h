#ifdef PIECE_H
#define PIECE_H

class Piece
{
public:
	int get_xPos();
	
	int get_yPos();
	
	char get_piece();
	
private:
	int xPos;
	int yPos;
	char piece;
}

#endif