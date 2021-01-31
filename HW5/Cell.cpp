#include "Cell.h"
namespace MBU{

Cell::Cell()
{               }

Cell::Cell(int row, int column){
    coordinate.row = row;
    coordinate.column = column;
}

Cell::Cell(int row, int column, CellType cell){
    coordinate.row = row;
    coordinate.column = column;
    this->cell = cell;
}

void Cell::setCellType(CellType cellType){
    cell = cellType;
}

CellType Cell::getCell() const { return cell; }

int Cell::getRow() const { return coordinate.row; }

int Cell::getClm() const { return coordinate.column; };

void Cell::setCoordinate(int gx, int gy, CellType type){
    coordinate.row = gx;
    coordinate.column = gy;
    cell = type;
}

}