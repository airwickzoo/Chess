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
string player;

//Game board variable
Piece* x[8][8];
string fake_board[8][8];

//Game methods
void play();
void move(string player);
void location(int &xCur, int &yCur, int &xTar, int &yTar);
void valid_location(int &x, int &y);
void starting_board();
void printing_board();
bool continue_playing();

void play(){
	//DO EVERYTHING
	cout << endl;
	cout << "Welcome! Before you start your game please note" << endl;
	cout << "That the common notation is letter then number" << endl;
	cout << "Such as b6 all other input would be invalid thank you." << endl;
	cout << endl << "White is indicated by <> and uppercase letters while " << endl;
	cout << "Black is indicated by [] and lowercase letters" << endl;
	
	bool checkmate = false;
	while(!checkmate){
		if(turn%2 == 0)
			player = "White";
		else
			player = "Black";
		cout << player << "'s move:" << endl;
		printing_board();
		
		move(player);
		turn++;
		if(turn == 5){
			checkmate = true;
		}
	}
}
void valid_location(int &x, int &y){
	string temp;
	
	//Ensures location on array
	while(x < 0 || x > 7 || y < 0 || y > 7){
		cout << "Invalid location. Please reenter another." << endl;
		cin >> temp;
		y = temp[0]-97;
		x = (temp[1]-56)*-1;
	}
}

void location(int &xCur, int &yCur, int &xTar, int &yTar){
	//Select the piece to move
	string start;
	cout << player << ": select a piece" << endl;
	cin >> start;
	yCur = start[0]-97;
	xCur = (start[1]-56)*-1;
	
	valid_location(xCur, yCur);
	//Check if it is turn's player piece
	if(turn%2 == 0){
		//White players
		while(x[xCur][yCur] == NULL || x[xCur][yCur]->get_piece()  < 65 || x[xCur][yCur]->get_piece() > 90){
			cout << "Not your piece. Please enter another location" << endl;
			cin >> start;
			yCur = start[0]-97;
			xCur = (start[1]-56)*-1;
			valid_location(xCur, yCur);
		}
	}else{
		while(x[xCur][yCur] == NULL || x[xCur][yCur]->get_piece()  < 97 || x[xCur][yCur]->get_piece() > 122){
			cout << "Not your piece. Please enter another location" << endl;
			cin >> start;
			yCur = start[0]-97;
			xCur = (start[1]-56)*-1;
			valid_location(xCur, yCur);
		}
	}
	
	//Select the destination
	string end;
	cout << player << ": choose a destination" << endl;
	cin >> end;
	
	//Changing location to array notation (x=row, y=col)
	yTar = end[0]-97;
	xTar = (end[1]-56)*-1;
	
	valid_location(xTar, yTar);
	
}

void move(string player){
	int xCur = -1, yCur = -1, xTar = -1, yTar = -1;
	
	location(xCur, yCur, xTar, yTar);
	
	//moved
	x[xTar][yTar] = x[xCur][yCur];
	x[xCur][yCur] = NULL;
	
	//move_valid = checkMoveValid(xCur, yCur, xTar, yTar);
	
}


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

void printing_board(){
	cout << "  +------------------------+" << endl;
	for(int row = 0; row < 8; row++){
		cout << 8-row << " |";
		for(int col = 0; col < 8; col++){
			if(x[row][col] != NULL){
				char piece = x[row][col]->get_piece();
				if(piece >= 65 && piece <= 90){
					//Check if piece is white's piece
					cout << "<" << piece << ">";
				}else if(piece >= 97 && piece <= 122){
					//Black's piece
					cout << "[" << piece << "]";
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
		
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				x[i][j] = NULL;
			}
		}
		
		//Ask user if they want to play again
		cont = continue_playing();
	}while(cont);
	
	cout << "Thanks for playing!";
	return 0;
}
