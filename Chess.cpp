#include "Piece.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"

#include <iostream>
#include <iomanip>

using namespace std;

const int CHESS_SIZE = 8;
int turn = 0;

const string black_piece = "prnbkq";
const string white_piece = "PRNBKQ";

//Game board variable
Piece* x[8][8];
string fake_board[8][8];

void printing_board(){
	cout << "  +------------------------+" << endl;
	for(int row = 0; row < 8; row++){
		cout << 8-row << " |";
		for(int col = 0; col < 8; col++){
			if(x[row][col] != NULL){
				char piece = x[row][col]->get_piece();
				if(turn%2 == 0){
					//White's turn
					if(piece >= 65 && piece <= 90){
						//Check if piece is white's piece
						cout << "<" << piece << ">";
					}else if(piece >= 97 && piece <= 122){
						//Black's piece
						cout << "[" << piece << "]";
					}
				}else{
					//Black's turn
					if(piece >= 65 && piece <= 90){
						//Check if piece is white's piece
						cout << "[" << piece << "]";
					}else if(piece >= 97 && piece <= 122){
						//Black's piece
						cout << "<" << piece << ">";
					}
				}
			}else{
				cout << fake_board[row][col];
			}
			
		}
		cout << "|" << endl;
	}
	
	cout << "  +------------------------+" << endl;
	cout << "    a  b  c  d  e  f  g  h" << endl;
}


void play(){
	//DO EVERYTHING
	cout << "Welcome! Before you start your game please note" << endl;
	cout << "That the common notation is letter then number" << endl;
	cout << "Such as b6 all other input would be invalid thank you." << endl;
	
	bool checkmate = false;
	while(!checkmate){
		string player;
		if(turn%2 == 0)
			player = "White";
		else
			player = "Black";
		cout << player << "'s move:" << endl;
		printing_board();
		
		//move();
		checkmate = true;
		turn++;
		printing_board();
	}
}
/**
void move(){
	bool input_valid = false;
	//Select the piece to move
	string start;
	cout << player << ": select a piece" << endl;
	cin >> start;
		
	//Make sure location contains valid piece
	while(!input_valid){
		//Change input if uppercase to lowercase
		if(start[0] >= 65 && start[0] <= 72){
			x[0] += 32;
		}
		if(start[0] >= 97 && start[0] <= 104 && start[1] >= 1 && start[1] <= 8 && ){
			int xCur = start[1]-1;
			int yCur = start[0]-97;
			if(turn%2 = 0 && game_board[xCur][yCur]->piece >= 65 && game_board[xCur][yCur]->piece <= 90){
				//White's turn and location on white piece
				input_valid = true;
			}else if(turn%2 = 1 && game_board[xCur][yCur]->piece >= 97 && game_board[xCur][yCur]->piece <= 122){
				//Black's turn and location on black piece
				input_valid = true;
			}
		}
		//Reenter data if wrong
		if(!input_valid){
			cout << "Invalid location: Please reenter" << endl;
			cin >> start;
		}
	}
	
	input_valid = false;
	//Select the destination
	string end;
	cout << player << ": choose a destination" << endl;
	cin >> end;
	
	//Make sure location does not contain your piece
	
	int xCur, yCur, xTar, yTar;
	xCur = start[1]-1;
	yCur = start[0]-97;
	xTar = end[1]-1;
	yTar = end[0]-97;
	
	move_valid = checkMoveValid(xCur, yCur, xTar, yTar);
	
	
}*/


/**
	Creates the starting chess board
	@param 8x8 array for entire board
	@return void (NULL)
*/
void starting_board()
{
	//Black is lower case, White is upper
	x[0][0] = new Rook(0,0,'r'); 
	x[0][1] = new Knight(0,1,'n');
	x[0][2] = new Bishop(0,2,'b');
	x[0][3] = new Queen(0,3,'q');
	x[0][4] = new King(0,4,'k');
	x[0][5] = new Bishop(0,5,'b');
	x[0][6] = new Knight(0,6,'n');
	x[0][7] = new Rook(0,7,'r');
	x[1][0] = new Pawn(1,0,'p');
	x[1][1] = new Pawn(1,1,'p');
	x[1][2] = new Pawn(1,2,'p');
	x[1][3] = new Pawn(1,3,'p');
	x[1][4] = new Pawn(1,4,'p');
	x[1][5] = new Pawn(1,5,'p');
	x[1][6] = new Pawn(1,6,'p');
	x[1][7] = new Pawn(1,7,'p');
	x[6][0] = new Pawn(6,0,'P');
	x[6][1] = new Pawn(6,1,'P');
	x[6][2] = new Pawn(6,2,'P');
	x[6][3] = new Pawn(6,3,'P');
	x[6][4] = new Pawn(6,4,'P');
	x[6][5] = new Pawn(6,5,'P');
	x[6][6] = new Pawn(6,6,'P');
	x[6][7] = new Pawn(6,7,'P');
	x[7][0] = new Rook(7,0,'R');
	x[7][1] = new Knight(7,1,'N');
	x[7][2] = new Bishop(7,2,'B');
	x[7][3] = new Queen(7,3,'Q');
	x[7][4] = new King(7,4,'K');
	x[7][5] = new Bishop(7,5,'B');
	x[7][6] = new Knight(7,6,'K');
	x[7][7] = new Rook(7,7,'R');

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(i%2 == 0 && j%2 == 0){
				fake_board[i][j] = ":::";
			}else if(i%2 == 1 && j%2 == 1){
				fake_board[i][j] = ":::";
			}else{
				fake_board[i][j] = "   ";
			}
		}
	}
}

/**
	Asks player if wants to play another game_board
	@param 
	@return true or false
*/
bool continue_playing(){
	//Ask if the player wants to play another match
	string input;
	cout << "Do you want to play another game? (Y/N)" << endl;
	cin >> input;
	
	if(input == "Y" || input == "y" || input == "yes"){
		turn = 0;
		return true;
	}else{
		return false;
	}
}

int main()
{
	bool cont = false;
	do{
		
		//Fake board for printing purposes
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(i%2 == 0 && j%2 == 0){
					fake_board[i][j] = ":::";
				}else if(i%2 == 1 && j%2 == 1){
					fake_board[i][j] = ":::";
				}else{
					fake_board[i][j] = "   ";
				}
			}
		}
		
		//Create the starting game board
		starting_board();
		
		//Playing Chess game
		play();
		
		//Remove memory of the game board
		//delete x;
		
		//Ask user if they want to play again
		cont = continue_playing();
	}while(cont);
	
	cout << "Thanks for playing!";
	return 0;
}
