#ifdef QUEEN_H
#define QUEEN_H

class Queen : public Piece
{
public:
	Queen(int x, int y, char p);
	
	void move(int xTar, int yTar);
	
	bool checkValid(int xTar, int yTar);
	
	int get_xPos();
	
	int get_yPos();
	
	char get_piece();
	
private:
	int xPos;
	int yPos;
	char piece;
}

#endif
