/*
	Muhammed Bedir ULUCAY
	1901042697
*/
#include <iostream>
#include "lib.h"
using namespace std;
#define max 12

int main(){

	char board[max][max];
	int gameType = 0,
		 size = 0,turn = 0;
	string str;

	GameType(gameType);		
	fillBoard(board);
	size = GetSize();
	getline(cin,str);

	DispBoard(board,size);	 
	if(gameType == 1)
		GameWithFriend(board,size,turn);
	else if(gameType == 2)
		GameWithComp(board,size);
	
	return 0;
}