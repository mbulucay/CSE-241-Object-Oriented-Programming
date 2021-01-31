#ifndef globalLib_H
#define globalLib_H

#include "AbstractHex.h"
#include "Cell.h"
#include "HexVector.h"
#include "HexArray1D.h"
#include "HexAdapter.hpp"

namespace MBU{

    void validSequence(std::vector<AbstractHex*> &GAMES);                               //Want a game to check is game valid or not
    bool validSequence(AbstractHex* &game);

    int getOperation();         //Main Menu

    void addGame(std::vector<AbstractHex *> &GAMES);                                    //add game which one you choose game

    void addVectorGame(std::vector<AbstractHex *> &GAMES);      
    void addArray1DGame(std::vector<AbstractHex *> &GAMES);
    void addAdapterVectorGame(std::vector<AbstractHex *> &GAMES);
    void addAdapterDequeGame(std::vector<AbstractHex *> &GAMES);

    bool checkGameId(const std::vector<AbstractHex *> &GAMES,const std::string id);     // prevent get same id for two different  game (each game has to be spesific id) 
    void gameList(const std::vector<AbstractHex *> &GAMES);                             //printing all games id
    void playGame(std::vector<AbstractHex *> &GAMES);                                   //open the game for choosen one

    void compareTwoGame(std::vector<AbstractHex *> &GAMES);                             //comparing game

    void closeProgram();

}

#endif