#include "HexVector.h"

namespace MBU{

HexVector::HexVector()
{                       }

HexVector::HexVector(std::string id){
    setProperties(id);
}

HexVector::HexVector(std::string id, int size){
    setProperties(id,size);
    fillCells();
}

HexVector::~HexVector(){}

void HexVector::setProperties(std::string id, int boardSize , int gameType, int turn){
    this->id = id;
    this->boardSize = boardSize;
    this->gameType = gameType;
    this->turn = turn;
}

void HexVector::setSize(){
    int s1, s2;                         //We want a valid size from user and setting it
    char cross;
    std::cout << "Please enter the size (Ex:5x5) : ";
    std::cin >> s1 >> cross >> s2;
    if (s1 > 4 && s2 == s1 && (cross == 'x' || cross == 'X')){
        putSize(s1);
        fillCells();
    }
    else{
        std::cout << "Unvalid size enter again ";
        setSize();                      //recursive if it is not valid
    }
}

void HexVector::setGameType(){
    int gtype;
    std::cout << "1-> Play with friend" << std::endl
         << "2-> Play with computer" << std::endl
         << "Please, Enter a game type : ";
    std::cin >> gtype;
    if(gtype == 1 || gtype == 2){   //we are accept valid type
        putGameType(gtype);
        std::cout << "============================" << std::endl;
    }    
    else{
        std::cout << "This is not a valid type enter a valid type" << std::endl;
        setGameType();              //recursive
    }
}

std::string HexVector::print()const{
    
    std::string result;             //Printing board
    int i = 1;

    result = result + "  ";
    for (char a = 'a', k = 0; k < getSize(); a++, ++k)
        result = result + a + " ";
    result = result + "\n";
    
    for(auto row : hexCells){
        result = result + std::to_string(i);
        for(int j=0;j < i; ++j)
            result = result   + " ";

        for(auto cell : row){
            result = result  + char(cell.getCell()) + " ";
        }
        result = result + "\n";
        ++i;
    }
    return result;
}

void HexVector::readFromFile(const std::string &fileName){

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
        removeCells();                              //reset properties according to the saved file
        setProperties(id, size, type, turn);
        setWinner(CellType(winner));
        setFinish(finish);
        fillCells();

        int i=0;
        while(file >> r >> c){                  //Getting coordinates end of file
            if(i % 2 == 0){
                Cell tmp(r, c, CellType::user1);
                hexCells[r][c] = tmp;
            }
            else{
                Cell tmp(r, c, CellType::user2);
                hexCells[r][c] = tmp;
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

void HexVector::writeToFile(const std::string &fileName) const{

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

void HexVector::reset(){                    // id and size are protecting others are reseting by default
    *this = HexVector(getId(), getSize());
}

void HexVector::removeCells(){              //removing all propertis of game
    *this = HexVector();
}

void HexVector::play(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator(seed);

    int r = generator() % getSize();        //Computer playing as finding free cell
    int c = generator() % getSize();

    while (!checkCoordinate(r, c)){
        r = generator() % getSize();
        c = generator() % getSize();
    }
    std::cout << "Computer move : " << static_cast<char>(c + 65) << "," << r + 1 << std::endl;
    savedMoves.push_back({r, c});
    Cell tmp (r,c, CellType::user2);
    hexCells[r][c] = tmp;
}

void HexVector::play(const Cell &cellobj){
    int r,row,column;
    char c;
    
    row = cellobj.getRow();
    column = cellobj.getClm();
    while (!checkCoordinate(row,column)){
       std::cout << "This is not valid coordinate enter coordinate not command : ";
       std::cin >> c >> r;
       row = r-1;
       column = c - 'A';
       std::cin.clear();
       std::cin.ignore(512, '\n');
    }
    
    savedMoves.push_back({row, column});        //adding saved moves

    if(turn%2 == 0)                                                 //Filiing cells according to the turn
        hexCells[row][column] = Cell(row,column,CellType::user1);
    else
        hexCells[row][column] = Cell(row,column,CellType::user2);

}

bool HexVector::checkCoordinate(const int &x, const int &y) const{
    return (getSize() > x && x >= 0 && getSize() > y && y >= 0 && hexCells[x][y].getCell() == CellType::empty);
}

void HexVector::getCoordinate(int &row, char &column, std::string& command){
    
    std::string line,tmp, fname, cmmd;
    std::vector<std::string> v;

    std::cout << "Enter coordinate (Ex: A 5) : ";
    std::getline(std::cin,line);

    std::stringstream str_strm(line);
    while(str_strm >> tmp)
        v.push_back(tmp);

    if(v[0] == "SAVE")                  // Calling related function according to the getting command
        writeToFile(v[1]);
    else if(v[0] == "LOAD"){
        readFromFile(v[1]);
    }
    else if(v[0] == "LAST"){
        try {
            Coordinate tmp = lastMove();
            std::cout << "The last move is " << char(tmp.column+'A')  << " " << tmp.row+1 << std::endl;
        }catch(const std::out_of_range& e){
            std::cout << "There is no last move  : \n" << e.what() << std::endl;
        }
    }
    else if(v[0] == "RESET")
        reset();
    else if (v[0] == "MOVES")
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
        column = line.at(0);
        row = sum;
    }
}

bool HexVector::isEnd(){
    checkUser1();
    checkUser2();
    return getFinish();
}

void HexVector::checkUser1(){               //Checking first column
    std::vector< std::vector<int> > way;

    for(int i=0; i<getSize(); ++i){
        if(hexCells[i][0].getCell() == CellType::user1)
            findWay(i, 0, way, CellType::user1);
    }

    for(auto coordinate : way)
        hexCells[coordinate[0]][coordinate[1]].setCellType(CellType::win1);

}

void HexVector::checkUser2(){               //Checking first row
    std::vector< std::vector<int> > way;

    for(auto cell : hexCells[0]){
        if(cell.getCell() == CellType::user2)
            findWay(cell.getRow(), cell.getClm(), way, CellType::user2);
    }

    for(auto coordinate : way)
        hexCells[coordinate[0]][coordinate[1]].setCellType(CellType::win2);

}

void HexVector::findWay(int x, int y, std::vector<std::vector<int>> &way, CellType user){

    std::vector<int> tmp;
    tmp.push_back(x);       tmp.push_back(y);               //Finding way using backtracking algorithm

    way.push_back(tmp);

    if(x == getSize()-1 && user == CellType::user2){    setFinish(true);
        setWinner(CellType::win1);
        return;
    }
    if(y == getSize()-1 && user == CellType::user1){    setFinish(true);
        setWinner(CellType::win2);
        return;
    }

    if (boundary(x - 1, y + 1) && passed(way, x - 1, y + 1) && hexCells[x - 1][y + 1].getCell() == user)
        findWay(x - 1, y + 1, way, user);
    if (boundary(x, y + 1) && passed(way, x, y + 1) && hexCells[x][y + 1].getCell() == user)
        findWay(x, y + 1, way, user);
    if (boundary(x + 1, y) && passed(way, x + 1, y) && hexCells[x + 1][y].getCell() == user)
        findWay(x + 1, y, way, user);
    if (boundary(x + 1, y - 1) && passed(way, x + 1, y - 1) && hexCells[x + 1][y - 1].getCell() == user)
        findWay(x + 1, y - 1, way, user);
    if (boundary(x, y - 1) && passed(way, x, y - 1) && hexCells[x][y - 1].getCell() == user)
        findWay(x, y - 1, way, user);
    if (boundary(x - 1, y) && passed(way, x - 1, y) && hexCells[x - 1][y].getCell() == user)
        findWay(x - 1, y, way, user);
    if (getFinish())
        return;

    way.pop_back();
}

bool HexVector::passed(std::vector<std::vector<int>> &way, int x, int y){
    bool check = true;
    for(std::vector<int> coordinate : way){                 //We dont want to pass same location twice
        if(coordinate[0] == x && coordinate[1] == y){
            check = false;
            break;
        }
    }
    return check;
}

bool HexVector::boundary(const int &x, const int &y){
    return x >= 0 && x < getSize() && y >= 0 && y < getSize();
}

Cell HexVector::operator()(int row, int column)const{
    return hexCells[row][column];
}

bool HexVector::operator==(const AbstractHex &board)const{
    
    if(getSize() != board.getSize())
        return false;
                                            //Comparing each cell of two board
    for(int i=0; i<getSize(); ++i){
        for(int j = 0; j<getSize(); ++j){
            if(this->operator()(i,j).getCell() != board(i,j).getCell()){
                std::cout << i << j << std::endl;
                return false;
            }
        }
    }

    return true;
}

Coordinate HexVector::lastMove()const{
    
    Coordinate lastmove;
    try{
        lastmove = savedMoves.at(getTurn()-1);          //if there is last move returning coordiante
    }
    catch(const std::out_of_range& e){                  //If there is not throwing exception
        throw e;
    }
    return lastmove;
}

int HexVector::numberOfMoves(){
    return getTurn();
}

void HexVector::fillCells(){
    std::vector<Cell> row;
                                            //Getting memory space for board
    for(int i=0; i<getSize() ; ++i){
        for(int j=0; j<getSize(); ++j){
            Cell tmp(i,j,CellType::empty);
            row.push_back(tmp);
        }
        hexCells.push_back(row);
        row.clear();
    }
}

void HexVector::playGame(){

    std::string free;               //Game menu
    std::cout << "\n================Welcome The Hex Game Menu===================" << std::endl
              << "               GAME Id  = " << getId() << std::endl
              << " \"SAVE file.txt\"       // This command game saving file.txt" << std::endl
              << " \"LOAD file.txt\"       // This command Load game named by file.txt" << std::endl
              << " \"LAST\"                // To get last move " << std::endl
              << " \"RESET\"               // To reset the board" << std::endl
              <<  "\"MOVES\"               // Show the number of moves" << std::endl        
              << " \"MENU\"                // If you want to change game or quit " << std::endl
              << " ====================Have a nice game :)====================" << std::endl
              << "-------------------------------------------------------------" << std::endl;
    if(getSize() == 0){
        setSize();
        setGameType();
    }
    getline(std::cin, free);
    if (getType() == 1)
        playWithFriend();
    else if (getType() == 2)
        playWithComputer();
}

void HexVector::playWithFriend(){
    std::string command = "";
    int row;
    char column;
    if (getFinish()){
        std::cout << print();
        std::cout << "\nThis game already finih " << (char)getWinner() << "Won" << std::endl
                  << "please choose another game\n";
    }

    while(!getFinish()){
        row = column = -1;
        std::cout << print();

        getCoordinate(row,column,command);
        
        if(command == "MENU")
            break;
        else if(row > -1 && column > -1){      //if entered coordiante row and column are bigger than -1
            int clm = column - 'A';
            row--;
            Cell tmp;
            
            if(getTurn() % 2 == 0)              //replacing the user chararacter of cell according to the turn
                tmp.setCoordinate(row,clm,CellType::user1);
            else
                tmp.setCoordinate(row,clm,CellType::user2);    
            
            play(tmp);
            if(isEnd())
                std::cout << "PLAYER " << char(getWinner()) << "HAS WON\n" << print();
            turn++;
        }
    }
}

void HexVector::playWithComputer(){

    std::string command;
    int row;
    char clm;
    if(getFinish()){
        std::cout << print();
        std::cout << "\nThis game already finih " << (char)getWinner() << " Won" << std::endl
                  << "please choose another game\n\n";
    }
    while(!getFinish()){
        row = clm = -1;

        std::cout << print();

        getCoordinate(row,clm,command);

        if(command == "MENU")
            break;

        if(row > -1 && clm > -1){

            int column = clm - 'A';
            row--;
            Cell tmp(row,column,CellType::user1);

            play(tmp);
            turn++;         //Your move

            if(isEnd()){
                std::cout << "PLAYER " << static_cast<char>(CellType::win1) << " WON\n" << print();
                winner = CellType::win1;
                break;
            }

            play();         //Computers move 
            turn++;

            if(isEnd()){
                std::cout << "PLAYER " << static_cast<char>(CellType::win2) << " WON\n" << print();
                winner = CellType::win2;
            }
        }
    }
}

}//end of namespace MBU