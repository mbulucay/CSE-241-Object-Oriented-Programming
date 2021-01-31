/*
    Muhammed Bedir ULUCAY
    1901042697
    CSE 241 HomeWork 3
*/

#include <iostream>
#include "lib.hpp"
using namespace std;

vector<Hex> GAMES;              //This is keep all game data Hex vector
int Hex::cellcount = 0;         //This is static varible
Hex CreateBoard(string name){   //This is create a game    
    return Hex(name);
}
///////////////////////////////////////////////////////////////////////////////
int main(){
    string name;
    int operation, index;

    while(true){
        
        cout << "==========================" << endl                        //Here is main menu you can create a game and play an exsiting game
             << " ====== MAIN MENU =======" << endl
             << "1-Create a new game " << endl
             << "2-Play an existing game"<< endl
             << "3-Quit" << endl
             << "Enter the operation : ";
        cin >> operation;
        if(cin.fail()){
            cin.clear();
            cin.ignore(512,'\n');
            cout << "!!!!!!!!!!UNKNOWN COMMAND!!!!!!!!!!" << endl;
        }
        else if(operation == 1){
            cout << "Enter game name : ";
            cin >> name;
            if(CheckName(name))
                GAMES.push_back(CreateBoard(name));                             //If user want to create a new game the game creating using name constructor
            else    
                cout << "\nThis game name already using choose another name " << endl;
        }
        else if(operation == 2){
            cout << "Enter game name you want to play : ";
            cin >> name;
            index = ReturnGameIndex(name);                                      //Returning the game index using game name
            if(index == -1)
                cout << "\nThere is no game called " << name << endl;
            else
                GAMES.at(index).playGame();
        }
        else if(operation == 3){
            cout << "\n !!Have a nice day!!" << endl
                 << "!!!! Come Again !!!!!" << endl
                 << "=======================" << endl;
            exit(1);
        }
        else 
            cout << "!!!!!!!!!!UNKNOWN COMMAND!!!!!!!!!!" << endl;
        
        if(GAMES.size() == 0 && operation != 2) 
            cout << "There are no game" << endl;
        else    
            GameList(); 
        
        if(GAMES.size() > 0)
            cout << "Filled Cells Of All Games : " << GAMES.at(0).getStatic() << endl << endl;       //Here the return the filled cell all game
    }
}          
