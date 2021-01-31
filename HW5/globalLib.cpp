#include "globalLib.h"

namespace MBU{

void validSequence(std::vector<AbstractHex*> &GAMES){
    try{
        int index;                      //Checking game for valid
        gameList(GAMES);
        std::cout << "Enter the game index to check valid sequence : ";
        std::cin >> index;
        if(validSequence(GAMES.at(index))){     //if invalid index throw exception
            std::cout << "  ==> " <<  GAMES.at(index)->getId() <<  " is a valid game\n"; 
        }else if(GAMES.at(index)->getSize() == 0){  //if size == 0 we cannot check validaty
            std::cout << "You did not srt the size yet please set size for the game first\n";
        }
        else{
            std::cout << "  ==> " << GAMES.at(index)->getId() << " is not a valid game\n";
        }

    }catch (const std::out_of_range& e){
        std::cerr << "Entered invalid index \n";
        std::cerr << e.what() << std::endl;
    }
}

bool validSequence(AbstractHex* &game){

    try {                               //board size and characters(x,o,X,O,.) are checking
        int size = game->getSize();
        if(size < 5)
            return false;
        for(int i=0; i<size; ++i){
            for(int j=0; j<size; ++j){
                if (game->operator()(i, j).getCell() != CellType::user1 && game->operator()(i, j).getCell() != CellType::user2
                && game->operator()(i, j).getCell() != CellType::empty 
                && game->operator()(i,j).getCell() != CellType::win1 && game->operator()(i,j).getCell() != CellType::win2 ){
                    std::cout << i << j;
                    
                    return false;

                }
            }
        }
    }
    catch(const std::exception& e){         //if get any excepting handling it
        std::cerr << e.what() << std::endl;
    }
    return true;
}

int getOperation(){

    int operation;

    std::cout << "==========================" << std::endl //Main Menu
              << " ====== MAIN MENU =======" << std::endl
              << "1-Create a new game" << std::endl
              << "2-Play an existing game" << std::endl
              << "3-Compare two game" << std::endl
              << "4-Check for Valid Sequence of game" << std::endl
              << "5-Quit" << std::endl
              << "Enter the operation : ";

    std::cin >> operation;
    std::cout << std::endl;

    return operation;
}

void addGame(std::vector<AbstractHex *>& GAMES){
    int operation;

    std::cout << "\nWhich game do you want to create\n\n"               //Creating game type menu
                << "1-Create a new game using HexVector.h" << std::endl
                << "2-Create a new game using HexArray1D.h" << std::endl
                << "3-Create a new game using HexAdater.h (vector)" << std::endl
                << "4-Create a new game using HexAdater.h (deque)" << std::endl
                << "\nEnter the operation : ";
    std::cin >> operation;
    switch (operation){
        case 1: addVectorGame(GAMES);        
                break;
        case 2: addArray1DGame(GAMES);
                break;
        case 3: addAdapterVectorGame(GAMES);
                break;
        case 4: addAdapterDequeGame(GAMES);
                break;
        default:    std::cout << "Unknown operation\n";
    }
}

void addVectorGame(std::vector<AbstractHex *>& GAMES){
    
    std::string id;                         //adding new HexVector game to GAMES (Abstrathex *)
    std::cout << "Enter the game name : ";
    std::cin >> id;
    
    if(checkGameId(GAMES,id))
        GAMES.push_back(new HexVector(id));
    else
        std::cout << "\nThis game name already using choose another name next time" << std::endl;
}

void addArray1DGame(std::vector<AbstractHex *> &GAMES){

    std::string id;                           //adding new HexArray1D game to GAMES (Abstrathex *)
    std::cout << "Enter the game name : ";
    std::cin >> id;
    
    if(checkGameId(GAMES,id))
        GAMES.push_back(new HexArray1D(id));
    else
        std::cout << "\nThis game name already using choose another name next time" << std::endl;
}

void addAdapterVectorGame(std::vector<AbstractHex *> &GAMES){
    
    std::string id;                             //adding new template vector game to GAMES (Abstrathex *)
    std::cout << "Enter the game name : ";
    std::cin >> id;
    
    if(checkGameId(GAMES,id))
        GAMES.push_back(new HexAdapter<std::vector>(id));
    else
        std::cout << "\nThis game name already using choose another name next time" << std::endl;
}

void addAdapterDequeGame(std::vector<AbstractHex *> &GAMES){
    
    std::string id;                         //adding new template deque game to GAMES (Abstrathex *)
    std::cout << "Enter the game name : ";
    std::cin >> id;
    
    if(checkGameId(GAMES,id))
        GAMES.push_back(new HexAdapter<std::vector>(id));
    else
        std::cout << "\nThis game name already using choose another name next time" << std::endl;
}

bool checkGameId(const std::vector<AbstractHex *> &GAMES,const std::string id){
    
    for (int i = 0; i < GAMES.size(); ++i) //Searching for game identy to dont use again same identity
        if (GAMES[i]->getId() == id)
            return false;
    return true;
}

void gameList(const std::vector<AbstractHex *>& GAMES){
    
    std::cout << "---------------------\n";
    std::cout << "Created Games : \n";
    for (int i = 0; i < GAMES.size(); ++i)
        std::cout << i << " > " << GAMES[i]->getId() << std::endl;
    std::cout << "---------------------\n";        
}

void playGame(std::vector<AbstractHex *> &GAMES){
    
    int index;
    
    try{
        gameList(GAMES);
        std::cout << "Which game do you want to play enter the index of game : ";
        std::cin >> index;                      
        if(std::cin.fail()){                        // open playGame of choosen game 
            std::cin.clear();
            std::cin.ignore(512, '\n');
            throw false;
        }
        GAMES.at(index)->playGame();
    }
    catch(const bool error){            //Handling exceptions
        std::cerr << "You need to enter a number\n";
    }
    catch(const std::exception& e){
        std::cerr << "This is not a valid index please enter a valid index next time " << '\n';
    }
}

void compareTwoGame(std::vector<AbstractHex *> &GAMES){
    int index1,index2;
    
    gameList(GAMES);
    
    try{                                                        //Comparing wanted two game 
        std::cout << "Enter the first game number : ";
        std::cin >> index1;
        std::cout << "Enter the second game number : ";
        std::cin >> index2;
        
        if(GAMES[index1] == GAMES[index2]){             
            std::cout << "\nTRUE\n" << GAMES[index1]->getId() << " and " << GAMES[index2]->getId() << " are equal game\n";
        }else{
            std::cout << "\nFALSE\n" << GAMES[index1]->getId() << " and " << GAMES[index2]->getId() << " are not equal game\n";
        }
    }
    catch(const std::exception& e){
        std::cout << "Compare cannot complated \n";
        std::cerr << e.what() << '\n';
    }
}

void closeProgram(){
    std::cout << "\n=======================" << std::endl
              << "!!Have a nice day!!" << std::endl
              << "!!!! Come Again !!!!!" << std::endl
              << "=======================" << std::endl;
    exit(1);
}

}//end of namespace MBU