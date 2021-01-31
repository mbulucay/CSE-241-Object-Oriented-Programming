#include <iostream>
#include "HexAdapter.hpp"

int main(){

	MBU::Cell c1(3,2,MBU::CellType::user1);
	MBU::Cell c2(4,2,MBU::CellType::user1);
	MBU::Cell c3(5,1,MBU::CellType::user1);
	MBU::Cell c4(2,4,MBU::CellType::user1);


	MBU::HexAdapter<std::vector> AdapVecGame("AdapVecGame",6);
	std::cout << "Game Created\n";
	std::cout << AdapVecGame.print();

	std::cout << "Calling lastMove() function before doing any move\n";
	try{
		MBU::Coordinate lmove = AdapVecGame.lastMove();
		std::cout << "Last move for the game : " << char(lmove.column+'A') << " " << lmove.row+1 << std::endl;
	}catch(const std::out_of_range& e){
            std::cout << "There is no last move  : \n" << e.what() << std::endl;
	}

	AdapVecGame.play(c1);
	AdapVecGame.increaseTurn();
	AdapVecGame.play();
	AdapVecGame.increaseTurn();
	std::cout << AdapVecGame.print();
	std::cout << "=====================\n\n";

	AdapVecGame.play(c2);
	AdapVecGame.increaseTurn();
	AdapVecGame.play();
	AdapVecGame.increaseTurn();
	std::cout << AdapVecGame.print();
	std::cout << "=====================\n\n";

	std::cout << "Writing file \n"; 
	AdapVecGame.writeToFile("AdaptedvectorSavedGame");
	std::cout << "=====================\n\n";

	std::cout << "Make two move after saving\n";
	AdapVecGame.play(c3);
	AdapVecGame.increaseTurn();
	AdapVecGame.play();
	AdapVecGame.increaseTurn();
	std::cout << AdapVecGame.print();
	std::cout << "=====================\n\n";


	std::cout << "Reading again file after make two move\n";
	AdapVecGame.readFromFile("AdaptedvectorSavedGame");
	std::cout << AdapVecGame.print();
	std::cout << "=====================\n\n";

	std::cout << "isEnd : " << AdapVecGame.isEnd() << std::endl;
	std::cout << "=====================\n\n";

	MBU::Cell vCell = AdapVecGame(4,2);
	std::cout << "AdapVecGame(4,2) index operator() vCell.getRow() << vCell.getClm() :  " << vCell.getRow() << ", " << vCell.getClm() << "\n";
	std::cout << "=====================\n\n";

	std::cout << "Number of moves (AdapVecGame.numberOfMoves()) : " << AdapVecGame.numberOfMoves() << std::endl;
	std::cout << "=====================\n\n";

	std::cout << "Calling again AdapVecGame.lastMove() function\n";
	try{
		MBU::Coordinate lmove = AdapVecGame.lastMove();
		std::cout << "Last move for the game : " << char(lmove.column+'A') << " " << lmove.row+1 << std::endl;
	}catch(const std::out_of_range& e){
            std::cout << "There is no last move  : \n" << e.what() << std::endl;
	}
	std::cout << "=====================\n\n";


	std::cout << "Create new game to compare\n";
	MBU::HexAdapter<std::vector> AdapVecGame2("AdapVecGame2",7);
	std::cout << AdapVecGame2.print();

	AdapVecGame2.play(c4);
	AdapVecGame2.increaseTurn();
	AdapVecGame2.play();
	AdapVecGame2.increaseTurn();
	std::cout << "After make move for second game\n";
	std::cout << AdapVecGame2.print();
	std::cout << "=====================\n\n";

	std::cout << "Compare Two Game\n";

	std::cout << "First Game to compare\n";
	std::cout << AdapVecGame.print();

	std::cout << "Second Game to compare\n";
	std::cout << AdapVecGame2.print();

	std::cout << "\nOperator == : ";
	if(AdapVecGame == AdapVecGame2){
		std::cout << "TRUE\n";
	}else{
		std::cout << "FALSE\n";
	}
	std::cout << std::endl;

	return 0;
}