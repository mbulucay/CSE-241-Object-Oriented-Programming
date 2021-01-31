#include <iostream>
#include "HexVector.h"

int main(){
	
	MBU::Cell c1(3,2,MBU::CellType::user1);
	MBU::Cell c2(4,2,MBU::CellType::user1);
	MBU::Cell c3(5,1,MBU::CellType::user1);
	MBU::Cell c4(2,4,MBU::CellType::user1);

	MBU::HexVector vGame("vetorGame",6);
	std::cout << "Game Created\n";
	std::cout << vGame.print();

	std::cout << "Calling lastMove() function before doing any move\n";
	try{
		MBU::Coordinate lmove = vGame.lastMove();
		std::cout << "Last move for the game : " << char(lmove.column+'A') << " " << lmove.row+1 << std::endl;
	}catch(const std::out_of_range& e){
            std::cout << "There is no last move  : \n" << e.what() << std::endl;
	}

	vGame.play(c1);
	vGame.increaseTurn();
	vGame.play();
	vGame.increaseTurn();
	std::cout << vGame.print();
	std::cout << "=====================\n\n";

	vGame.play(c2);
	vGame.increaseTurn();
	vGame.play();
	vGame.increaseTurn();
	std::cout << vGame.print();
	std::cout << "=====================\n\n";

	std::cout << "Writing file \n"; 
	vGame.writeToFile("vectorSavedGame");
	std::cout << "=====================\n\n";

	std::cout << "Make two move after saving\n";
	vGame.play(c3);
	vGame.increaseTurn();
	vGame.play();
	vGame.increaseTurn();
	std::cout << vGame.print();
	std::cout << "=====================\n\n";


	std::cout << "Reading again file after make two move\n";
	vGame.readFromFile("vectorSavedGame");
	std::cout << vGame.print();
	std::cout << "=====================\n\n";

	std::cout << "isEnd : " << vGame.isEnd() << std::endl;
	std::cout << "=====================\n\n";

	MBU::Cell vCell = vGame(4,2);
	std::cout << "vGame(4,2) index operator() vCell.getRow() << vCell.getClm() :  " << vCell.getRow() << ", " << vCell.getClm() << "\n";
	std::cout << "=====================\n\n";

	std::cout << "Number of moves (vGame.numberOfMoves()) : " << vGame.numberOfMoves() << std::endl;
	std::cout << "=====================\n\n";

	std::cout << "Calling again vGame.lastMove() function\n";
	try{
		MBU::Coordinate lmove = vGame.lastMove();
		std::cout << "Last move for the game : " << char(lmove.column+'A') << " " << lmove.row+1 << std::endl;
	}catch(const std::out_of_range& e){
            std::cout << "There is no last move  : \n" << e.what() << std::endl;
	}
	std::cout << "=====================\n\n";

	std::cout << "Create new game to compare\n";
	MBU::HexVector vGame2("vetorGame2",7);
	std::cout << vGame2.print();

	vGame2.play(c4);
	vGame2.increaseTurn();
	vGame2.play();
	vGame2.increaseTurn();
	std::cout << "After make move for second game\n";
	std::cout << vGame2.print();
	std::cout << "=====================\n\n";

	std::cout << "Compare Two Game\n";

	std::cout << "First Game to compare\n";
	std::cout << vGame.print();

	std::cout << "Second Game to compare\n";
	std::cout << vGame2.print();

	std::cout << "\nOperator == : ";
	if(vGame == vGame2){
		std::cout << "TRUE\n";
	}else{
		std::cout << "FALSE\n";
	}
	std::cout << std::endl;
	return 0;
}