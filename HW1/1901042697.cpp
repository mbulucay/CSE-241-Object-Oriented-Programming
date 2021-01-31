/*
	Muhammed Bedir ULUCAY
	1901042697
*/
#include <iostream>
#include <string>
#include "lib.h"
using namespace std;
#define max 12

void GameWithFriend(char board[max][max], int size);
void GameWithComp(char board[max][max], int size);

int main() {

	char board[max][max];		//We got the base variable here
	int gameType,size;
	string str;
	
	size = GetSize();
	GameType(&gameType);		//We determine the size of board, type of game
	fillBoard(board);
	DispBoard(board,size);
	getline(cin,str);

	cout << "---------------------------" << endl
		 << "Player 1's character is 'x'" << endl
		 << "Computer's character is 'o'" << endl
		 << "---------------------------" << endl;

	if(gameType == 1)
		GameWithFriend(board,size);
	else if(gameType == 2)
		GameWithComp(board,size);

	return 0;
}

void GameWithFriend(char board[max][max], int size){

	int x,y;
	bool checkcoor;

	while(true){					
		/*
			Here,getting coordinate player 1 & player 2.After get coordinate,checking
			the can win or not after that we display the board of hex game
		*/
		cout << "Player 1(x) enter coordinat : ";
		GetCoordinate(&x,&y);
		checkcoor = CheckCoordinate(board,x,y,size);

		if(checkcoor)
			board[x][y] = 'x';
		else{
			while(checkcoor == false){
				CoordinateWarn();
				GetCoordinate(&x,&y);
				checkcoor = CheckCoordinate(board,x,y,size);
			}
			board[x][y] = 'x';
		}
		CheckBlue(board,size);
		DispBoard(board,size);

		cout << "Player 2(o) enter coordinat : ";
		GetCoordinate(&x,&y);
		checkcoor = CheckCoordinate(board,x,y,size);
		if(checkcoor)
			board[x][y] = 'o';
		else{
			while(checkcoor == false){
				CoordinateWarn();
				GetCoordinate(&x,&y);
				checkcoor = CheckCoordinate(board,x,y,size);
			}
			board[x][y] = 'o';
		}
		CheckRed(board,size);
		DispBoard(board,size);
	}
}

void GameWithComp(char board[max][max], int size){

	int  x, y, move = 0,
		 cx = -1, cy = -1;
	bool checkcoor;

	while(true){

		cout << "Player 1(x) enter coordinat : ";				//Here player doing his move
		GetCoordinate(&x,&y);
		checkcoor = CheckCoordinate(board,x,y,size);

		if(checkcoor)
			board[x][y] = 'x';

		else{
			while(checkcoor == false){
				CoordinateWarn();
				GetCoordinate(&x,&y);
				checkcoor = CheckCoordinate(board,x,y,size);
			}
			board[x][y] = 'x';
		}
		CheckBlue(board,size);

		CompMove(board,size,&cx,&cy,move);			//Computers have choosen coordinate 
		board[cx][cy] = 'o';						//'o' putting the game board	
		CheckRed(board,size);
		
		DispBoard(board,size);

		cx = -1;						//Computer before the choose location we need to reset
		cy = -1;						//saved coordinate according to the CompMove function
		move++;		
	}
}

