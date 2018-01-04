#ifdef ROOK_H
#define ROOK_H

class Rook
{
public:
	Rook(int x, int y, char p);
	
	void move(int xTar, int yTar);
	
	bool checkValid(int xTar, int yTar);
	
	int get_xPos();
	
	int get_yPos();
	
private:
	int xPos;
	int yPos;
	char piece;
}

#endif
