#ifndef PAWN_H
#define PAWN_H

class Pawn{
	public:
	
	Pawn(int x, int y, int b);
	
	void move(int xTar, int yTar);
	
	bool checkValid(int xTar, int yTar);
	
	private:
		int xPos;
		int yPos;
		bool black;
};

#endif