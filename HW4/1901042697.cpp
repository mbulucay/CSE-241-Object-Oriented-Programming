/*
    Muhammed Bedir ULUCAY
    1901042697 
    CSE 241    Homework 4
*/

#include <iostream>
#include "lib.hpp"

int Hex::count = 0;     //static variable
int main(){

    std::vector<Hex*> GAMES;     
    int operation;

    while(true){

        operation = GetOperation();
        switch(operation){
            case 1:     PushGAME(GAMES);               break;
            case 2:     PlayAnExistingGame(GAMES);     break;
            case 3:     CompareTwoGames(GAMES);        break;
            case 4:     CloseProgram();                break;
            default:
                std::cout << "\n!!!!!!!!!!UNKNOWN COMMAND!!!!!!!!!!\n";
        }
        GameList(GAMES);
        
        if (GAMES.size() > 0)   //Print filled cell of all created games
            std::cout << "Filled Cells Of All Games : " << GAMES[0]->getStatic() << "\n\n";
    }
    return 0;
}