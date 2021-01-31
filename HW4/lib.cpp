#include <iostream>
#include "lib.hpp"

////////////////////////////////////////////////////                //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// GLOBAL FUNCTIONS /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////                //////////////////////////////////////////////////////////////

bool CheckName(const std::vector<Hex*> &GAMES, std::string name){
    bool result = true;
    for (int i = 0; i < GAMES.size(); ++i)      //Searching for game identy to dont use again same identity
        if (GAMES[i]->getId() == name)
            result = false;
    return result;
}

int ReturnGameIndex(const std::vector<Hex*> &GAMES, std::string name){
    int index = -1;
    int i = 0;
    for (int i = 0; i < GAMES.size(); ++i){     //Find index using game identity
        if (GAMES[i]->getId() == name){
            index = i;
            break;
        }
    }
    return index;
}

void GameList(const std::vector<Hex*> &GAMES){
    std::cout << "\n---------------------" << std::endl         //Print all created game name
              << "Existing game names :" << std::endl;
    for (int i = 0; i < GAMES.size(); ++i)
        std::cout << "Game " << i + 1 << " :" << GAMES[i]->getId() << std::endl;
    std::cout << "----------------------" << std::endl;
}

void CompareTwoGames(const std::vector<Hex*> &GAMES, int &game1, int &game2){
    std::string name1, name2;
    GameList(GAMES);
    std::cout << "Enter the first game name : ";        //Get two game name 
    std::cin >> name1;
    std::cout << "Enter the second game name : ";
    std::cin >> name2;
    game1 = ReturnGameIndex(GAMES, name1);              //Finding their index and assaign them
    game2 = ReturnGameIndex(GAMES, name2);
}

//MENU FUNCTION
int GetOperation(){
    int operation;
    std::cout << "==========================" << std::endl      //Main Menu
              << " ====== MAIN MENU =======" << std::endl
              << "1-Create a new game " << std::endl
              << "2-Play an existing game" << std::endl
              << "3-Compare two game" << std::endl
              << "4-Quit" << std::endl
              << "Enter the operation : ";
    std::cin >> operation;
    std::cout << std::endl;
    return operation;
}

void PlayAnExistingGame(std::vector<Hex*> &GAMES){
    std::string name;
    int gameIndex;
    std::cout << "Enter the game name you wanna play : ";       //We take game name to play
    std::cin >> name;
    gameIndex = ReturnGameIndex(GAMES, name);
    if (gameIndex == -1)                                        //If it not exist    
        std::cout << "There is no game called " << name << std::endl;
    else
        GAMES[gameIndex]->playGame();  
}

void CompareTwoGames(const std::vector<Hex*> &GAMES){
    int index_1, index_2;
    CompareTwoGames(GAMES, index_1, index_2);
    if (index_1 != -1 && index_2 != -1){                //if both game are exsiting compare them
        std::cout <<"----------------------------------------\n";
        std::cout << "\nThe result is";
        if (*GAMES[index_1] == *GAMES[index_2])         //We are using operation overloding operator==
            std::cout << "TRUE" << std::endl;           
        else
            std::cout << "FALSE" << std::endl;
        std::cout << "----------------------------------------\n";
    }
    else
        std::cout << "Make sure that you enter the correct game name" << std::endl;
}

void PushGAME(std::vector<Hex*> &GAMES){
    std::string name;
    std::cout << "Enter the game name : ";
    std::cin >> name;
    if (CheckName(GAMES, name)){        //If game name is not used                           
        Hex *tmp = new Hex(name);           //We are using conversion construtor
        GAMES.push_back(tmp);               //and push it main game vector
    }    
    else
        std::cout << "\nThis game name already using choose another name" << std::endl;
}

void CloseProgram(){
    std::cout << "\n=======================" << std::endl
              << "!!Have a nice day!!" << std::endl
              << "!!!! Come Again !!!!!" << std::endl
              << "=======================" << std::endl;
    exit(1);
}

////////////////////////////////////////////////////                //////////////////////////////////////////////////////////////
/////////////////////////////////////////////// CLASS MEMBER FUNCTIONS ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////                //////////////////////////////////////////////////////////////

Hex::Hex()
    : boardSize(-1), gameType(-1), turn(0), id(""), hexCells(nullptr),savedCoordinates(nullptr)
{}
Hex::Hex(std::string& id)
    : boardSize(0), gameType(0), turn(0), id(id), hexCells(nullptr),savedCoordinates(nullptr)
{}
Hex::Hex(std::string& id, int size)
    : boardSize(size), gameType(0), turn(0), id(id)
{   fillCells();}
Hex::Hex(std::string& id, int size, int type, int turn, celltype winner, bool finish)
    : boardSize(size), gameType(type), turn(turn), id(id),finish(finish)
{   fillCells();}
Hex::Hex(const Hex &rS)
    :   id(rS.getId()),boardSize(rS.getSize()),gameType(rS.getType()),turn(rS.getTurn()),winner(rS.getWinner()),finish(rS.getFinish())
{   
    savedCoordinates = new coorinate[rS.getSize() * rS.getSize()];

    for(int i=0; i<getTurn(); ++i)                              //We are doing deep copy
        savedCoordinates[i] = rS.savedCoordinates[i];       //Assing saved coordinate

    hexCells = new Cell*[rS.getSize()];
    for(int i=0; i<rS.getSize(); ++i)                       //Creating cell objects for class
        hexCells[i] = new Cell[rS.getSize()];

    for(int i=0; i<rS.getSize(); ++i)                       //setting board according to the copy object
        for(int j=0; j<rS.getSize(); ++j)
            hexCells[i][j].setCoordinate(i, j,celltype::empty);
}   

Hex::~Hex() {
    delete [] savedCoordinates;             //Deleting the all dynamic memory
    for (int i = 0; i < getSize(); ++i)
        delete [] hexCells[i];
}

Hex::Cell::Cell() : row(-1),clm(-1),cell(celltype::empty)
{}

//BASIC SETTER
void Hex::fillCells(){
    
    savedCoordinates = new coorinate[getSize() * getSize()];        //We are allocate enough memory place 
    hexCells = new Cell*[getSize()];
    for (int i = 0; i < getSize(); ++i)
        hexCells[i] = new Cell[getSize()];
    cleanBoard();       //Filing with . all board
}

void Hex::setSize(){
    int s1, s2;                         //We want a valid size from user and setting it
    char cross;
    std::cout << "Please enter the size (Ex:5x5) : ";
    std::cin >> s1 >> cross >> s2;
    if (s1 > 4 && s2 == s1 && (cross == 'x' || cross == 'X')){
        setSize(s1);
        fillCells();
    }
    else{
        std::cout << "Unvalid size enter again ";
        setSize();//recursive if it is not valid
    }
}

void Hex::setType(){
    int gtype;
    std::cout << "1-> Play with friend" << std::endl
         << "2-> Play with computer" << std::endl
         << "Please, Enter a game type : ";
    std::cin >> gtype;
    if(gtype == 1 || gtype == 2){   //we are accept valid type
        setType(gtype);
        std::cout << "============================" << std::endl;
    }    
    else{
        std::cout << "This is not a valid type enter a valid type" << std::endl;
        setType();  //recursive
    }
}

//BOARD FUNCTIONS
void Hex::removeBoard(){
    delete [] savedCoordinates;     //for load or resize ect. delete allocated dynamic memory
    for(int i=0; i<getSize(); ++i)
        delete [] hexCells[i];
}

void Hex::cleanBoard(){
    for(int i=0; i<getSize(); ++i)          //fill board with .
        for(int j=0; j<getSize(); ++j)
            hexCells[i][j].setCoordinate(i,j,celltype::empty);
}

void Hex::resizeBoard(){
    int s1,s2;
    char cross;                             //Deleting old board and creating new board
    std::string free;
    std::cout << "-------------------------\nEnter the new size (ex: 5x5):";
    std::cin >> s1 >> cross >> s2;
    if(s1 > 4 && s1 == s2 && (cross == 'x' || cross == 'X')){
        removeBoard();
        setSize(s1);
        fillCells();
    }
    else 
        std::cout << "This is not valid size Enter a valid size next time \n";
    count -= getTurn(); //setting static
    setTurn(0);         //we clearing board so we need to make turn = 0
    getline(std::cin, free);
}

//SAVE & LOAD FUNCTIONS
void Hex::saveGame(const std::string &fname)const{

    std::ofstream file;
    file.open(fname,std::ios::out);
    if (!file.is_open()){
        std::cout << "file could not opened \n";
        return;
    }    
    file << *this;      //Printing file according to the saving style
    std::cout << "\nGame Saved To " << fname << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++\n";

    file.close();
}

void Hex::loadGame(const std::string &fname){

    std::ifstream file(fname);
    if (!file.is_open()){
        std::cout << "Someting went wrong check the file is exsitingn\n";
        return;
    }
    file >> *this;          // assign values               
    std::cout << fname << " game is loaded" << std::endl
              << "++++++++++++++++++++++++++++++" << std::endl;
    if(getType() == 1)
        playWithFriend();
    else 
        playWithComp();    
    file.close();
}

//GAME FUNCTIONS
void Hex::playGame(){
    std::string free;
    std::cout << "\n================Welcome The Hex Game Menu===================" << std::endl
              << "               GAME Id  = " << getId() << std::endl
              << " \"SAVE file.txt\"       // This command game saving file.txt" << std::endl
              << " \"LOAD file.txt\"       // This command Load game named by file.txt" << std::endl
              << " \"--\"                  // To pre--" << std::endl
              << " \"---\"                // To pos--"  << std::endl
              << " \"SIZE\"                // To make resize the board " << std::endl
              << " \"MENU\"                // If you want to change game or quit " << std::endl
              << " ====================Have a nice game :)====================" << std::endl
              << "-------------------------------------------------------------" << std::endl;
    if (getSize() == 0){            //If user out the game entered again we have already this data so dont take them again
        setSize();
        setType();
    }
    getline(std::cin, free);
    if (getType() == 1)
        playWithFriend();
    else if (getType() == 2)
        playWithComp();
}

void Hex::playWithComp(){

    std::string command;
    int row;
    char clm;
    if (getFinish()){
        std::cout << *this;
        std::cout << "\nThis game already finih " << getWinner() << "Won" << std::endl
                  << "please choose another game\n\n";
    }

    while (!getFinish()){
        row = clm = -1;
        std::cout << *this;
        getCoordinate(celltype::user1,row,clm,command);     
        if (command == "MENU")
            return;
        if (row > -1 && clm > -1){
            play(row, clm);             //Player doing his move
            turn++;
            checkUser1();   //checking board
            if (getFinish()){
                std::cout << "PLAYER " << static_cast<char>(celltype::win1) << " WON" << std::endl;
                winner = celltype::win1;
                std::cout << *this;
                break;
            }
            play();                     //Computer doing its move
            turn++;
            checkUser2();   //checking board
            if(getFinish()){
                std::cout << "PLAYER " << static_cast<char>(celltype::win2) << " WON" << std::endl;
                winner = celltype::win2;
                std::cout << *this;
            }
        }
    }
}

void Hex::playWithFriend(){
    
    std::string command = "";
    int row;
    char clm;
    if (getFinish()){
        std::cout << *this;
        std::cout << "\nThis game already finih " << (char)getWinner() << "Won" << std::endl
                  << "please choose another game\n";
    }
    while (!getFinish()){
        row = clm = -1;
        std::cout << *this;
        if (getTurn() % 2 == 0)                                 //x is playing
            getCoordinate(celltype::user1,row,clm,command);
        else                                                    //o is playing 
            getCoordinate(celltype::user2, row, clm, command);
        if(command == "MENU")
            break;
        else if(row > -1 && clm > -1){          //Checking the coordinate according to the entered
            play(row,clm);
            if(turn %2 == 0)
                checkUser1();               //Checking game board is finish?
            else
                checkUser2();
            turn++;
        }
        if (getFinish()){                       //If the game finish printing here
            std::cout << "++++++++++++++++++++++++++++++++++++" << std::endl;
            if (getTurn() % 2 == 0){
                std::cout << "PLAYER " << static_cast<char>(celltype::win2) << " KAZANDI" << std::endl;
                winner = celltype::win1;
            }else{
                std::cout << "PLAYER " << static_cast<char>(celltype::win1) << " KAZANDI" << std::endl;
                winner = celltype::win2;
            }
            std::cout << "++++++++++++++++++++++++++++++++++++" << std::endl;
            std::cout << *this;
        }
    }
}

void Hex::getCoordinate(celltype player, int &row, char &clm, std::string& command){

    std::string line,tmp, fname, cmmd = "";
    std::vector<std::string> v;
    
    std::cout << "Player " << static_cast<char>(player) << std::endl        //get command or coordinate
              << "Enter coordinate :(ex: A 5) : ";
    getline(std::cin, line);

    std::stringstream str_strm(line);
    while(str_strm >> tmp)
        v.push_back(tmp);

    if (v[0] == "SAVE")       
        saveGame(v[1]);
    else if (v[0] == "LOAD")  {
        loadGame(v[1]);
        command = "MENU";
    }
    else if (v[0] == "--")     
        --*this;
    else if(v[0] == "---")     
        (*this)--;
    else if(v[0] == "SIZE") 
        resizeBoard(); 
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
        clm = line.at(0);
        row = sum;
    }
}

void Hex::play(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator(seed);

    int r = generator() % getSize();        //Computer playing as finding free cell
    int c = generator() % getSize();

    while (!checkCoordinate(r, c)){
        r = generator() % getSize();
        c = generator() % getSize();
    }
    std::cout << "Computer move : " << static_cast<char>(c + 65) << "," << r + 1 << std::endl;
    increaseStatic();
    savedCoordinates[turn] = {r,c};
    hexCells[r][c].setCoordinate(r, c, celltype::user2);
}

void Hex::play(int row,char clm){

    int r = row - 1;
    int c = clm - 'A' ;
    while (!checkCoordinate(r,c)){
       std::cout << "This is not valid coordinate enter coordinate not command : ";
       std::cin >> clm  >> row;
       r = row-1;
       c = clm - 'A';
       std::cin.clear();
       std::cin.ignore(512, '\n');
    }
    increaseStatic();   //Setting static varible
    savedCoordinates[turn] = {r, c};
    if(turn%2 == 0)
        hexCells[r][c].setCoordinate(r,c,celltype::user1);
    else
        hexCells[r][c].setCoordinate(r, c,celltype::user2);
}

void Hex::setCoordinate(int gx, int gy, celltype type){
    hexCells[gx][gy].setCoordinate(gx, gy, type);
}

void Hex::Cell::setCoordinate(int gx, int gy, celltype type){
    row = gx;
    clm = gy;
    cell = type;
}

bool Hex::checkCoordinate(const int &x, const int &y) const{
    return (getSize() > x && x >= 0 && getSize() > y && y >=0 && hexCells[x][y].getCell() == celltype::empty);
}

void Hex::popCell(){
    int row = savedCoordinates[getTurn()-1].row;            //deletting last element of dynamic saved arrays
    int clm = savedCoordinates[getTurn()-1].clm;
    hexCells[row][clm].setCoordinate(row,clm,celltype::empty);
    turn--;
    if(getType() == 2){
        row = savedCoordinates[getTurn()-1].row;
        clm = savedCoordinates[getTurn()-1].clm;
        hexCells[row][clm].setCoordinate(row,clm,celltype::empty);
        turn--;
    }
}

//OPERATOR OVERLODINGS
std::ostream &operator<<(std::ostream &sout, const Hex &game){

    if(&sout == &std::cout){    //(If using ostream)  ,here printing board and its features
        int c = 0;
        int free = 0;
        sout << "--------------------------------------------\n";   //Features
        sout << "ID   : " << game.getId() << "   " << "Size : " << game.getSize() << "   ";
        sout << "Type : " << game.getType() << "   " << "Turn : " << game.getTurn() << "   ";
        sout ;
        sout << "Winner: " << (char)game.getWinner() << "   " << "finish :" << game.getFinish() << std::endl;
        sout << game.scoreOfUsers() << std::endl;                   //Print Scores
        sout << "  ";
        for(char clm ='A' ;c<game.getSize();++c)
            sout << char(clm+c) << " ";
        sout << std::endl;   
        for(int i=0; i<game.getSize(); ++i){                        //Print Board
            sout << i+1 << " ";
            for (int j = 0; j < free; ++j)
                sout << " ";
            for (int j= 0; j< game.getSize(); ++j)
                sout << char(game.hexCells[i][j].getCell()) << " ";
            sout << std::endl;
            free++;
        }
        sout << "=====================================\n";
    } else {        // if ofsream returnin here

        sout << "Id: " << game.getId() << std::endl;            // Printing according to the saving 
        sout << "Size: " << game.getSize() << std::endl;        // file style
        sout << "Type: " << game.getType() << std::endl;
        sout << "Turn: " << game.getTurn() << std::endl;
        sout << "Winner: " << game.getWinner() << std::endl;
        sout << "Finish: " << game.getFinish() << std::endl;

        for (int i = 0; i < game.getTurn(); ++i){                //Choosen coordinate are saving
            int row = game.savedCoordinates[i].row,
                clm = game.savedCoordinates[i].clm;
            sout << row << " " << clm << " " << game.hexCells[row][clm].getCell() << std::endl;
        }

    }
    return sout;
}

std::ifstream& operator>>(std::ifstream &sin,Hex &game){

    std::string id, free;
    int size, type, turn, winner, position, r, c;
    celltype player;
    bool finish;

    game.count -= game.getTurn();       //setting static variable

    sin >> free >> id;                  //Filling loaded game features
    game.setId(id);
    sin >> free >> size;
    game.removeBoard();                 //Cleaning board
    game.setSize(size);
    game.fillCells();                   //Set the board again according to the new size
    sin >> free >> type;
    game.setType(type);
    sin >> free >> turn;
    game.setTurn(turn);
    game.count += turn;                 //setting static variable
    
    sin >> free >> winner;
    game.setWinner(celltype(winner));
    sin >> free >> finish;
    game.setFinish(finish);
    int i = 0;
    while(sin >> r >> c >> position){               //coordinates saving according to the savedCoordinate
        game.setCoordinate(r,c,celltype(position)); //We assaing them bact to board and savedCoordiante
        game.savedCoordinates[i].row = r;
        game.savedCoordinates[i].clm = c;
        i++;
    }

    return sin;
}

Hex& Hex::operator=(const Hex &rightSide){
  
    if(this != &rightSide){                 //We are doing deep copy for dynamic memory
        removeBoard();                      //delete all dynamic variable in class variable
        setSize(rightSide.getSize());       //set new size
        fillCells();                        //Filling them with .

        for(int i=0; i<getSize(); ++i){         //board set again according to the copied object
            for(int j=0; j<getSize(); ++j){
                if(rightSide.hexCells[i][j].getCell() != '.')
                    hexCells[i][j].setCoordinate(i, j, hexCells[i][j].getCell());
            }
        }
        setId(rightSide.getId());                   //Setting game features
        setType(rightSide.getType());
        setTurn(rightSide.getTurn());
        setWinner(rightSide.getWinner());
        setFinish(rightSide.getFinish());
    }
    return *this;
}

Hex& Hex::operator--(){
    if(turn == 0){          //To dont take segmentation fault
        std::cout << "There is no cell to delete\n";
        return *this;
    }
    popCell();              //Deleting last saved coordinate
    decreaseStatic();
    return *this;
}

Hex Hex::operator--(int){
    Hex tmp = (*this);
    if (turn == 0){         //To dont take segmentation fault
        std::cout << "There is no cell to delete\n";
        return *this;
    }
    popCell();              //deleting the last element of dynamic array
    decreaseStatic();
    return tmp;
}

bool operator==(const Hex &leftSide, const Hex &rightSide){
    int counter1 = 0, counter2 = 0;
    for(int i=0; i<leftSide.getSize(); ++i)             //Count filled cell in board 1
        for (int j = 0; j < leftSide.getSize(); ++j)
            if (leftSide.getCell(i, j) != celltype::empty)
                counter1++;  
                                                //sperate loop because the sizes are colud be different 
    
    for(int i=0; i<rightSide.getSize(); ++i)            //Count filled cell in board 2
        for(int j=0; j<rightSide.getSize(); ++j)
            if (rightSide.getCell(i, j) != celltype::empty)
                counter2++;

    return counter1 > counter2;
}

//STATIC VARIBLE
void Hex::increaseStatic(){
    count++;
}

void Hex::decreaseStatic(){
    count--;
}

int Hex::getStatic(){
    return count;
}

//CALCULATE SCORE
std::string Hex::scoreOfUsers()const {
    int score1 = 0,score2 = 0;
    for(int i=0; i<getSize(); ++i){             //Calculate the score of users
        for(int j=0; j<getSize(); ++j){
            ///User 1 score
            if ((hexCells[i][j].getCell() == celltype::user1) &&
                ((j < getSize()-1 && hexCells[i][j].getCell() == hexCells[i][j + 1].getCell()) ||
                 (j < getSize()-1 && i> 0 && hexCells[i][j].getCell() == hexCells[i - 1][j + 1].getCell()) ||
                 (i < getSize()-1 && hexCells[i][j].getCell() == hexCells[i + 1][j].getCell())))
            {    score1++;  }
            //User 2 score
            if ((hexCells[i][j].getCell() == celltype::user2 || hexCells[i][j].getCell() == celltype::win2) &&
                ((j < getSize()-1 && hexCells[i][j].getCell() == hexCells[i][j + 1].getCell()) ||
                 (i < getSize()-1 && hexCells[i][j].getCell() == hexCells[i + 1][j].getCell())  ||
                 (i < getSize()-1 && j > 0 && hexCells[i][j].getCell() == hexCells[i + 1][j - 1].getCell()) ||
                 (j > 0 && hexCells[i][j].getCell() == hexCells[i][j - 1].getCell())))
            {    score2++;  }
            //if the game has done we give the player max score winning character
            if (hexCells[i][j].getCell() == celltype::win1){
                score1 = getSize()*getSize();
                break;
            }
            if (hexCells[i][j].getCell() == celltype::win2){
                score2 = getSize()*getSize();
                break;
            }
        }
    }  

    return "Score of User 1(x): " + std::to_string(score1) + "\nScore of User 2(o): " + std::to_string(score2) + "\n";
}

//FINDING WAY
void Hex::checkUser2(){
    std::vector<std::vector<int>> way;          //We are checking first row for user 2 to find way
    for(int i=0; i<getSize(); ++i){
        Cell tmp = hexCells[0][i];
        if (tmp.getCell() == celltype::user2)
            findWay(tmp.getRow(), tmp.getClm(), way, celltype::user2);
    }
    
    for (std::vector<int> a : way)
        hexCells[a[0]][a[1]].setCoordinate(a[0], a[1], celltype::win2);
}

void Hex::checkUser1(){
    std::vector<std::vector<int>> way;          //We are checking first clm for user 1 to find way
    for (int i = 0; i < getSize(); ++i){
        if (hexCells[i][0].getCell() == celltype::user1)
            findWay(i, 0, way, celltype::user1);
    }
    for (std::vector<int> a : way)
        hexCells[a[0]][a[1]].setCoordinate(a[0], a[1], celltype::win1);
}

void Hex::findWay(int x, int y, std::vector<std::vector<int>> &way, celltype user){
    std::vector<int> tmp;
    tmp.push_back(x);       tmp.push_back(y);       //Keep passed way
    way.push_back(tmp);
    if (x == getSize() - 1 && user == celltype::user2){     //Winnig conndition for user 2
        setEndGame(true);
        return;
    }
    if (y == getSize() - 1 && user == celltype::user1){     //Winnig condition for user 1
        setEndGame(true);
        return;
    }
    //Serach way using backtracking algorithm
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

bool Hex::passed(std::vector<std::vector<int>> &way, int x, int y){
    bool check = true;
    for (std::vector<int> coordinate : way){        //Using findWay to dont pass same place
        if (coordinate[0] == x && coordinate[1] == y){
            check = false;
            break;
        }
    }
    return check;
}

bool Hex::boundary(const int &x, const int &y){
    return x >= 0 && x < getSize() && y >= 0 && y < getSize();
}
