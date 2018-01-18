#include "Piece.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>

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
void valid_location(int &xCur, int &yCur);
void valid_dest(int xCur, int yCur, int &xTar, int &yTar);
void starting_board();
bool horizontal();
bool vertical();
bool diagonal();
bool kingcheck();
void printing_board();
void checkValid();
bool continue_playing();

void play(){
	//DO EVERYTHING
	cout << endl;
	cout << "Welcome! Before you start your game please note" << endl;
	cout << "That the common notation is letter then number" << endl;
	cout << "Such as b6; all other input is invalid, thank you." << endl;
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
		if(turn == 10){
			checkmate = true;
		}
		cout << "kingcheck: " << kingcheck() << endl;
	}
}

// Loops until user inputs a valid location
void valid_location(int &xLoc, int &yLoc){
	string temp;
	//Ensures location on array
	while(xLoc < 0 || xLoc > 7 || yLoc < 0 || yLoc > 7){
		cout << "Invalid location. Please reenter another." << endl;
		cin >> temp;
		yLoc = temp[0]-97;
		xLoc = (temp[1]-56)*-1;
	}
	
}

void valid_dest(int xCur, int yCur, int &xTar, int &yTar)
{
	string temp;
	Piece* piece = x[xCur][yCur];
	while((xTar == xCur && yTar == yCur)
			/*|| (islower(x[xTar][yTar]->get_piece()) && islower(piece->get_piece())) 
			|| (isupper(x[xTar][yTar]->get_piece()) && isupper(piece->get_piece()))*/
			|| !piece->checkValid(xTar, yTar, x)
		)
			

	{
		cout << "Invalid destination. Please reenter another." << endl;
		cin >> temp;
		yTar = temp[0]-97;
		xTar = (temp[1]-56)*-1;
	}
}

// Loops until user selects a valid starting location and ending location
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
	valid_dest(xCur,yCur,xTar,yTar);
}

void move(string player){
	int xCur = -1, yCur = -1, xTar = -1, yTar = -1;
	
	location(xCur, yCur, xTar, yTar);
	
	x[xTar][yTar] = x[xCur][yCur];
	x[xCur][yCur] = NULL;
	
	x[xTar][yTar]->set_moved();

	
}

//segmentation fault somewhere in horizontal, vertical, diagonal

bool horizontal(Piece* start, Piece* end){
    bool clear = true;
    int start_x = start->get_xPos();
    int end_x = end->get_xPos();
    if(start->get_xPos() > end->get_xPos()){
        start_x = end->get_xPos();
        end_x = start->get_xPos();
    }
    if(start->get_yPos() != end->get_yPos()){
        clear = false;
    }
    else {
        for(int i = start_x+1; i < end_x; i++){
            if(x[i][start->get_yPos()] != NULL){
                clear = false;
            }
        }
    }
    return clear;
}

bool vertical(Piece* start, Piece* end){
    bool clear = true;
    int start_y = start->get_yPos();
    int end_y = end->get_yPos();
    if(start->get_yPos() > end->get_yPos()){
        start_y = end->get_yPos();
        end_y = start->get_yPos();
    }
    if(start->get_xPos() != end->get_xPos()){
        clear = false;
    }
    else {
        for(int i = start_y+1; i < end_y; i++){
            if(x[i][start->get_yPos()] != NULL){
                clear = false;
            }
        }
    }
    return clear;
    
}

bool diagonal(Piece* start, Piece* end){
    bool clear = true;
    int x_d = 1;
    int y_d = 1;
    if(start->get_xPos()-end->get_xPos() < 0){
        x_d = -1;
    }
    if(start->get_yPos()-end->get_yPos() < 0){
        y_d = -1;
    }
    if(abs(start->get_xPos()-end->get_xPos()) != abs(start->get_yPos()-end->get_yPos())){
        clear = false;
    }
    else{
        for(int i = 1; i < start->get_xPos()-end->get_xPos(); i ++){
            if(x[start->get_xPos()+(i*x_d)][start->get_yPos()+(i*y_d)] != NULL){
                clear = false;
            }
        }
    }
    return clear;
}

bool kingcheck(){
    char king = 'k';
    char rook = 'R';
    char knight = 'N';
    char bishop = 'B';
    char queen = 'Q';
    char pawn = 'P';
    
    if (turn % 2 == 1){
        king = 'K';
        rook = 'r';
        knight = 'n';
        bishop = 'b';
        queen = 'q';
        pawn = 'p';
    }


    char a[8][8];
    int kingrow = 0;
    int kingcol = 0;
    for (int j = 0; j < 8; j ++){
        for (int k = 0; k < 8; k ++){
            if(x[j][k] != NULL){
                a[j][k] = x[j][k]->get_piece();
                if(a[j][k] == king){
                    kingrow = j;
                    kingcol = k;
                }
            }
        }
    }
    cout << "not segmented yet!" << endl;
    // rook
    for (int row = 0; row < 8; row ++){
        for (int col = 0; col < 8; col ++){
            if (a[row][col] == rook){
                if (horizontal(x[row][col], x[kingrow][kingcol]) || vertical(x[row][col], x[kingrow][kingcol])){
                    return true;
                }
            }
        }
    }
    
    // knight
    if (kingrow < 7 && kingcol < 7){
        if (a[kingrow+1][kingcol+2] == knight){
            return true;
        }
    }

    if (kingrow < 7 && kingcol >0){
        if (a[kingrow+1][kingcol-1] == knight){
            return true;
        }
    }
    
    if (kingrow > 0 && kingcol < 6){
        if (a[kingrow-1][kingcol+2] == knight){
            return true;
        }
    }
    
    if (kingrow > 0 && kingcol > 1) {
        if (a[kingrow-1][kingcol-2] == knight){
            return true;
        }
    }
    
    if (kingrow < 6 && kingcol < 7){
        if (a[kingrow+2][kingcol+1] == knight){
            return true;
        }
    }

    if (kingrow < 6 && kingcol > 0){
        if (a[kingrow+2][kingcol-1] == knight){
            return true;
        }
    }

    if (kingrow > 1 && kingcol <7){
        if (a[kingrow-2][kingcol+1] == knight){
            return true;
        }
    }

    if (kingrow > 1 && kingcol > 0){
        if (a[kingrow-2][kingcol-1] == knight){
            return true;
        }
    }

    // bishop
    for (int row = 0; row < 8; row ++){
        for (int col = 0; col < 8; col ++){
            if (a[row][col] == bishop){
                if (diagonal(x[row][col], x[kingrow][kingcol])){
                    return true;
                }
            }
        }
    }
    
    // pawn
    for (int row = 0; row < 8; row ++){
        for (int col = 0; col < 8; col ++){
            if (a[row][col] == pawn && abs(row-kingrow) == 1){
                if (diagonal(x[row][col], x[kingrow][kingcol])){
                    return true;
                }
            }
        }
    }
    
    // queen
    for (int row = 0; row < 8; row ++){
        for (int col = 0; col < 8; col ++){
            if (a[row][col] == queen){
                if (diagonal(x[row][col], x[kingrow][kingcol]) || horizontal(x[row][col], x[kingrow][kingcol]) || vertical(x[row][col], x[kingrow][kingcol])){
                    return true;
                }
            }
        }
    }
    
    return false;
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
	x[7][6] = new Knight(7,6,'N');
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
