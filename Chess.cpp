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

//Global Variables
const int CHESS_SIZE = 8;
int turn = 0;
string player;

//Gameboard variables
Piece* x[8][8]; //Actual board
char y[8][8]; //Virtual board to check valid movements
string fake_board[8][8]; //Used for printing

//Game methods (in order)
void play();
void move(string player);
void valid_location(int &xCur, int &yCur);
void location(int &xCur, int &yCur, int &xTar, int &yTar);
void move_copy(int xCur, int yCur, int xTar, int yTar);
bool checkMoveValid(int &xCur, int &yCur, int &xTar, int &yTar);
void findking(int player, int &kingrow, int &kingcol);
bool kingcheck(int player);
bool horizontal(int row, int col, int kingrow, int kingcol);
bool vertical(int row, int col, int kingrow, int kingcol);
bool diagonal(int row, int col, int kingrow, int kingcol);
bool checkmate();
void promote();
void starting_board();
void printing_board();
bool continue_playing();

/**
	Regulates entire game until checkmate
*/
void play(){
	//Starting response
	cout << endl;
	cout << "Welcome! Before you start your game please note" << endl;
	cout << "That the common notation is letter then number" << endl;
	cout << "Such as b6 all other input would be invalid thank you." << endl;
	
	//Testing if checkmate in game
	bool bcheckmate = false;
	while(!bcheckmate){
		//Set whose turn it is
		if(turn%2 == 0)
			player = "White";
		else
			player = "Black";
		
		//Moving pieces
		move(player);
		
		//Checking if moved piece checks the king
		if(kingcheck(turn)){
			//Checking if checkmate
			if(!checkmate()){
				cout << player << " checked the king" << endl;
			}else{
				printing_board();
				cout << player << " has checkmated the king !!!" << endl;
				bcheckmate = true;
			}
		}
		//Change the turn
		turn++;
	}
}

/**
	Moving the pieces each turn
	@param string player (state player's turn)
*/
void move(string player){
	int xCur = -1, yCur = -1, xTar = -1, yTar = -1;
	bool move_valid = false;
	
	//Printing board each iteration
	cout << endl << player << "'s move:" << endl;
	printing_board();
	
	//Finds the location of piece and target destination
	location(xCur, yCur, xTar, yTar);
	
	//Check if move is a legal move (reject if not)
	if(!checkMoveValid(xCur, yCur, xTar, yTar)){
		cout << "Not A Valid Move" << endl;
		//Recalls move to keep iteration code
		move(player);
		return;
	}
	
	//Creates a virtual board of all the pieces
	move_copy(xCur, yCur, xTar, yTar);
	
	//Checks if your king is in check AFTER movement
	if(kingcheck(turn+1)){
		cout << "Your King is in Check You Bonobo" << endl;
		//Recalls move until valid
		move(player);
		return;
	}
	
	//Checks if piece is castling
	if((x[xCur][yCur]->get_piece() == 'k' || x[xCur][yCur]->get_piece() == 'K')
		&& abs(yTar-yCur) == 2){
		if(yTar > yCur){
			//King side castle
			x[xTar][yTar] = x[xCur][yCur]; //king moved
			x[xTar][yTar-1] = x[xCur][yCur+3];
			x[xCur][yCur] = NULL;
			x[xCur][yCur+3] = NULL; 
		}else{
			//Queen side castle
			x[xTar][yTar] = x[xCur][yCur]; //king moved
			x[xTar][yTar+1] = x[xCur][yCur-4];
			x[xCur][yCur] = NULL;
			x[xCur][yCur-4] = NULL; 
		}
	}else{
		//Ordinary piece movve
		x[xTar][yTar] = x[xCur][yCur];
		x[xCur][yCur] = NULL;
	}
	
	//Check for promotion of pawns
	promote();
	
	//After move set the piece to move
	x[xTar][yTar]->set_moved();
}

/**
	Ensures the input is valid location
	@param int &x
	@param int &y
*/
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

/**
	Find the current location and target destination
	@param int& xCur (references the xCur in move)
	@param int& yCur (likewise)
	@param int& xTar (likewise)
	@param int& yTar (likewise)
*/
void location(int &xCur, int &yCur, int &xTar, int &yTar){
	//Select the piece to move
	string start;
	cout << player << ": select a piece" << endl;
	cin >> start;
	
	//Convert string input into row and column
	yCur = start[0]-97;
	xCur = (start[1]-56)*-1;
	
	//Check if input location is on the 8x8 board
	valid_location(xCur, yCur);
	
	//Check if it is turn's player piece
	if(turn%2 == 0){
		//White turn
		while(x[xCur][yCur] == NULL || islower(x[xCur][yCur]->get_piece())){
			cout << "Not your piece. Please enter another location" << endl;
			cin >> start;
			//Renters valids and rechecks the points
			yCur = start[0]-97;
			xCur = (start[1]-56)*-1;
			valid_location(xCur, yCur);
		}
	}else{
		//Black turn
		while(x[xCur][yCur] == NULL || isupper(x[xCur][yCur]->get_piece())){
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
	
	//Make sure final destination is valid
	valid_location(xTar, yTar);
}

/**
	Creates the virutal board for testing before actual movement
	@param int xCur (intial location)
	@param int yCur (inital location)
	@param int xTar (desired location)
	@param int yTar (desired location)
*/
void move_copy(int xCur, int yCur, int xTar, int yTar){
	//Creates virtual array the characters on chess board
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(x[i][j] != NULL)
			{
				y[i][j] = x[i][j]->get_piece();
			}
			//Not an available piece
			else
			{
				y[i][j] = ' ';
			}
		}
	}
	
	//Moves the piece virtually for testing
	y[xTar][yTar] = y[xCur][yCur];
	y[xCur][yCur] = ' ';
}

/**
	Find the current location and target destination
	@param int& xCur (references the xCur in move)
	@param int& yCur (likewise)
	@param int& xTar
	@param int& yTar
	@return True 	 (move is legal)
*/
bool checkMoveValid(int &xCur, int &yCur, int &xTar, int &yTar){
	//Grabs the targetpiece
	char piece = x[xCur][yCur]->get_piece();
	
	//If selected is same location
	if(xCur == xTar && yCur == yTar)
	{
		return false;
	}
	
	//Check if destination contains own player's piece
	if(x[xTar][yTar] != NULL && 
		(((islower(x[xTar][yTar]->get_piece()) && islower(x[xCur][yCur]->get_piece())) 
		|| (isupper(x[xTar][yTar]->get_piece()) && isupper(x[xCur][yCur]->get_piece())))))
	{	
		return false;
	}
	
	//Rook piece
	if(piece == 'r' || piece == 'R')
	{
		return (horizontal(xCur, yCur, xTar, yTar) || vertical(xCur, yCur, xTar, yTar));
	}
	//Bishop piece
	else if(piece == 'b' || piece == 'B')
	{
		return (diagonal(xCur, yCur, xTar, yTar));
	}
	//Knight piece
	else if(piece == 'n' || piece == 'N')
	{
		//Location in a 'L' shape
		if(abs(xCur-xTar) == 2 && abs(yCur-yTar) == 1)
		{
			return true;
		}
		else if(abs(xCur-xTar) == 1 && abs(yCur-yTar) == 2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//Queen piece
	else if(piece == 'q' || piece == 'Q'){
		return(horizontal(xCur, yCur, xTar, yTar) || vertical(xCur, yCur, xTar, yTar)
			|| diagonal(xCur, yCur, xTar, yTar));
	}
	//King piece
	else if(piece == 'K' || piece == 'k')
	{
		//Make sure only moved 1 square away at a time
		if(abs(xTar-xCur) == 1 && abs(yTar-yCur) == 0)
		{
			return true;
		}
		else if(abs(xTar-xCur) == 0 && abs(yTar-yCur) == 1)
		{
			return true;
		}
		else if(abs(xTar-xCur) == 1 && abs(yTar-yCur) == 1)
		{
			return true;
		}
		//Testing for castle availability
		else if(!x[xCur][yCur]->get_moved() && abs(yTar-yCur) == 2)
		{
			//King side Castle
			if(yTar > yCur){	
				//Make sure corner piece is a rook that never moved
				if(x[xCur][yCur+3] != NULL && (x[xCur][yCur+3]->get_piece() == 'r' 
				|| x[xCur][yCur+3]->get_piece() == 'R') && !x[xCur][yCur+3]->get_moved())
				{
					//Testing if any pieces obstruct castle
					if(!horizontal(xCur, yCur, xTar, yTar)){
						return false;
					}
					//Testing if king gets checked while moving to castle
					move_copy(xCur, yCur, xTar, yCur+1);
					if(kingcheck(turn+1)){
						return false;
					}
					move_copy(xCur, yCur, xTar, yCur+2);
					if(kingcheck(turn+1)){
						return false;
					}
					//Satisfy all requirements of Castling
					return true;
				}
				else
				{
					return false;
				}
			}
			//Queen side castle
			else if (yTar < yCur)
			{				
				//Same as King side
				if(x[xCur][yCur-4] != NULL && (x[xCur][yCur-4]->get_piece() == 'r' 
				|| x[xCur][yCur-4]->get_piece() == 'R') && !x[xCur][yCur-4]->get_moved())
				{
					if(!horizontal(xCur, yCur, xTar, yTar))
					{
						return false;
					}
					move_copy(xCur, yCur, xTar, yCur-1);
					if(kingcheck(turn+1))
					{
						return false;
					}
					move_copy(xCur, yCur, xTar, yCur-2);
					if(kingcheck(turn+1))
					{
						return false;
					}
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		//Not a valid movement
		else
		{
			return false;
		}
	}
	//Pawn Piece
	else{
		int two = 2;
		int one = 1;
		
		//Change variables if white's pawn
		if(isupper(piece))
		{
			two = -2;
			one = -1;
		}
		
		//Moved more than 2 spaces
		if(abs(xTar - xCur) > 2)
		{
			return false;
		}
		//Same column
		if(yCur == yTar)
		{
			//Piece obstructing
			if(x[xTar][yTar] != NULL)
			{	
				return false;
			}
			//Test pawn only moving 1 space forward
			if(xTar != xCur + one && xTar != xCur + two)
			{
				return false;
			}
			//Pawn already moved (can't move 2 spaces anymore)
			if(xTar == xCur + two && x[xCur][yCur]->get_moved())
			{
				return false;
			}
		}
		//Capturing a piece
		else if(yTar == yCur + 1 || yTar == yCur - 1)
		{
			//Test if location movement is a 1 square diagonal
			if(xTar != xCur + one)
			{
				return false;
			}
			//No piece at the targeted diagonal
			if(x[xTar][yTar] == NULL)
			{
				return false;
			}
		}
		//Not a valid pawn movement
		else
		{
			return false;
		}
	}
	//All requirements met
	return true;
}

/**
	Find the location of specific player's kingcheck
	@param int player (targeted player)
	@param int& row (reference kingrow location) 
	@param int& col (reference kingcol location)
*/
void findking(int player, int &row, int &col){
	char king = 'K';
	//Player Black
	if(player % 2 == 1)
	{
		king = 'k';
	}
	//Looping Virtual board to find location of king
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(y[i][j] != ' ' && y[i][j] == king){
				row = i;
				col = j;
				return;
			}
		}
	}
}

/**
	Testing if opposite player (off turn's player) is in check
	@param int player (targeted player)
	@return True	  (king being checked by a piece)
*/
bool kingcheck(int player){
	//White's turn and black's king
	char oppking = 'K';
    char king = 'k';
    char rook = 'R';
    char knight = 'N';
    char bishop = 'B';
    char queen = 'Q';
    char pawn = 'P';
    
	//Change if black's turn, king is white's
    if (player % 2 == 1){
		oppking = 'k';
        king = 'K';
        rook = 'r';
        knight = 'n';
        bishop = 'b';
        queen = 'q';
        pawn = 'p';
    }

	//Find location of opposite player's king
	int kingrow, kingcol;
	findking(player+1, kingrow, kingcol);
    
	//cout << "King is at " << kingrow << " " << kingcol << endl;
	
    //Rook
    for (int row = 0; row < 8; row ++)
	{
        for (int col = 0; col < 8; col ++)
		{
            if (y[row][col] == rook)
			{
				//If horizontal || vertical has no pieces obstructing
                if (horizontal(row, col, kingrow, kingcol) 
					|| vertical(row, col, kingrow, kingcol))
				{
                    return true;
                }
            }
        }
    }
    
    //Knight
	//Testing all 8 possible squares for knight
    if (kingrow < 7 && kingcol < 6 && y[kingrow+1][kingcol+2] == knight)
	{
		return true;
    }
    else if (kingrow < 7 && kingcol > 1 && y[kingrow+1][kingcol-2] == knight)
	{
		return true;
    }
    else if (kingrow > 0 && kingcol < 6 && y[kingrow-1][kingcol+2] == knight)
	{
		return true;
    }
    else if (kingrow > 0 && kingcol > 1 && y[kingrow-1][kingcol-2] == knight)
	{
		return true;
    }
    else if (kingrow < 6 && kingcol < 7 && y[kingrow+2][kingcol+1] == knight)
	{
		return true;
    }
    else if (kingrow < 6 && kingcol > 0 && y[kingrow+2][kingcol-1] == knight)
	{
		return true;
    }
    else if (kingrow > 1 && kingcol <7 && y[kingrow-2][kingcol+1] == knight)
	{
		return true;
    }
    else if (kingrow > 1 && kingcol > 0 && y[kingrow-2][kingcol-1] == knight)
	{
		return true;
    }

    //Bishop
    for (int row = 0; row < 8; row ++)
	{
        for (int col = 0; col < 8; col ++)
		{
            if (y[row][col] == bishop)
			{
				//Testing if diagonal has no pieces obstructing
                if (diagonal(row, col, kingrow, kingcol))
				{
					return true;
                }
            }
        }
    }
    
    //Pawn
    for (int row = 0; row < 8; row ++)
	{
        for (int col = 0; col < 8; col ++)
		{
			//Testing if king is 1 space away
            if (y[row][col] == pawn && abs(row-kingrow) == 1)
			{
                if (diagonal(row, col, kingrow, kingcol))
				{
                    return true;
                }
            }
        }
    }
    
    //Queen
    for (int row = 0; row < 8; row ++)
	{
        for (int col = 0; col < 8; col ++)
		{
            if (y[row][col] == queen)
			{
				//Testing if horizontal, vertical or diagonal has no piece
                if (diagonal(row, col, kingrow, kingcol) 
					|| horizontal(row, col, kingrow, kingcol) 
					|| vertical(row, col, kingrow, kingcol))
				{
					return true;
                }
            }
        }
    }
    
	int row = kingrow;
	int col = kingcol;
	//King
	//Testing if opponent king is in the way of King's movement
	if(row < 7 && y[row+1][col] == oppking)
	{
		return true;
	}else if(row < 7 && col < 7 && y[row+1][col+1] == oppking)
	{
		return true;
	}else if(row < 7 &&  col > 0 && y[row+1][col-1] == oppking)
	{
		return true;
	}else if (col < 7 && y[row][col+1] == oppking)
	{
		return true;
	}else if(col > 0 && y[row][col-1] == oppking)
	{
		return true;
	}else if(row > 0 && y[row-1][col] == oppking)
	{
		return true;
	}else if(row > 0 && col < 7 && y[row-1][col+1] == oppking)
	{
		return true;
	}else if(row > 0 &&  col > 0 && y[row-1][col-1] == oppking)
	{
		return true;
	}
	
    return false;
}

/**
	Find if any piece is between the path of 2 pieces horizontally
	@param int row 		(inital location)
	@param int col
	@param int kingrow	(king's location)
	@param int kingcol
	@return True 		(No piece in between)
*/
bool horizontal(int row, int col, int kingrow, int kingcol){
    int start_y = col;
    int end_y = kingcol;
    //Flip position if backwards
	if(start_y > end_y)
	{
        start_y = kingcol;
        end_y = col;
    }
	//Not on same row
    if(row != kingrow)
	{
        return false;
    }
    else 
	{
		//Check if pieces are between (in virtual board)
        for(int i = start_y+1; i < end_y; i++)
		{
            if(y[row][i] != ' ')
			{
                return false;
            }
        }
    }
    return true;
}

/**
	Find if any piece is between the path of 2 pieces vertically
	@param int row 		(inital location)
	@param int col
	@param int kingrow	(king's location)
	@param int kingcol
	@return True 		(No piece in between)
*/
bool vertical(int row, int col, int kingrow, int kingcol){
    int start_x = row;
    int end_x = kingrow;
	//Flip position if backwards
    if(start_x > end_x)
	{
        start_x = kingrow;
        end_x = row;
    }
	//Not on same col
    if(col != kingcol)
	{
        return false;
    }
	else
	{
		//Check if pieces are between (virtual board)
        for(int i = start_x+1; i < end_x; i++){
            if(y[i][col] != ' '){
                return false;
            }
        }
    }
    return true;
}

/**
	Find if any piece is between the path of 2 pieces diagonally
	@param int row 		(inital location)
	@param int col
	@param int kingrow	(king's location)
	@param int kingcol
	@return True 		(No piece in between)
*/
bool diagonal(int row, int col, int kingrow, int kingcol){
    int x_d = 1;
    int y_d = 1;
    //Flip if target and destination backwards
	if(row - kingrow < 0)
	{
        x_d = -1;
    }
    if(col - kingcol < 0)
	{
        y_d = -1;
    }
	
	//Checking if diagonal
    if((col - kingcol) == 0 
	|| (double)abs(row - kingrow)/(double)abs(col - kingcol) != 1)
	{
        return false;
    }
	else
	{
		//Check if pieces are between (virtual board)
        for(int i = 1; i < abs(row - kingrow); i++)
		{
            if(y[kingrow +(i * x_d)][kingcol +(i * y_d)] != ' ')
			{
                return false;
            }
        }
    }
    return true;
}

/**
	Testing all possible moves for opponent to get out of check
	@return true (checkmated)
	@return false (possible movement exists)
*/
bool checkmate(){
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			//Testing is detected piece is opposite piece
			if(x[i][j] != NULL && 
				((isupper(x[i][j]->get_piece()) && turn%2 == 1) ||
				(islower(x[i][j]->get_piece()) && turn%2 == 0)))
			{
				for(int r = 0; r < 8; r++)
				{
					for(int c = 0; c < 8; c++)
					{
						//Test if possible valid move
						if(checkMoveValid(i, j, r, c))
						{
							//Move on virtual board
							move_copy(i, j, r, c);
							//Test if opposite's player not in check
							if(!kingcheck(turn))
							{
								//cout << x[i][j]->get_piece() << "from" << i << " " << j << endl << "to" << r << " " << c <<endl;
								return false;
							}
						}							
					}
				}
			}			
		}
	}
	return true;
}

/**
	Changes pawn to another piece when reaches opposite end
*/
void promote(){
    string answer;
    char rook = 'R';
    char knight = 'N';
    char bishop = 'B';
    char queen = 'Q';
    char pawn = 'P';
    int row = 0;
    
	//Flip if blacks turn & black piece hit white edge
    if (turn % 2 == 1){
        rook = 'r';
        knight = 'n';
        bishop = 'b';
        queen = 'q';
        pawn = 'p';
        row = 7;
    }
    
	//Testing location of pawn
    for (int i = 0; i < 8; i++){
        if (y[row][i] == pawn){
			//Deletes pawn
			x[row][i] == NULL;
			//Priming Read
            cout << "What piece would you like to promote to?" << endl;
            cin >> answer;
			//Enter until valid input
            while (answer != "queen" && answer != "bishop" &&
                   answer != "knight" && answer != "rook"){
                cout << "Enter a valid piece (e.g. queen, rook)" << endl;
                cin >> answer;
            }
			//Creates new variable
            if (answer == "queen"){
                x[row][i] = new Queen(row,i,queen);
            }
            if (answer == "rook"){
                x[row][i] = new Rook(row,i,rook);
            }
            if (answer == "bishop"){
                x[row][i] = new Bishop(row,i,bishop);
            }
            if (answer == "knight"){
                x[row][i] = new Knight(row,i,knight);
            }
        }
    }
}


/**
	Creates the starting board every new game
*/
void starting_board(){
	//Clear the entire board
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			x[i][j] = NULL;
		}
	}
	//Create inital gameboard
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

	//Create string board for printing
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(i%2 == 0 && j%2 == 0){
				fake_board[i][j] = ":::"; //Black square
			}else if(i%2 == 1 && j%2 == 1){
				fake_board[i][j] = ":::";
			}else{
				fake_board[i][j] = "   "; //White square
			}
		}
	}
}

/**
	Formats the chess board to print into console
*/
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
				//Access fake board to print black/white square
				cout << fake_board[row][col];
			}
			
		}
		cout << "|" << endl;
	}
	//Chessboard format
	cout << "  +------------------------+" << endl;
	cout << "    a  b  c  d  e  f  g  h" << endl;
}

/**
	Asks player if wants to play another game_board
	@return bool (True if yes to continue playing)
*/
bool continue_playing(){
	//Ask if the player wants to play another match
	string input;
	cout << "Do you want to play another game? (Y/N)" << endl;
	cin >> input;
	
	//Asks for the input
	if(input == "Y" || input == "y" || input == "yes"){
		turn = 0;
		return true;
	}else{
		return false;
	}
}

int main(){
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
        
        //Ask user if they want to play again
        cont = continue_playing();
    }while(cont);
    cout << "Thanks for playing!";
    return 0;
}