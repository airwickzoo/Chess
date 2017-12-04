/*
#include “Piece.h”
#include “King.h”
#include “Pawn.h”
#include “Queen.h”
#include “Bishop.h”
#include “Knight.h”
#include “Rook.h”
*/

using namespace std;

/**
	Creates the starting chess board
	@param 8x8 array for entire board
	@return void (NULL)
*/
void starting_board(piece *x[][8])
{
	x[0][0] = new Rook(0,0,true); 
	x[0][1] = new Knight(0,1,true);
	x[0][2] = new Bishop(0,2,true);
	x[0][3] = new Queen(0,3,true);
	x[0][4] = new King(0,4,true);
	x[0][5] = new Bishop(0,5,true);
	x[0][6] = new Knight(0,6,true);
	x[0][7] = new Rook(0,7,true);
	x[1][0] = new Pawn(1,0,true);
	x[1][1] = new Pawn(1,1,true);
	x[1][2] = new Pawn(1,2,true);
	x[1][3] = new Pawn(1,3,true);
	x[1][4] = new Pawn(1,4,true);
	x[1][5] = new Pawn(1,5,true);
	x[1][6] = new Pawn(1,6,true);
	x[1][7] = new Pawn(1,7,true);
	x[6][0] = new Pawn(6,0,false);
	x[6][1] = new Pawn(6,1,false);
	x[6][2] = new Pawn(6,2,false);
	x[6][3] = new Pawn(6,3,false);
	x[6][4] = new Pawn(6,4,false);
	x[6][5] = new Pawn(6,5,false);
	x[6][6] = new Pawn(6,6,false);
	x[6][7] = new Pawn(6,7,false);
	x[7][0] = new Rook(7,0,false);
	x[7][1] = new Knight(7,1,false);
	x[7][2] = new Bishop(7,2,false);
	x[7][3] = new Queen(7,3,false);
	x[7][4] = new King(7,4,false);
	x[7][5] = new Bishop(7,5,false);
	x[7][6] = new Knight(7,6,false);
	x[7][7] = new Rook(7,7,false);
}

/**
	Asks player if wants to play another game_board
	@param 
	@return true or false
*/
bool continue_playing(){
	//Ask if the player wants to play another match
}

int main()
{
	
	
	do{
		bool cont = false;
		
		//Game board variable
		piece* game_board[8][8] = NULL;
		
		starting_board(game_board);
		
		//Playing Chess game
		//play();
		
		//Remove memory of the game board
		delete game_board;
		
		//Ask user if they want to play again
		cont = continue_playing();
	}while(cont);
	
	
	
	return 0;
}
