#include <iostream>
#include "HexArray1D.h"

int main(){

	MBU::Cell c1(3,2,MBU::CellType::user1);
	MBU::Cell c2(4,2,MBU::CellType::user1);
	MBU::Cell c3(5,1,MBU::CellType::user1);
	MBU::Cell c4(2,4,MBU::CellType::user1);

	MBU::HexArray1D ArrayGame("HexArray1DGame",6);
	std::cout << "Game Created\n";
	std::cout << ArrayGame.print();


	std::cout << "Calling lastMove() function before doing any move\n";
	try{
		MBU::Coordinate lmove = ArrayGame.lastMove();
		std::cout << "Last move for the game : " << char(lmove.column+'A') << " " << lmove.row+1 << std::endl;
	}catch(const std::out_of_range& e){
            std::cout << "There is no last move  : \n" << e.what() << std::endl;
	}


	ArrayGame.play(c1);
	ArrayGame.increaseTurn();
	ArrayGame.play();
	ArrayGame.increaseTurn();
	std::cout << ArrayGame.print();
	std::cout << "=====================\n\n";

	ArrayGame.play(c2);
	ArrayGame.increaseTurn();
	ArrayGame.play();
	ArrayGame.increaseTurn();
	std::cout << ArrayGame.print();
	std::cout << "=====================\n\n";

	std::cout << "Writing file \n"; 
	ArrayGame.writeToFile("Array1DSavedGame");
	std::cout << "=====================\n\n";

	std::cout << "Make two move after saving\n";
	ArrayGame.play(c3);
	ArrayGame.increaseTurn();
	ArrayGame.play();
	ArrayGame.increaseTurn();
	std::cout << ArrayGame.print();
	std::cout << "=====================\n\n";


	std::cout << "Reading again file after make two move\n";
	ArrayGame.readFromFile("Array1DSavedGame");
	std::cout << ArrayGame.print();
	std::cout << "=====================\n\n";

	std::cout << "isEnd : " << ArrayGame.isEnd() << std::endl;
	std::cout << "=====================\n\n";

	MBU::Cell ACell = ArrayGame(4,2);
	std::cout << "ArrayGame(4,2) index operator() ACell.getRow() << vCell.getClm() :  " << ACell.getRow() << ", " << ACell.getClm() << "\n";
	std::cout << "=====================\n\n";

	std::cout << "Number of moves (ArrayGame.numberOfMoves()) : " << ArrayGame.numberOfMoves() << std::endl;
	std::cout << "=====================\n\n";

	std::cout << "Calling again ArrayGame.lastMove() function\n";
	try{
		MBU::Coordinate lmove = ArrayGame.lastMove();
		std::cout << "Last move for the game : " << char(lmove.column+'A') << " " << lmove.row+1 << std::endl;
	}catch(const std::out_of_range& e){
            std::cout << "There is no last move  : \n" << e.what() << std::endl;
	}
	
	std::cout << "=====================\n\n";


	std::cout << "Create new game to compare\n";
	MBU::HexArray1D ArrayGame2("ArrayGame2",7);
	std::cout << ArrayGame2.print();

	ArrayGame2.play(c4);
	ArrayGame2.increaseTurn();
	ArrayGame2.play();
	ArrayGame2.increaseTurn();
	std::cout << "After make move for second game\n";
	std::cout << ArrayGame2.print();
	std::cout << "=====================\n\n";

	std::cout << "Compare Two Game\n";

	std::cout << "First Game to compare\n";
	std::cout << ArrayGame.print();

	std::cout << "Second Game to compare\n";
	std::cout << ArrayGame2.print();

	std::cout << "\nOperator == : ";
	if(ArrayGame == ArrayGame2){
		std::cout << "TRUE\n";
	}else{
		std::cout << "FALSE\n";
	}
	std::cout << std::endl;

	return 0;
}