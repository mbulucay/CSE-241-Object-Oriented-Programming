#include "HexArray1D.h"

namespace MBU{

HexArray1D::HexArray1D()
{                       }

HexArray1D::HexArray1D(std::string id){
    setProperties(id);
}

HexArray1D::HexArray1D(std::string id, int size){
    setProperties(id, size);
    fillCells();
}

HexArray1D::HexArray1D(const HexArray1D &obj){
    
    setProperties(obj.getId(), obj.getSize(), obj.getType(), obj.getTurn());        //Defining properties and allocate memory space
    hexCells = (Cell*)malloc(sizeof(Cell)*getSize()*getSize());

    for(int i=0; i<getSize()*getSize(); ++i)        //Deep Copying objects cells
        hexCells[i] = obj.hexCells[i];
}

HexArray1D::~HexArray1D(){
    if(hexCells != nullptr)
        delete[] hexCells;
}

void HexArray1D::setProperties(std::string id, int boardSize, int gameType , int turn ){
    this->id = id;
    this->boardSize = boardSize;
    this->gameType = gameType;
    this->turn = turn;
}

HexArray1D& HexArray1D::operator=(const HexArray1D &obj){

    if(this != &obj){           //Deep copy for board pointer

        Cell *newCellArray1D;
        newCellArray1D = (Cell*)malloc(sizeof(Cell)*getSize()*getSize());

        setProperties(obj.getId(), obj.getSize(), obj.getType(), obj.getTurn());
        setFinish(obj.getFinish());
        setWinner(obj.getWinner());

        delete [] hexCells;
        savedMoves.clear();

        for(int i=0; i<getSize()*getSize(); ++i)
            newCellArray1D[i] = obj.hexCells[i];

        for(auto c : obj.savedMoves)
            savedMoves.push_back(c);

        hexCells = newCellArray1D;    
    }

    return *this;
}

std::string HexArray1D::print()const{

        std::string result;
        int i = 1;
                                            //Printing board
        result = result + " ";
        for (char a = 'a', k = 0; k < getSize(); a++, ++k)
            result = result + a + " ";
    
        for(int j=0; j<getSize() * getSize(); ++j){
            if (j % (getSize()) == 0)
                result = result + "\n";
            
            if(j%(getSize()) == 0){
                result = result + std::to_string(i);
                for(int m =0;m<i; ++m)
                    result = result + " ";
                ++i;
            }
            result = result + char(hexCells[j].getCell()) + " ";
        }
        result = result + "\n";
    return result;
}

void HexArray1D::readFromFile(const std::string &fileName){
    std::string id, free;
    
    int size, type, turn, winner, position, r, c;
    CellType player;
    bool finish;

    std::ifstream file;
    try {
        file.open (fileName);

        file >> free >> id;
        file >> free >> size;
        file >> free >> type;
        file >> free >> turn;
        file >> free >> winner;
        file >> free >> finish;
        removeCells();                             //Setting properties according to the file
        setProperties(id, size, type, turn);
        setWinner(CellType(winner));
        setFinish(finish);
        fillCells();

        int i=0;
        while(file >> r >> c){

            if(i % 2 == 0){
                Cell tmp(r, c, CellType::user1);
                hexCells[r * getSize() + c] = tmp;
            }
            else{
                Cell tmp(r, c, CellType::user2);
                hexCells[r * getSize() + c] = tmp;
            }

            savedMoves.push_back({r,c});
            i++;
        }
        std::cout << "Game loaded from " << fileName << std::endl;
        file.close();
    }
    catch (std::ifstream::failure e) {
        std::cerr << e.what() << std::endl;
    }
}

void HexArray1D::writeToFile(const std::string &fileName) const{

    std::ofstream file;
    file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    try{
        file.open(fileName);

        file << "Id: " << getId() << std::endl;     // Printing according to the saving
        file << "Size: " << getSize() << std::endl; // file style
        file << "Type: " << getType() << std::endl;
        file << "Turn: " << getTurn() << std::endl;
        file << "Winner: " << getWinner() << std::endl;
        file << "Finish: " << getFinish() << std::endl;

        for (auto coordinate : savedMoves)
            file << coordinate.row << " " << coordinate.column << std::endl;
        
        std::cout << "Game saved to " << fileName << std::endl;
        file.close();
    }
    catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}

void HexArray1D::reset(){       //Protecting id and size (sadece isaretleri kareler siliniyor)
    *this = MBU::HexArray1D(getId(), getSize());
}

void HexArray1D::removeCells(){  //All data removing has game
    delete [] hexCells;
}

void HexArray1D::play(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator(seed);

    int index = generator() % (getSize()*getSize()) ;       //Computer playing random  

    while (!checkCoordinate(index)){                    //Checking coordinate valid or not
        index = generator() % (getSize() * getSize());
        std::cout << "aaa" << std::endl;
    }
    
    int row, column;                //We set the row and column according to the index for Cell coordinate
    row = index / getSize();
    column = index % getSize();

    std::cout << "Computer move : " << static_cast<char>(column + 'A') << "," << row + 1 << std::endl;

    savedMoves.push_back({row,column});
    Cell tmp(row,column,CellType::user2);

    hexCells[index] = tmp;
}

void HexArray1D::play(const Cell &cellobj){

    int row, column,index;

    row = cellobj.getRow();
    column = cellobj.getClm();
    index = row*getSize() + column;

    while(!checkCoordinate(index)){
        int r;
        char c;
        std::cout << "This is not valid coordinate enter coordinate not command : ";
        std::cin >> c >> r;
        row = r-1;
        column = c - 'A';
        index = row*getSize() + column;
        std::cin.clear();
        std::cin.ignore(512, '\n');
    }

    savedMoves.push_back({row,column});                         //Saving moves
    if(turn%2 == 0)
        hexCells[index] = Cell(row, column, CellType::user1);       //Filling cell according to the turn
    else
        hexCells[index] = Cell(row, column, CellType::user2);
}

bool HexArray1D::checkCoordinate(const int &index) const{
    return hexCells[index].getCell() == CellType::empty;
}

bool HexArray1D::isEnd(){

    checkUser1();
    checkUser2();
    return getFinish();
}

Cell HexArray1D::operator()(int row, int column) const{
    return hexCells[row*getSize() + column];
}

bool HexArray1D::operator==(const AbstractHex &board) const{

    if(this != &board){                         //Checking cell on board one by one
        if (getSize() != board.getSize())
            return false;

        for (int i = 0; i < getSize() ; ++i){
            for (int j = 0; j < getSize(); ++j){
                if (operator()(i, j).getCell() != board(i, j).getCell())
                    return false;
            }        
        }
    }
    return true;
}

Coordinate HexArray1D::lastMove()const{
    Coordinate lastmove;
    try{
        lastmove = savedMoves.at(getTurn()-1);      //If there is a last move returning its coordinate
    }
    catch(const std::out_of_range& e){              //if it is not throwing an exception
        throw e;
    }
    return lastmove;
}

int HexArray1D::numberOfMoves(){
    return getTurn();
}

void HexArray1D::fillCells(){
    int counter = 0;
    
    hexCells = (Cell*)malloc(sizeof(Cell)*getSize()*getSize());         //Allocating memory space

    for (int i = 0; i < getSize(); ++i){
        for(int j = 0; j <getSize() ; ++j){
            hexCells[counter] = Cell(i,j,CellType::empty);
            counter++;
        }
    }
}

void HexArray1D::playGame(){

    std::string free;
    std::cout << "\n================Welcome The Hex Game Menu===================" << std::endl
              << "               GAME Id  = " << getId() << std::endl
              << " \"SAVE file.txt\"       // This command game saving file.txt" << std::endl
              << " \"LOAD file.txt\"       // This command Load game named by file.txt" << std::endl
              << " \"LAST\"                // To get last move " << std::endl
              << " \"RESET\"               // To reset the board" << std::endl
              << " \"MOVES\"               // Get tthe number of moves" << std::endl
              << " \"MENU\"                // If you want to change game or quit " << std::endl
              << " ====================Have a nice game :)====================" << std::endl
              << "-------------------------------------------------------------" << std::endl;
    if(getSize() == 0){
        setSize();
        setGameType();
    }
    getline(std::cin,free);
    if (getType() == 1)
        playWithFriend();
    else if (getType() == 2)
        playWithComputer();
}

void HexArray1D::playWithFriend(){
    std::string command = "";
    int index;
    if (getFinish()){
        std::cout << print();
        std::cout << "\nThis game already finih " << (char)getWinner() << "Won" << std::endl
                  << "please choose another game\n";
    }
  
    while(!getFinish()){
        command = " ";
        index = -1;
        std::cout << print();

        getCoordinate(index,command);

        if(command == "MENU")
            break;
        else if(index > -1){
            int row,clm;
            row = index / getSize();
            clm = index % getSize();
            Cell tmp;

            if(getTurn() %2 == 0)
                tmp.setCoordinate(row, clm, CellType::user1);
            else
                tmp.setCoordinate(row, clm, CellType::user2);

            play(tmp);

            if(isEnd())
                std::cout << "PLAYER " << char(getWinner()) << " HAS WON\n" << print();
            turn++;
        }    
    }
}

void HexArray1D::playWithComputer(){
    std::string command;
    int index;
    if(getFinish()){
        std::cout << print();
        std::cout << "\nThis game already finih " << (char)getWinner() << "Won " << std::endl
                  << "please choose another game\n\n";
    }

    while(!getFinish()){
        command = " ";
        index = -1;

        std::cout << print();

        getCoordinate(index,command);

        if(command == "MENU")
            break;

        else if(index > -1){

            int row, clm;
            row = index / getSize();
            clm = index % getSize();
            Cell tmp;

            if(getTurn() % 2 == 0)
                tmp.setCoordinate(row, clm, CellType::user1);
            else
                tmp.setCoordinate(row, clm, CellType::user2);

            play(tmp);
            turn++;
            if(isEnd()){
                std::cout << "PLAYER" << static_cast<char>(CellType::win1) << "WON\n" << print();
                winner = CellType::win1;
                break;
            }

            play();
            turn++;
            if(isEnd()){
                std::cout << "PLAYER" << static_cast<char>(CellType::win2) << "WON\n" << print();
                winner = CellType::win2;
            }
        }
    }
}

void HexArray1D::setSize(){

    int s1, s2;        //We want a valid size from user and setting it
    char cross;
    std::cout << "Please enter the size (Ex:5x5) : ";
    std::cin >> s1 >> cross >> s2;
    if (s1 > 4 && s2 == s1 && (cross == 'x' || cross == 'X')){
        putSize(s1);
        fillCells();
    }
    else{
        std::cout << "Unvalid size enter again ";
        setSize(); //recursive if it is not valid
    }
}

void HexArray1D::setGameType(){

    int gtype;
    std::cout << "1-> Play with friend" << std::endl
         << "2-> Play with computer" << std::endl
         << "Please, Enter a game type : ";
    std::cin >> gtype;
    if(gtype == 1 || gtype == 2){   //we are accept just valid type
        putGameType(gtype);
        std::cout << "============================" << std::endl;
    }    
    else{
        std::cout << "This is not a valid type enter a valid type" << std::endl;
        setGameType(); //recursive
    }
}

void HexArray1D::getCoordinate(int &index, std::string &command){

    std::string line,tmp, fname, cmmd;
    std::vector<std::string> v;

    std::cout << "Enter coordinate (Ex: A 5) : ";
    std::getline(std::cin,line);

    std::stringstream str_strm(line);
    while(str_strm >> tmp)
        v.push_back(tmp);

    if(v[0] == "SAVE")                  //Calling related functions according to the command
        writeToFile(v[1]);
    else if(v[0] == "LOAD")
        readFromFile(v[1]);
    else if(v[0] == "LAST"){
        try {
            Coordinate tmp = lastMove();
            std::cout << "The last move is " << char(tmp.column + 'A')  << " " << tmp.row+1 << std::endl;
        }catch(const std::out_of_range& e){
            std::cout << "There is no last move  : \n" << e.what() << std::endl;
        }
    }
    else if(v[0] == "RESET")
        reset();
    else if(v[0] == "MOVES")
        std::cout << "Number of moves = " << numberOfMoves() << "\n";    
    else if(v[0] == "MENU")
        command = "MENU";
    else{
        
        int sum = 0;
        for (char i : line){
            if (i >= '0' && i <= '9')
                sum = sum * 10 + i - '0';
            if (i == '-'){
                sum = 0;                //Negatif isaretli degerler icin
                break;
            }
        }
        char column = line.at(0);
        int row = sum;
        index = (row-1)*getSize() + column - 'A';
    }
}

void HexArray1D::checkUser1(){              //Looking first column for user 1

    std::vector<std::vector<int>> way;
 
    for (int i = 0; i < getSize(); ++i){
        if (operator()(i, 0).getCell() == CellType::user1)
            findWay(i, 0, way, CellType::user1);
    }

    for (auto coordinate : way)
        hexCells[coordinate[0] * getSize() + coordinate[1]].setCellType(CellType::win1);
}

void HexArray1D::checkUser2(){             //Looking first row for user 1s

    std::vector< std::vector<int> > way;

    for(int i=0; i<getSize(); ++i)    
        if(operator()(0,i).getCell() == CellType::user2)
            findWay(operator()(0, i).getRow(), operator()(0, i).getClm(), way, CellType::user2);

    for (auto coordinate : way)
        hexCells[coordinate[0] * getSize() + coordinate[1]].setCellType(CellType::win2);
}

void HexArray1D::findWay(int x, int y, std::vector<std::vector<int>> &way, CellType user) {

    //Finding way using backtracking algorithm

    std::vector<int> tmp;
    tmp.push_back(x);       tmp.push_back(y);

    way.push_back(tmp);
    if(x == sqrt(getSize()*getSize())-1 && user == CellType::user2){    setFinish(true);
        setWinner(CellType::win1);
        return;
    }
    if(y == sqrt(getSize()*getSize())-1 && user == CellType::user1){    setFinish(true);
        setWinner(CellType::win2);
        return;
    }

    if (boundary(x - 1, y + 1) && passed(way, x - 1, y + 1) && operator()(x-1, y+1).getCell() == user)
        findWay(x - 1, y + 1, way, user);
    if (boundary(x, y + 1) && passed(way, x, y + 1) && operator()(x, y + 1).getCell() == user)
        findWay( x, y + 1, way, user);
    if (boundary(x + 1, y) && passed(way, x + 1, y) && operator()(x+1, y).getCell() == user)
        findWay( x + 1, y, way, user);
    if (boundary(x + 1, y - 1) && passed(way, x + 1, y - 1) && operator()(x + 1, y - 1).getCell() == user)
        findWay( x + 1, y - 1, way, user);
    if (boundary(x, y - 1) && passed(way, x, y - 1) && operator()(x, y - 1).getCell() == user)
        findWay( x, y - 1, way, user);
    if (boundary(x - 1, y) && passed(way, x - 1, y) && operator()(x - 1, y).getCell() == user)
        findWay( x - 1, y, way, user);
    if (getFinish())
        return;

    way.pop_back();
}

bool HexArray1D::boundary(const int &x, const int &y){
    return x >= 0 && x < sqrt(getSize()*getSize()) && y >= 0 && y < sqrt(getSize()*getSize());
}

bool HexArray1D::passed(std::vector<std::vector<int>> &way, int x, int y){      //If we pass the coordiante we dont pass again
    bool check = true;
    for(auto coordinate : way){
        if(coordinate[0] == x && coordinate[1] == y){
            check = false;
            break;
        }
    }
    return check;
}

}//end of namespace MBU