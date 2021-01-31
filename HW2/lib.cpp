#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include "lib.h"
using namespace std;
#define max 12
#define maxway 144
#define crdt 2

enum Cell : char{
	empty = '.', user1 = 'x', user2 = 'o'	
};

int GetSize(){
	int s1,s2;
	char cross;

	cout << "Please, Enter the size of board (Ex:6x6) : ";
	cin >> s1 >> cross >> s2; 		 
	if( s1 > 5  && s1 < 13 && s1 == s2 && (cross == 'x' || cross == 'X'))
		return s1;		
	
	else if(cin.fail()){
		cerr << "YOU MADE FAIL ENTERING" << endl
			 << "ENTER ACCORDING TO THE RULE" << endl;
		cin.clear(); cin.ignore(512,'\n');
		return GetSize();
	}
	else{
		cerr << "\n==UNVALID SIZE== " << endl;
		return GetSize();
	}
	cout << "-------------------------------------" << endl;
}

void fillBoard(char board[max][max]){
	for(int i=0; i<max; ++i){
		for(int j=0; j<max; ++j)
			board[i][j] = Cell::empty;
	}
}

void GameType(int &type){
	
	cout << "===========================================" << endl
		 << "-------------WELCOME HEX GAME--------------" << endl
		 << "===========================================" << endl
		 << "        Choose Game Type " << endl
		 << "1 -> Play with your friend" << endl
		 << "2 -> Play with computer" << endl 
		 << "Enter the type : ";
		
		cin >> type;
		if(cin.fail()){
			cin.clear(); cin.ignore(512, '\n');
			cerr << "YOU ENTERED FAIL ENTERING" << endl
				 << "ENTER 1 OR 2 " << endl;
			GameType(type);	 
		}
		else if(type != 1 && type != 2){
			cerr << "\n\nUNVALID GAME TYPE PLEASE ENTER VALID VALUE\n" << endl;
			GameType(type);			
		}
}

void DispBoard(const char board[max][max],const int length){

	char letter = 'a';
	int space = 0;

	for(int i=0; i<length; ++i)
		cout << " " << (char)((int)letter+i);
	cout<< endl;

	for(int i=0; i<length; ++i){
		cout << i+1;
		for(int k=0; k<space; ++k)
			cout << " ";
		for(int j=0; j< length ; ++j)
			cout << board[i][j] << " ";
		cout << endl;
		space++;
	}
	cout << "----------------------------------------" << endl;
}
 
void GetCoordinate(int* x,int* y,string &saved ,string &load){

	//We check the input what it is save,load or it is coordinate
	cout << "Enter cordinate : ";
	string gcrdnt;
	string cm ,fname;
	getline(cin,gcrdnt);
	cm =  gcrdnt.substr(0,4);

	if(cm == "SAVE"){
		auto pos = gcrdnt.find(" ");
		fname = gcrdnt.substr(pos+1,gcrdnt.length());
		saved = fname;
	}			
	else if(cm == "LOAD"){
		auto pos = gcrdnt.find(" ");
		fname = gcrdnt.substr(pos+1,gcrdnt.length());
		load = fname;
	}
	else{
		auto sum = 0;
		*y = static_cast<int>(gcrdnt.at(0)) -17-'0';			//This is set as index coordinate getting from user
		for(char i : gcrdnt){
			if (i >= '0' && i <= '9'){
				sum = sum * 10 + i - '0' - 1;
			}
			if(i == '-'){
				sum = -1;
				break;
			}
		}					
		*x = sum;
	}
}

bool CheckCoordinate(char board[max][max],int x,int y,int size){
	bool check = true;
																		//The cordinate is valid or not 	
	if(x > size-1 || y>size-1 || x < 0 || y < 0 || board[x][y] != Cell::empty)	//checking it
		check = false;
	
	return check;
}

void LoadGame(string fname){
	char board[max][max];
	int size,type,turn;

	fillBoard(board);
	LoadGame(board,size,type,turn,fname);		//Variable set according to the file.txt
	DispBoard(board,size);

	if(type == 1)
		GameWithFriend(board,size,turn);
	else if(type == 2)
		GameWithComp(board,size);
}

void LoadGame(char board[max][max],int &size ,int &type ,int &turn,const string fname){

	string word;		
	char player;
	int x,y;

	ifstream file (fname);
	if(!file.is_open()){
		cerr << "File could not opened program aborted ..." << endl;
		exit(1);
	}

	file >> word >> size;
	file >> word >> type;
	file >> word >> turn;

	while(file >> x >> y >> player)
		board[x][y] = player;

	file.close();
}

void GameSave(char board[max][max],const int &size,const int &type,const int &turn, const string &fname){
		
	ofstream file (fname);			//	Game saving according to the index charracter	Ex: 4 5 x

	file << "Size: " << size << endl;
	file << "Type: " << type << endl;
	file << "Turn: " << turn << endl; 

	for(int i=0; i<size; ++i){
		for(int j=0; j<size; ++j){
			if(board[i][j] != Cell::empty)
				file << i << " " << j << " " << board[i][j] <<endl;
		}
	}

	file.close();

	cout << "Game saved to " << fname << endl;
	cout << "======================" << endl ;
}

void GameWithFriend(char board[max][max], int size,int turn){

	int x,y;
	string saved = " " ,loaded = " ";
	while(true){								//We get coordinate according to the turn
		
		GetCoordinate(&x,&y,saved,loaded);
		if(saved != " "){
		 	GameSave(board,size,1,2,saved);
			GetCoordinate(&x,&y,saved,loaded);
			saved = " ";
		}
		if(loaded != " "){	
			LoadGame(loaded);
			exit(1);
		}
		if(CheckCoordinate(board,x,y,size)){
			if(turn % 2 == 0)
				board[x][y] = Cell::user1;
			else if(turn % 2 == 1)
				board[x][y] = Cell::user2;
		}
		else{
			cerr << "\nThis is not a valid coordinate" << endl;
			continue;
		}
		CheckBlue(board,size);
		CheckRed(board,size);
		DispBoard(board,size);
		turn++;
		saved = " ";
		loaded = " ";
	}
}

void GameWithComp(char board[max][max], int size){

	int  x, y, move = 0;

	decltype(x) cx = -1, cy = -1;
	string saved = " ",loaded = " ";

	while(true){

		GetCoordinate(&x,&y,saved,loaded);
		if(saved != " "){ 	
			GameSave(board,size,2,0,saved);
			GetCoordinate(&x,&y,saved,loaded );
			saved = " ";
		}
		if(loaded != " "){
			LoadGame(loaded);
			exit(1);
		}
		if(CheckCoordinate(board,x,y,size))
			board[x][y] = Cell::user1;
		else{
			cerr << "\nThis is not a valid coordinate" << endl;
			continue;
		}
		CheckBlue(board,size);

		CompMove(board,size,&cx,&cy,move);			//Computers have choosen coordinate 
		cout << "Computers move " << static_cast<char>(cy + 65) << " " << cx+1 << endl;
		board[cx][cy] = 'o';						//'o' putting the game board	
		CheckRed(board,size);
		
		DispBoard(board,size);
		cx = -1;						//Computer before the choose location we need to reset
		cy = -1;						//saved coordinate according to the CompMove function
		saved = " ";
		loaded = " ";
		move++;		
	}
}

void CompMove(char board[max][max],int size,int *x,int *y,int move){

	int cy;
	
	if(board[(size-1)/2][(size-1)/2] == Cell::empty){	//To dominate the center
		*x = (size-1)/2;
		*y = (size-1)/2;
		return;
	}
	else if(board[(size+1)/2][(size+1)/2] == Cell::empty){	//To dominate the center
		*x = (size+1)/2;
		*y = (size+1)/2;
		return;
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  	minstd_rand0 generator (seed);
	
	if(*x < 0){
		
		*x = FindNextFreeRow(board,size,&cy);	//If there is a free row we find it
		if(*x >= 0 && *x < size){				//and using cy we put 'o' next place to put	
			
			if(board[*x][cy] == Cell::empty)
				*y = cy;
			else if(board[*x][cy-1] == Cell::empty)
				*y = cy-1;
			else{
				*y = generator()%size;			//If two down place is full ve put random column
				while(board[*x][*y] != Cell::empty){
					*y = generator()%size;
				}
			}
		}

		else{
			if(move%2 == 1)						//We try to make smarter as using bridge of two point
				SearchBridge(board,size,x,y);
			else{
				while(board[*x][*y] != Cell::empty){	//We are doing quque after fill all row one bridge one random
					*x = generator()%size;
					*y = generator()%size;
				}
			}	
		}
	}
}

int FindNextFreeRow(char board[max][max],int size,int *cy){
	
	bool flag = true;
	int row = -1;
											//Searching free row start 0 -> size one by one 
	for(int i=0; i<size; ++i){
		flag = CheckRow(board[i],size);
		if(flag == false){
			if(i != 0)
				*cy = FindCoulomn(board[i-1],size);
			else
			*cy = size/2;
			row = i;
			i = size;
		}
	}

	return row;
}

int FindCoulomn(char row[max],int size){
	
	int clm;	
	/* This fonction helps us to check row to put next logical  
		position finding 'o' in a row 
	*/
	for(int i = 0; i<size; ++i){
		if(row[i] == Cell::user2){
			clm = i;
			i = size;
		}
	}
	return clm;
}

bool CheckRow(char row[max],int size){
	
	bool result = false;
	/*
		This is checking row is there an 'o' if it is we pass next 
		row in function FindNextFreeRow(...)
	*/
	for (int i = 0; i < size; ++i){
		if(row[i] == Cell::user2){
			result = true;
			i = size;
		}
	}

	return result;
}

void SearchBridge(char board[max][max],int size,int *x,int *y){				//Bridge olusturuyor
	/*

							4   1   3 
						9	  .   .		7		
					12		.	o	.		11
						8	  .	  . 	10
							6	2	5
		It is search two point to connet each other using bridge 
		Some direction has two different connet way in that is happend it choose writing before in code	

	*/
	for(int i=0;i<size && *x<0 && *y<0; ++i){
		for (int j = 0; j < size && *x<0 && *y<0; ++j){
			
			if(board[i][j] == Cell::user2){

				if(board[i-2][j+1] == Cell::user2){				//1
					if(board[i-1][j] == Cell::empty){
						*x = i-1;	*y = j;
					}	
					else if(board[i-1][j+1] == Cell::empty){
						*x = i-1;	*y = j+1;
					}
				}
				else if(board[i+2][j-1] == Cell::user2){		//2
					if(board[i+1][j-1] == Cell::empty){
						*x = i+1;	*y = j-1;
					}
					else if(board[i+1][j] == Cell::empty){
						*x = i+1;	*y = j;
					}
				} 
				else if(board[i-2][j+2] == Cell::user2 && board[i-1][j+1] == Cell::empty){	//3
						*x = i-1;  	*y = j+1;
				}
				else if(board[i-2][j] == Cell::user2 && board[i-1][j] == Cell::empty){		//4
						*x = i-1;	*y = j;
				}
				else if(board[i+2][j-2] == Cell::user2 && board[i+1][j] == Cell::empty){	//5
						*x = i+1;	*y = j;
				}
				else if(board[i+2][j-2] == Cell::user2 && board[i+1][j-1] == Cell::empty){	//6
					*x = i+1;	*y = j-1;
				}
				else if(board[i-1][j+2] == Cell::user2){	//7
					if(board[i-1][j+1] == Cell::empty){
						*x = i-1;	*y = j+1;
					}
					else if(board[i][j+1] == Cell::empty){
						*x = i;	*y = j+1;
					}
				}
				else if(board[i+1][j-2] == Cell::user2){	//8
					if(board[i][j-1] == Cell::empty){
						*x = i;		*y = j-1;
					}
					else if(board[i+1][j-1] == Cell::empty){
						*x = i+1;	*y = j-1;
					}
				}
				else if(board[i-1][j-1] == Cell::user2){	//9
					if(board[i-1][j] == Cell::empty){
						*x = i-1;	*y = j;
					}
					else if(board[i][j-1] == Cell::empty){
						*x = i;		*y = j-1;
					}
				}
				else if(board[i+1][j+1] == Cell::user2){	//10
					if(board[i][j+1] == Cell::empty){
						*x = i;		*y = j+1;
					}
					else if(board[i+1][j] == Cell::empty){
						*x = i+1;	*y = j;
					}
				}
				else if(board[i][j+2] == Cell::user2 && board[i][j+1] == Cell::empty){	//11
					*x = i;		*y = j+1;
				}
				else if(board[i][j-2] == Cell::user2 && board[i][j-1] == Cell::empty){	//12
					*x = i;		*y = j-1;	
				}
			}
		}
	}
}

void CheckRed(char board[max][max], int size){

	int way[maxway][crdt] = {0};							//This function is arabasamak 
	int counter = 0;
	for(int i=0; i<size; ++i){							//It is searching 'o' in the first row 
		if(board[0][i] == Cell::user2)
			RecFindWay(board, way, size, 0, i, counter,Cell::user2);
	}
}

void CheckBlue(char board[max][max],int size){

	int way[maxway][crdt] = {0};							//This function is arabasamak 
	int counter = 0;
	for(int i=0; i<size; ++i){							//It is searching 'x' in the first clm 
		if(board[i][0] == Cell::user1)
			RecFindWay(board, way, size, i, 0, counter,Cell::user1);
	}
}

void RecFindWay(char board[max][max],int way[maxway][crdt],int size,int x,int y,int counter,char player){

	if((x == size-1 && board[x][y] == player && player == Cell::user2) ){ 	//It is stopping if the player 2 (o) is reach the top to bottom
		way[counter][0] = x;
		way[counter][1] = y;
		DisplayWinnigBoard(way,board,counter,size,player);
		return;
	}
	if(y==size-1 && board[x][y] == player && player == Cell::user1){		//It is stopping if the player 1 (x) is reach the left to right
		way[counter][0] = x;
		way[counter][1] = y;
		DisplayWinnigBoard(way,board,counter,size,player);
		return;
	}

	if(CheckSides(board ,way, counter,size, x, y,player) == false){		//If we cannot find a path to winning.This stop recursive
		way[counter][0] = x;
		way[counter][1] = y;
		return;
	}

	way[counter][0] = x;		 
	way[counter][1] = y;		

	if(board[x-1][y+1] == player && SearchInWay(way, counter, x-1, y+1) == false){		//right up 1
		RecFindWay(board, way, size, x-1, y+1, counter+1,player);
	}
	if(board[x-1][y] == player   && SearchInWay(way, counter, x-1, y) == false){  		//left up 2
		RecFindWay(board, way, size, x-1, y, counter+1,player);
	}
	if(board[x][y-1] == player   && SearchInWay(way, counter, x, y-1) == false){      	//left
		RecFindWay(board, way, size, x, y-1, counter+1,player);
	}
	if(board[x+1][y-1] == player && SearchInWay(way, counter, x+1, y-1) == false){   	//left down 4
		RecFindWay(board, way, size, x+1, y-1, counter+1,player);
	}
	if(board[x+1][y] == player   && SearchInWay(way, counter, x+1, y) == false){	 	//right down 5
		RecFindWay(board, way, size, x+1, y, counter+1,player);
	}
	if(board[x][y+1] == player   && SearchInWay(way, counter, x, y+1) == false){     	//right 6
		RecFindWay(board, way, size ,x ,y+1, counter+1,player);
	}
}

bool CheckSides(char board[max][max] ,int passedway[maxway][crdt],int counter,int size,int x, int y,char player){	//Bir noktanin etrafindaki noktalari kontrol ediyor

	bool result = true;
	char rival;
	
	if(player == Cell::user2)
		rival = Cell::user1;
	if(player == Cell::user1)
		rival = Cell::user2;

	//This function helps us to find out end of the way.It checks six side of a point as rules.

	//	 If we passed index                              or      '.'              or       rival char         or        out of board 
	if( (SearchInWay(passedway, counter,x-1,y+1) == true || board[x-1][y+1] == Cell::empty|| board[x-1][y+1] == rival || x-1<0 || y+1>size-1) &&
		(SearchInWay(passedway, counter,x-1,y)   == true || board[x-1][y] == Cell::empty  || board[x-1][y] == rival   || x-1<0)   &&
		(SearchInWay(passedway, counter,x,y-1)   == true || board[x][y-1] == Cell::empty  || board[x][y-1] == rival   || y-1<0) &&
		(SearchInWay(passedway, counter,x+1,y-1) == true || board[x+1][y-1] == Cell::empty|| board[x+1][y-1] == rival || x+1>size-1 || y-1<0) &&
		(SearchInWay(passedway, counter,x+1,y)   == true || board[x+1][y] == Cell::empty  || board[x+1][y] == rival   || x+1>size-1)   &&
		(SearchInWay(passedway, counter,x,y+1)   == true || board[x][y+1] == Cell::empty  || board[x][y+1] == rival   || y+1>size-1))
	{
		result = false;
	}

	return result;
}

bool SearchInWay(int passedway[maxway][crdt], int counter, int x, int y){
	int result = false;
																// If we pass the cordinate x,y the it return true
	for(int i=0; i<counter; ++i){								// to dont pass again the location
		if(passedway[i][0] == x && passedway[i][1] == y){
			result = true;
			i = counter;
		}
	}
	return result;
}

void DisplayWinnigBoard(int way[maxway][crdt],char board[max][max],int counter,int size,char player){

	int x,y;
	cout << "\n=======================================" << endl				// It is print board as Capital Letter in index which way has  
		 << "=======!!!!!!WINNING BOARD!!!!!!=======" << endl				
		 << "=======================================" << endl;
	for(int i=0; i< counter+1; ++i){
		x = way[i][0];
		y = way[i][1];
		board[x][y] -= ' ';			//This is make x->X  o->O
	}
	DispBoard(board,size);
	cout << "=========================================" << endl
		 << "      THE WINNER IS " << static_cast<char>(player-' ') << endl		
		 << "=========================================" << endl << endl;
	exit(1);
}