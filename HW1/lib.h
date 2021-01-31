#ifndef LIB_H
#define LIB_H 

#include <string>
#define max 12
#define maxway 144
#define crdt 2
using namespace std;

int GetSize();
bool CheckSize(string str,int* size);
void fillBoard(char board[max][max]);
void GameType(int *type);
void DispBoard(char board[max][max],int length);
void GetCoordinate(int* x,int* y);
bool CheckCoordinate(char board[max][max],int x,int y,int size);
void CoordinateWarn();

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

