#ifndef HexArray1D_H
#define HexArray1D_H

#include "AbstractHex.h"

namespace MBU{

    class HexArray1D : public AbstractHex{

        public:
            
            HexArray1D();
            HexArray1D(std::string id);
            HexArray1D(std::string id, int size);

            HexArray1D(const HexArray1D& obj);
            ~HexArray1D();
            HexArray1D& operator=(const HexArray1D& obj);

            //wanted functions
            std::string print()const;
            void readFromFile(const std::string &fileName);
            void writeToFile(const std::string &fileName) const;
            void reset();               //protecting id and size
            void play();
            void play(const Cell &cellobj);
            bool isEnd();
            Cell operator()(int row, int column) const;
            bool operator==(const AbstractHex &board) const;
            Coordinate lastMove()const;
            int numberOfMoves();
            void setSize();
            void setGameType();


            void fillCells();           //get space from ram for cells 
            void removeCells();         //all properties removing include id and size

            void playGame();
            void playWithFriend();
            void playWithComputer();

            void setProperties(std::string id, int boardSize = 0,int gameType = 0, int turn = 0);

            void getCoordinate(int &index, std::string &command);
            bool checkCoordinate(const int &index) const;

            //end game control functions'
            void checkUser1();
            void checkUser2();
            void findWay(int x, int y, std::vector<std::vector<int>> &way, CellType user);
            bool boundary(const int &x, const int &y);
            bool passed(std::vector<std::vector<int>> &way, int x, int y);

        private:
            Cell *hexCells;
            std::vector<Coordinate> savedMoves;
    };

}//end of namespace MBU

#endif //HexArray1D