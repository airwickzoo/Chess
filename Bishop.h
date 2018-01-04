#ifdef BISHOP_H
#define BISHOP_H

class Bishop
{
public:
	Bishop(int x, int y, char p);
	
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
