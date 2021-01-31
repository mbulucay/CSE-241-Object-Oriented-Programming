#ifndef LIB_H_
#define LIB_H_ 

#include <string>
#define max 12
#define maxway 144
#define crdt 2
using namespace std;

int GetSize();
void fillBoard(char board[max][max]);
void GameType(int &type);
void DispBoard(const char board[max][max],const int length);
void GetCoordinate(int* x,int* y,string &saved,string &load);
bool CheckCoordinate(char board[max][max],int x,int y,int size);

void GameSave(char board[max][max],const int &size,const int &type,const int &turn,const string &fname);
void LoadGame(string fname = "notfound");
void LoadGame(char board[max][max],int &size,int &type,int &turn,string fname = "notfound");

void GameWithFriend(char board[max][max], int size,int turn);
void GameWithComp(char board[max][max], int size);

void CompMove(char board[max][max],int size,int *x,int *y,int move);
void SearchBridge(char board[max][max],int size,int *x,int *y);
int FindNextFreeRow(char board[max][max],int size,int *cy);
bool CheckRow(char row[max],int size);
int FindCoulomn(char row[max],int size);

void CheckRed(char board[max][max], int size);
void CheckBlue(char board[max][max],int size);
void IsThereWay(char board[max][max], int size, int x, int y,char player);
void RecFindWay(char board[max][max],int way[maxway][crdt],int size,int x,int y,int counter,char player);
bool CheckSides(char board[max][max] ,int passedway[maxway][crdt],int counter,int size,int x, int y, char player);
bool SearchInWay(int passedway[maxway][crdt], int counter, int x, int y);
void DisplayWinnigBoard(int way[maxway][crdt],char board[max][max],int counter,int size,char player);

#endif