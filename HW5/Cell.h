#ifndef Cell_H
#define Cell_H

namespace MBU{

    enum CellType : char{
        empty = '.',
        user1 = 'x',    user2 = 'o',
        win1 = 'X',    win2 = 'O'
    };

    class Coordinate{
        public:
            int row, column;
    };

    class Cell{
        
        public:
            Cell();
            Cell(int row,int column);
            Cell(int row, int column, CellType gcell = CellType::empty);

            CellType getCell()const;
            int getRow() const;
            int getClm() const;
            void setCellType(CellType cellType);

            void setCoordinate(int gx, int gy, CellType type);

        private:
            Coordinate coordinate;
            CellType cell;
    };
}
#endif