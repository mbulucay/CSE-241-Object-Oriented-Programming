#ifndef HexVector_H
#define HexVector_H

#include "AbstractHex.h"

namespace MBU{

    class HexVector : public AbstractHex{

        public:

            HexVector();
            HexVector(std::string id);
            HexVector(std::string id,int size);
            ~HexVector();

            //wanted functions
            std::string print()const;
            void readFromFile(const std::string &fileName);
            void writeToFile(const std::string &fileName) const;
            void reset();
            void play();
            void play(const Cell &cellobj);
            bool isEnd();
            Cell operator()(int row, int column) const;
            bool operator==(const AbstractHex &board)const;
            Coordinate lastMove()const;
            int numberOfMoves();
            void setSize();
            void setGameType();


            //game functions
            void fillCells();
            void removeCells();
            
            void playGame();
            void playWithFriend();
            void playWithComputer();

            
            void setProperties(std::string id, int boardSize = 0,int gameType = 0, int turn = 0);

            void getCoordinate(int &row, char &column, std::string &command);
            bool checkCoordinate(const int &x, const int &y) const;

            //end game control functions
            void checkUser1();
            void checkUser2();
            void findWay(int x, int y, std::vector<std::vector<int>> &way, CellType user);
            bool boundary(const int &x, const int &y);
            bool passed(std::vector<std::vector<int>> &way, int x, int y);

        private:
            std::vector<std::vector<Cell>> hexCells;
            std::vector<Coordinate> savedMoves;
    };
}
#endif