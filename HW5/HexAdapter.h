#ifndef HexAdapter_H
#define HexAdapter_H_

#include "AbstractHex.h"

namespace MBU{

    template <template <typename ...> class T>
    class HexAdapter : public AbstractHex{

        public:

            HexAdapter();
            HexAdapter(std::string id);
            HexAdapter(std::string id,int boardSize);
            ~HexAdapter();

            std::string print()const;
            void readFromFile(const std::string &fileName);
            void writeToFile(const std::string &fileName) const;
            void reset();           //reset board(size and id are protecting)
            void play();
            void play(const Cell &cellobj);
            bool isEnd();
            Cell operator()(int x,int y)const;
            bool operator==(const AbstractHex &board) const;
            Coordinate lastMove()const;
            int numberOfMoves();

            void fillCells();           //Getting place from ram and fill with empty cell
            void removeCells();         //removing board (all properties)

            void playGame();
            void playWithFriend();
            void playWithComputer();

            void setSize();
            void setGameType();

            void setProperties(std::string id, int boardSize = 0,int gameType = 0, int turn = 0);

            bool checkCoordinate(const int &x, const int &y) const;

            void checkUser1();
            void checkUser2();
            void findWay(int x, int y, T<T<int>> &way, CellType user);
            bool passed(T<T<int>> &way, int x, int y);
            bool boundary(const int &x, const int &y);

            void getCoordinate(int &row, char &column, std::string &command);

            private : 
                T<T<Cell>> hexCells;
                T<Coordinate> savedMoves;

    };
}

#endif