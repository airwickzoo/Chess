#include "Piece.h"
#include <cctype>
#include <iostream>

using namespace std;

Piece::Piece(int x, int y, char p)
{
	xPos = x;
	yPos = y;
	piece = p;
	moved = false;
}

int Piece::get_xPos()
{
	return xPos;
}

int Piece::get_yPos()
{
	return yPos;
}

char Piece::get_piece()
{
	return piece;
}

void Piece::set_xPos(int xTar)
{
	xPos = xTar;
}

void Piece::set_yPos(int yTar)
{
	yPos = yTar;
}

void Piece::set_moved()
{
	moved = true;
}

void Piece::move(int xTar, int yTar)
{
	this->xPos = xTar;
	this->yPos = yTar;
}

bool Piece::checkValid(int xTar, int yTar, Piece* board[8][8])
{
	return true;
}

