#ifndef AbstractHex_H
#define AbstractHex_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>
#include <vector>
#include <deque>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <stdexcept>	
#include <new>

#include "Cell.h"

namespace MBU{

    class AbstractHex{

        public:
            
            virtual ~AbstractHex(){}
            virtual std::string print()const = 0;
            virtual void readFromFile(const std::string &fileName) = 0;
            virtual void writeToFile(const std::string &fileName) const = 0;
            virtual void reset() = 0;
            virtual void play() = 0;
            virtual void play(const Cell &cellobj) = 0;
            virtual bool isEnd() = 0;
            virtual Cell operator()(int, int) const = 0;
            virtual bool operator==(const AbstractHex &board) const = 0;
            virtual Coordinate lastMove() const= 0;
            virtual int numberOfMoves() = 0;

            //  Board Functions
            virtual void fillCells() = 0;

            //Game Functions
            virtual void playGame() = 0;
            virtual void playWithFriend() = 0;
            virtual void playWithComputer() = 0;

            //  GET Functions
            int getSize()const {return boardSize;}
            int getTurn()const {return turn;}
            bool getFinish()const {return finish;}
            CellType getWinner()const {return winner;}
            int getType()const {return gameType;}
            std::string getId()const {return id;}

            //  SET Functions
            virtual void setSize() = 0;
            void putSize(const int boardSize){
                this->boardSize = boardSize;
            }

            virtual void setGameType() = 0;
            void putGameType(const int gameType) { 
                this->gameType = gameType; 
            }

            void setFinish(const bool finish) { this->finish = finish; }
            void setWinner(const CellType& winner){this->winner = winner;}

            void increaseTurn(){turn++;}

            static int getNumberOfAllGames() { return numberOfAllHexGame; }
            void increaseStatic() { numberOfAllHexGame++; }
            void decreasecStatic() { numberOfAllHexGame--; }

        protected:                                  //Common properties of all game
        
            static int numberOfAllHexGame;
            std::string id;
            int boardSize, gameType, turn;
            CellType winner = CellType::empty;
            bool finish = false;

    };
}
#endif
