#include<iostream>

#include "globalLib.h"

// g++ .\1901042697.cpp .\HexAdapter.hpp .\HexArray1D.cpp .\HexVector.cpp .\AbstractHex.h .\Cell.cpp .\globalLib.cpp

int main(){

    std::vector<MBU::AbstractHex*> GAMES;
    int operation;
    
    while (true){
        std::cout << "============================\n";
        MBU::gameList(GAMES);
        operation = MBU::getOperation();

        switch(operation){

            case 1: MBU::addGame(GAMES);
                    break;
            case 2: MBU::playGame(GAMES);
                    break;
            case 3: MBU::compareTwoGame(GAMES);
                    break;
            case 4: MBU::validSequence(GAMES);
                    break;
            case 5: MBU::closeProgram();
                    break;                                            
            default: std::cout << "\n--Unknown operation--\n";        
        }
    }

    return 0;
}