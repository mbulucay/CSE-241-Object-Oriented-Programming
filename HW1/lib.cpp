#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include "lib.h"
using namespace std;
#define max 12
#define maxway 144
#define crdt 2

bool CheckSize(string str,int *size){
	
	bool check = true;						//We take a string from user 
	int first = 1, second = 1;				//then we check it the valid or nat valid
	
	if(str.length() == 3){

		first = static_cast<int>(str.at(0)) -'0';			//Tek basakli sayilar icin	6x6
		second = static_cast<int>(str.at(2))-'0';
		
		if(first != second || first < 6 || first > 12 || str.at(1) != 'x')
			check = false;
	}
	else if(str.length() == 5){								//Cift basamakli sayilar icin	10x10
		first = (static_cast<int>(str.at(0)) -'0')*10;
		first +=(static_cast<int>(str.at(1)) - '0');
		second *=(static_cast<int>(str.at(3)) -'0')*10;
		second+= (static_cast<int>(str.at(4))-  '0'); 

		if(first != second || first < 6 || first > 12 || str.at(2) != 'x')
			check = false;
	}												//If the inut is not valid then function return false
	else
		check = false;
	*size = first;
	
	return check;	
}

int GetSize(){
	
	string str;
	int size;
	
	cout << "===========================================" << endl
		 << "-----------WELCOME MY HEX GAME-------------" << endl
		 << "===========================================" << endl
		 << "Please, Enter the size of board  : ";
	getline(cin,str);

	while(CheckSize(str,&size) == false){
		cout << "Please,Enter a valid value between 6x6-12x12" << endl
			 << "Enter the size of board  : ";
		getline(cin,str);
	}
	cout << "-------------------------------------------" << endl;
	
	return size;
}

void fillBoard(char board[max][max]){
	for(int i=0; i<max; ++i){
		for(int j=0; j<max; ++j)
			board[i][j] = '.';
	}
}

void GameType(int *type){
	
	cout << "         Game Type\n";
	cout << "1 -> Play with your friend" << endl
		 << "2 -> Play with computer" << endl
		 << "Please, Enter Game Type (1 or 2) : ";
	cin >> *type;
	while(*type !=1 && *type != 2){
		cout << "Please select a valid value" << endl
			 << "Enter Game Type (1 or 2) : ";
		cin >> *type;
	}
	cout << "-------------------------------------" << endl;
}

void DispBoard(char board[max][max],int length){

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
}

void CoordinateWarn(){
		cout << "\nThis is not a valid coordinate" << endl
			 << "Please enter a valid coordinate(Ex: C 5) : ";
}

void GetCoordinate(int* x,int* y){

	string gcrdnt;
	getline(cin,gcrdnt);

	while(gcrdnt.length() < 3 || gcrdnt.length() > 4){
		CoordinateWarn();
		getline(cin,gcrdnt);
	}

	*y = static_cast<int>(gcrdnt.at(0)) -17-'0';			//This is set as index coordinate getting from user
	if(gcrdnt.length() == 3)
			*x = static_cast<int>(gcrdnt.at(2))-1 -'0';
	else if(gcrdnt.length() == 4){
		*x = static_cast<int>(gcrdnt.at(2)) -'0';
		*x*=10 + static_cast<int>(gcrdnt.at(3))-'0';
		*x-=1;
	}
}

bool CheckCoordinate(char board[max][max],int x,int y,int size){
	bool check = true;
																		//The cordinate is valid or not 	
	if(x > size-1 || y>size-1 || board[x][y] != '.' || x < 0 || y < 0)	//checking it
		check = false;
	
	return check;
}

void CompMove(char board[max][max],int size,int *x,int *y,int move){

	int cy;
	
	if(board[(size-1)/2][(size-1)/2] == '.'){	//To dominate the center
		*x = (size-1)/2;
		*y = (size-1)/2;
		return;
	}
	else if(board[(size+1)/2][(size+1)/2] == '.'){	//To dominate the center
		*x = (size+1)/2;
		*y = (size+1)/2;
		return;
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  	minstd_rand0 generator (seed);
	
	if(*x < 0){
		
		*x = FindNextFreeRow(board,size,&cy);	//If there is a free row we find it
		if(*x >= 0 && *x < size){				//and using cy we put 'o' next place to put	
			
			if(board[*x][cy] == '.')
				*y = cy;
			else if(board[*x][cy-1] == '.')
				*y = cy-1;
			else{
				*y = generator()%size;			//If two down place is full ve put random column
				while(board[*x][*y] != '.'){
					*y = generator()%size;
				}
			}
		}

		else{
			if(move%2 == 1)						//We try to make smarter as using bridge of two point
				SearchBridge(board,size,x,y);
			else{
				while(board[*x][*y] != '.'){	//We are doing quque after fill all row one bridge one random
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
		if(row[i] == 'o'){
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
		if(row[i] == 'o'){
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
			
			if(board[i][j] == 'o'){

				if(board[i-2][j+1] == 'o'){				//1
					if(board[i-1][j] == '.'){
						*x = i-1;	*y = j;
					}	
					else if(board[i-1][j+1] == '.'){
						*x = i-1;	*y = j+1;
					}
				}
				else if(board[i+2][j-1] == 'o'){		//2
					if(board[i+1][j-1] == '.'){
						*x = i+1;	*y = j-1;
					}
					else if(board[i+1][j] == '.'){
						*x = i+1;	*y = j;
					}
				} 
				else if(board[i-2][j+2] == 'o' && board[i-1][j+1] == '.'){	//3
						*x = i-1;  	*y = j+1;
				}
				else if(board[i-2][j] == 'o' && board[i-1][j] == '.'){		//4
						*x = i-1;	*y = j;
				}
				else if(board[i+2][j-2] == 'o' && board[i+1][j] == '.'){	//5
						*x = i+1;	*y = j;
				}
				else if(board[i+2][j-2] == 'o' && board[i+1][j-1] == '.'){	//6
					*x = i+1;	*y = j-1;
				}
				else if(board[i-1][j+2] == 'o'){	//7
					if(board[i-1][j+1] == '.'){
						*x = i-1;	*y = j+1;
					}
					else if(board[i][j+1] == '.'){
						*x = i;	*y = j+1;
					}
				}
				else if(board[i+1][j-2] == 'o'){	//8
					if(board[i][j-1] == '.'){
						*x = i;		*y = j-1;
					}
					else if(board[i+1][j-1] == '.'){
						*x = i+1;	*y = j-1;
					}
				}
				else if(board[i-1][j-1] == 'o'){	//9
					if(board[i-1][j] == '.'){
						*x = i-1;	*y = j;
					}
					else if(board[i][j-1] == '.'){
						*x = i;		*y = j-1;
					}
				}
				else if(board[i+1][j+1] == 'o'){	//10
					if(board[i][j+1] == '.'){
						*x = i;		*y = j+1;
					}
					else if(board[i+1][j] == '.'){
						*x = i+1;	*y = j;
					}
				}
				else if(board[i][j+2] == 'o' && board[i][j+1] == '.'){	//11
					*x = i;		*y = j+1;
				}
				else if(board[i][j-2] == 'o' && board[i][j-1] == '.'){	//12
					*x = i;		*y = j-1;	
				}
			}
		}
	}
}


void CheckRed(char board[max][max], int size){

	for(int i=0; i<size; ++i){							//It is searching 'o' in the first row 
		if(board[0][i] == 'o')
			IsThereWay(board,size,0,i,'o');
	}
}

void CheckBlue(char board[max][max],int size){

	for(int i=0; i<size; ++i){							//It is searching 'x' in the first clm 
		if(board[i][0] == 'x')
			IsThereWay(board,size,i,0,'x');
	}
}

void IsThereWay(char board[max][max], int size, int x, int y, char player){

	int way[maxway][crdt] = {0};							//This function is arabasamak 
	int counter = 0;										//Before find way because it has some var we will need way and index counter
	RecFindWay(board, way, size, x, y, counter,player);
}

void RecFindWay(char board[max][max],int way[maxway][crdt],int size,int x,int y,int counter,char player){

	if((x == size-1 && board[x][y] == player && player == 'o') ){ 	//It is stopping if the player 2 (o) is reach the top to bottom
		way[counter][0] = x;
		way[counter][1] = y;
		DisplayWinnigBoard(way,board,counter,size,player);
		return;
	}
	if(y==size-1 && board[x][y] == player && player == 'x'){		//It is stopping if the player 1 (x) is reach the left to right
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

	/*	
		We keep the way of index that we are passed.This helps us to do two thing
		Firstly we can make turn the capital letter (x->X)(o->O)
		Secondly we prevent to be infinity recursive.When we try to find winning path it prevent to pass same index
				Ex:		o     This shape can easily create infinit recursive
					   o o	
	*/

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
	
	if(player == 'o')
		rival = 'x';
	if(player == 'x')
		rival = 'o';

	//This function helps us to find out end of the way.It checks six side of a point as rules.

	//	 If we passed index                              or      '.'              or       rival char         or        out of board 
	if( (SearchInWay(passedway, counter,x-1,y+1) == true || board[x-1][y+1] == '.'|| board[x-1][y+1] == rival || x-1<0 || y+1>size-1) &&
		(SearchInWay(passedway, counter,x-1,y)   == true || board[x-1][y] == '.'  || board[x-1][y] == rival   || x-1<0)   &&
		(SearchInWay(passedway, counter,x,y-1)   == true || board[x][y-1] == '.'  || board[x][y-1] == rival   || y-1<0) &&
		(SearchInWay(passedway, counter,x+1,y-1) == true || board[x+1][y-1] == '.'|| board[x+1][y-1] == rival || x+1>size-1 || y-1<0) &&
		(SearchInWay(passedway, counter,x+1,y)   == true || board[x+1][y] == '.'  || board[x+1][y] == rival   || x+1>size-1)   &&
		(SearchInWay(passedway, counter,x,y+1)   == true || board[x][y+1] == '.'  || board[x][y+1] == rival   || y+1>size-1))
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
