#ifdef PIECE_H
#define PIECE_H

class Piece
{
public:
	int get_xPos();
	
	int get_yPos();
	
	char get_piece();
	
	void set_xPos(int xTar);
	
	void set_yPos(int yTar);
	
private:
	int xPos;
	int yPos;
	char piece;
	bool moved;
}

#endif
