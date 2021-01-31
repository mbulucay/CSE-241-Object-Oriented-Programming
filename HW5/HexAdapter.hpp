#include "HexAdapter.h"

namespace MBU{

template <template <typename...> class T>
HexAdapter<T>::HexAdapter()
{                           }

template <template <typename...> class T>
HexAdapter<T>::HexAdapter(std::string id){
    setProperties(id);
}

template <template <typename...> class T>
HexAdapter<T>::HexAdapter(std::string id, int boardSize){
    setProperties(id, boardSize);
    fillCells();
}

template <template <typename...> class T>
HexAdapter<T>::~HexAdapter()
{                                       }

template <template <typename...> class T>
void HexAdapter<T>::setProperties(std::string id, int boardSize, int gameType, int turn)
{
    this->id = id;
    this->boardSize = boardSize;
    this->gameType = gameType;
    this->turn = turn;
}

template <template <typename...> class T>
std::string HexAdapter<T>::print()const
{

    std::string result;             //  returning board shape
    int i = 1;

    result = result + "  ";
    for (char a = 'a', k = 0; k < getSize(); a++, ++k)
        result = result + a + " ";
    result = result + "\n";

    for (auto row : hexCells)
    {
        result = result + std::to_string(i);
        for (int j = 0; j < i; ++j)
            result = result + " ";

        for (auto cell : row)
        {
            result = result + char(cell.getCell()) + " ";
        }
        result = result + "\n";
        ++i;
    }
    return result;
}

template <template <typename...> class T>
void HexAdapter<T>::readFromFile(const std::string &fileName){

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
        removeCells();                          //Setting all properties of board again according to the save file
        setProperties(id, size, type, turn);
        setWinner(CellType(winner));
        setFinish(finish);
        fillCells();

        int i=0;
        while(file >> r >> c){                  //Getting coordinate to fill cells of board
            if(i % 2 == 0){
                Cell tmp(r, c, CellType::user1);
                hexCells[r][c] = tmp;
            }
            else{
                Cell tmp(r, c, CellType::user2);
                hexCells[r][c] = tmp;
            }
		    std::cout << "Game loaded from " << fileName << std::endl;
            savedMoves.push_back({r,c});
            i++;
        }
        file.close();
    }
    catch (std::ifstream::failure e) {
        std::cerr << e.what() << std::endl;
    }
}

template <template <typename...> class T>
void HexAdapter<T>::writeToFile(const std::string &fileName) const{

    std::ofstream file;
    file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    try{
        file.open(fileName);

        file << "Id: " << getId() << std::endl;         // Printing according to the saving
        file << "Size: " << getSize() << std::endl;     // file style
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

template <template <typename...> class T>
void HexAdapter<T>::reset(){                //id and size are protecting
    *this = HexAdapter(getId(),getSize());
}

template <template <typename...> class T>
void HexAdapter<T>::removeCells(){          //removing all properties of board
    *this = HexAdapter();
}

template <template <typename...> class T>
void HexAdapter<T>::play(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator(seed);

    int r = generator() % getSize();    //Computer playing as finding free cell
    int c = generator() % getSize();

    while (!checkCoordinate(r, c)){
        r = generator() % getSize();
        c = generator() % getSize();
    }
    std::cout << "Computer move : " << static_cast<char>(c + 65) << "," << r + 1 << std::endl;
    savedMoves.push_back({r, c});
    Cell tmp(r, c, CellType::user2);
    hexCells[r][c] = tmp;
}

template <template <typename...> class T>
void HexAdapter<T>::play(const Cell &cellobj){
    int r,row,column;
    char c;
    
    row = cellobj.getRow();                         //User move placeing on the board
    column = cellobj.getClm();
    
    while (!checkCoordinate(row,column)){
       std::cout << "This is not valid coordinate enter coordinate not command : ";
       std::cin >> c >> r;
       row = r-1;
       column = c - 'A';
       std::cin.clear();
       std::cin.ignore(512, '\n');
    }
    
    savedMoves.push_back({row, column});

    if(turn%2 == 0)
        hexCells[row][column] = Cell(row,column,CellType::user1);
    else
        hexCells[row][column] = Cell(row,column,CellType::user2);

}

template <template <typename...> class T>
bool HexAdapter<T>::checkCoordinate(const int &x, const int &y) const{
    return (getSize() > x && x >= 0 && getSize() > y && y >= 0 && hexCells[x][y].getCell() == CellType::empty);
}

template <template <typename...> class T>
bool HexAdapter<T>::isEnd(){
    checkUser1();
    checkUser2();
    return getFinish();
}

template <template <typename...> class T>
void HexAdapter<T>::checkUser1(){               //Check first column for user 1
    
    T< T<int> > way;

    for(int i=0; i<getSize(); ++i){
        if(hexCells[i][0].getCell() == CellType::user1)
            findWay(i, 0, way, CellType::user1);
    }

    for(auto coordinate : way)
        hexCells[coordinate[0]][coordinate[1]].setCellType(CellType::win1);
}

template <template <typename...> class T>
void HexAdapter<T>::checkUser2(){               //Check first row for user 2
    
    T< T<int> > way;

    for(auto cell : hexCells[0]){
        if(cell.getCell() == CellType::user2)
            findWay(cell.getRow(), cell.getClm(), way, CellType::user2);
    }

    for(auto coordinate : way)
        hexCells[coordinate[0]][coordinate[1]].setCellType(CellType::win2);
}

template <template <typename...> class T>
void HexAdapter<T>::findWay(int x, int y, T<T<int>> &way, CellType user){
    
    T<int> tmp;                                         //Finding way useing backtracking algorithm
    tmp.push_back(x);       tmp.push_back(y);

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

template <template <typename...> class T>
bool HexAdapter<T>::passed(T<T<int>> &way, int x, int y){       //We dont want to pass same cell two times
    bool check = true;
    
    for(auto coordinate : way){
        if(coordinate[0] == x && coordinate[1] == y){
            check = false;
            break;
        }
    }
    return check;
}

template <template <typename...> class T>
bool HexAdapter<T>::boundary(const int &x, const int &y){
    return x >= 0 && x < getSize() && y >= 0 && y < getSize();
}

template <template <typename...> class T>
Cell HexAdapter<T>::operator()(int row, int column) const{
    return hexCells[row][column];                               //returning wanted cell
}

template <template <typename...> class T>
bool HexAdapter<T>::operator==(const AbstractHex &board) const{

    if(getSize() != board.getSize())                //comparing each cell of two boards
            return false;

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

template <template <typename...> class T>
Coordinate HexAdapter<T>::lastMove()const{
    Coordinate lastmove;
    
    try{                                            //if there is last move return it
        lastmove = savedMoves.at(getTurn()-1);
    }
    catch(const std::out_of_range& e){              //other wise returning exception
        throw e;
    }
    return lastmove;
}

template <template <typename...> class T>
int HexAdapter<T>::numberOfMoves(){   
    return getTurn();                               //return moves number
}

template <template <typename...> class T>
void HexAdapter<T>::fillCells(){

    T<Cell> row;                                    //get space from ram and make them empty cell

    for (int i = 0; i < getSize(); ++i){
        for (int j = 0; j < getSize(); ++j){
            Cell tmp(i, j, CellType::empty);
            row.push_back(tmp);
        }
        hexCells.push_back(row);
        row.clear();
    }
}

template <template <typename...> class T>
void HexAdapter<T>::playGame(){
        std::string free;               //Game Menu
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
    if (getSize() == 0){
            setSize();
            setGameType();
    }
    getline(std::cin, free);
    if (getType() == 1)
        playWithFriend();
    else if (getType() == 2)
        playWithComputer();
}

template <template <typename...> class T>
void HexAdapter<T>::playWithFriend(){
    std::string command = "";
    int row;
    char column;
    
    if (getFinish()){                   //If user wants to open already finish game printing this
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
        else if(row > -1 && column > -1){       //if user entered a coordinate row and column must be bigger then -1
            int clm = column - 'A';
            row--;
            Cell tmp;
            
            if(getTurn() % 2 == 0)
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

template <template <typename...> class T>
void HexAdapter<T>::playWithComputer(){
    std::string command;
    int row;
    char clm;
    
    if(getFinish()){                //if user want to open already finish game
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
            
            play(tmp);              //user move
            turn++;
            if(isEnd()){
                std::cout << "PLAYER " << static_cast<char>(CellType::win1) << " WON\n" << print();
                winner = CellType::win1;
                break;
            }
            
            play();                 //computer move
            turn++;
            if(isEnd()){
                std::cout << "PLAYER " << static_cast<char>(CellType::win2) << " WON\n" << print();
                winner = CellType::win2;
            }
        }
    }
}

template <template <typename...> class T>
void HexAdapter<T>::getCoordinate(int &row, char &column, std::string &command)
{

    std::string line,tmp, fname, cmmd;
    std::vector<std::string> v;

    std::cout << "Enter coordinate (Ex: A 5) : ";       //Get command from user
    std::getline(std::cin,line);

    std::stringstream str_strm(line);
    while(str_strm >> tmp)
        v.push_back(tmp);

    if(v[0] == "SAVE")                      //Calling related function according to the getting command
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

template <template <typename...> class T>
void HexAdapter<T>::setSize(){

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
        setSize(); //recursive if it is not valid
    }
}

template <template <typename...> class T>
void HexAdapter<T>::setGameType(){

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
        setGameType(); //recursive
    }
}

}//end of namespace MBU
