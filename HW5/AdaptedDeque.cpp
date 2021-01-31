#include <iostream>
#include "HexAdapter.hpp"

int main(){

	MBU::Cell c1(3,2,MBU::CellType::user1);
	MBU::Cell c2(4,2,MBU::CellType::user1);
	MBU::Cell c3(5,1,MBU::CellType::user1);
	MBU::Cell c4(2,4,MBU::CellType::user1);


	MBU::HexAdapter<std::deque> AdapDeqGame("AdapDeqGame",6);
	std::cout << "Game Created\n";
	std::cout << AdapDeqGame.print();

	std::cout << "Calling lastMove() function before doing any move\n";
	try{
		MBU::Coordinate lmove = AdapDeqGame.lastMove();
		std::cout << "Last move for the game : " << char(lmove.column+'A') << " " << lmove.row+1 << std::endl;
	}catch(const std::out_of_range& e){
            std::cout << "There is no last move  : \n" << e.what() << std::endl;
	}

	AdapDeqGame.play(c1);
	AdapDeqGame.increaseTurn();
	AdapDeqGame.play();
	AdapDeqGame.increaseTurn();
	std::cout << AdapDeqGame.print();
	std::cout << "=====================\n\n";

	AdapDeqGame.play(c2);
	AdapDeqGame.increaseTurn();
	AdapDeqGame.play();
	AdapDeqGame.increaseTurn();
	std::cout << AdapDeqGame.print();
	std::cout << "=====================\n\n";

	std::cout << "Writing file \n"; 
	AdapDeqGame.writeToFile("dequeSavedGame");
	std::cout << "=====================\n\n";

	std::cout << "Make two move after saving\n";
	AdapDeqGame.play(c3);
	AdapDeqGame.increaseTurn();
	AdapDeqGame.play();
	AdapDeqGame.increaseTurn();
	std::cout << AdapDeqGame.print();
	std::cout << "=====================\n\n";


	std::cout << "Reading again file after make two move\n";
	AdapDeqGame.readFromFile("dequeSavedGame");
	std::cout << AdapDeqGame.print();
	std::cout << "=====================\n\n";

	std::cout << "isEnd : " << AdapDeqGame.isEnd() << std::endl;
	std::cout << "=====================\n\n";

	MBU::Cell dCell = AdapDeqGame(4,2);
	std::cout << "AdapDeqGame(4,2) index operator() dCell.getRow() << dCell.getClm() :  " << dCell.getRow() << ", " << dCell.getClm() << "\n";
	std::cout << "=====================\n\n";

	std::cout << "Number of moves (AdapDeqGame.numberOfMoves()) : " << AdapDeqGame.numberOfMoves() << std::endl;
	std::cout << "=====================\n\n";

	std::cout << "Calling again AdapDeqGame.lastMove() function\n";
	try{
		MBU::Coordinate lmove = AdapDeqGame.lastMove();
		std::cout << "Last move for the game : " << char(lmove.column+'A') << " " << lmove.row+1 << std::endl;
	}catch(const std::out_of_range& e){
            std::cout << "There is no last move  : \n" << e.what() << std::endl;
	}
	std::cout << "=====================\n\n";


	std::cout << "Create new game to compare\n";
	MBU::HexAdapter<std::deque> AdapDeqGame2("AdapDeqGame2",7);
	std::cout << AdapDeqGame2.print();

	AdapDeqGame2.play(c4);
	AdapDeqGame2.increaseTurn();
	AdapDeqGame2.play();
	AdapDeqGame2.increaseTurn();
	
	std::cout << "After make move for second game\n";
	std::cout << AdapDeqGame2.print();
	std::cout << "=====================\n\n";

	std::cout << "Compare Two Game\n";

	std::cout << "First Game to compare\n";
	std::cout << AdapDeqGame.print();

	std::cout << "Second Game to compare\n";
	std::cout << AdapDeqGame2.print();

	std::cout << "\nOperator == : ";
	if(AdapDeqGame == AdapDeqGame2){
		std::cout << "TRUE\n";
	}else{
		std::cout << "FALSE\n";
	}
	std::cout << std::endl;

	return 0;
}