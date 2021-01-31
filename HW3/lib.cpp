#include <iostream>
#include "lib.hpp"
using namespace std;

extern vector<Hex> GAMES;

///////////////////////////////////////////////////////////////////////////////// Constructs & Static variable set and get
Hex::Hex()
    :   size(0),type(0){}

Hex::Hex(string gname)
    :   gameName(gname),Winner(celltype::empty),size(0){};

Hex::Hex(int gsize) 
    :   size(gsize),type(2),Winner(celltype::empty)
    {fillCells();}

Hex::Hex(int gsize,int gtype) 
    :   size(gsize),type(gtype),Winner(celltype::empty)
    {fillCells();}

void Hex::raiseStatic(){
    cellcount++;
}
int Hex::getStatic(){
    return cellcount;
}  

///////////////////////////////////////////////////////////////////////////////// Global Functions

int ReturnGameIndex(string name){			//Search the index of the game which using name in all game 
    int index = -1;
    int i = 0;
    for (int i=0; i<GAMES.size(); ++i){
        if(GAMES.at(i).getName() == name){
            index = i;
            break;
        }
    }
    return index;
}

void GameList(){								//Print game list
    cout << "\n---------------------" << endl
         << "Existing game names :" << endl;
    int i=1;
    for(Hex tmp : GAMES){
        cout << "Game " << i  << " :"<< tmp.getName() << endl;  
        i++;
    }  
    cout << "----------------------" << endl;
}

bool CheckName(string name){					//Check the game is exist or not
    bool result = true;
    for (int i=0; i<GAMES.size(); ++i){
        if(GAMES.at(i).getName() == name)
            result = false;
    }
    return result;
}
///////////////////////////////////////////////////////////////////////////////// 
///////////////////////////////////////////////////////////////////////////////// Class Member Functions
///////////////////////////////////////////////////////////////////////////////// 
void Hex::playGame(){																			
	/*	
	This is the game menu it show the command list and their features
 	and setting the size and game type
	*/

    string free;
    cout <<"\n================Welcome The Hex Game Menu===================" << endl
         << " Game name  = " << getName()  << "\t\tsize : " << getSize()  << "x" << getSize() << "\ttype : " << getType() << endl
         << " SAVE file.txt      // This command game saving file.txt" << endl
         << " LOAD file.txt      // This command Load game named by file.txt" << endl
         << " CMPR               // To compare with another game " << endl
		 << " SIZE               // To make game resize" << endl        
         << " MENU               // If you want to change game or quit " << endl
         << " ====================Have a nice game :)====================" << endl
         << "-------------------------------------------------------------" << endl;		
    if(getSize() == 0){
        setSize();
        setType();
    }       
    getline(cin,free); 
    if(getType() == 1)
        playWithFriend();
    else if(getType() == 2)
        playWithComp();
}

void Hex::playWithFriend(){

    string save = " ",load = " ",menu = " ",cmpr = " ",size = " " ;
    
    if(getEndGame()){
        disp();    
        cout << "\nThis game already finih "<< Winner << " Won" << endl
             << "please choose another game\n" << endl; 
    }
    while (!getEndGame()){
        disp();            
        if(getTurn() % 2 == 0){
            getCoordinate(celltype::user1,save,load,menu,cmpr,size);		//This function set the command and coordinate 
            checkUser1();													//Checking is the win condition
        }    
        else{
            getCoordinate(celltype::user2,save,load,menu,cmpr,size);
            checkUser2();
        }
        if(getEndGame()){											//This is show us the if the game is finish
            if(getTurn() %2 == 0){
                cout << "PLAYER " << static_cast<char>(celltype::win1) << " KAZANDI" << endl;    
                Winner = celltype::win1;
            }
            else{             
                cout << "PLAYER " << static_cast<char>(celltype::win2) << " KAZANDI" << endl;    
                Winner = celltype::win2;
            }
            disp();
        }
        if(save != " "){ saveGame(save);							//If the user enter a command doing the entered command
            turn--;
        }
        else if(load != " "){ loadGame(load);
            turn--;
        }
        else if(cmpr != " "){ compare();
            turn--; 
        }
        else if(size != " "){ reSize();
        	turn--;  
        }
        else if(menu != " ")
            break; 

        save = " ";     load = " ";
        cmpr = " ";     menu = " ";
        size = " ";
        turn++;
    }
}

void Hex::playWithComp(){
    string save = " ",load = " ",menu = " ",cmpr = " ",size = " ";

    while(!getEndGame()){
        disp();
        getCoordinate(celltype::user1,save,load,menu,cmpr,size);				//Same with against the friend
        checkUser1();
        if(getEndGame()){
            cout << "PLAYER " << static_cast<char>(celltype::win1) << " WON" << endl;
            disp();
            break;
        }
        if(save != " ")
            saveGame(save);
        else if(load != " ")
            loadGame(load);
        else if(cmpr != " ")
            compare();   
        else if(size != " ")
        	reSize();             
        else if(menu != " ")
            break;
        else{
            play();
            checkUser2();
        }
        if(getEndGame()){
            cout << "COMPUTER HAS WON" << endl   
            << "PLAYER " << static_cast<char>(celltype::win2) << " WON" << endl;
            disp();
            break;
        }
        save = " ";     load = " ";        
        cmpr = " ";     menu = " ";
        size = " ";
    }
}

void Hex::play(char gx,int gy){

    int x = static_cast<int>(gx-65);
    gy -= 1;
    while(checkCoordinate(gy,x)){
        disp();
        cout << "This is not a valid coordinate " << endl
        	 << "Enter JUST coordinate not command" << endl
          	 << "Enter a valid coordinate(Ex:A 1) : ";
        cin >> gx >> gy;
        gy -= 1;
        x = static_cast<int>(gx-65);
        cin.clear();
        cin.ignore(512,'\n');
    }
    
    raiseStatic();													//this is add +1 to static cellCount varible each time

    if(turn % 2 == 0)												//Put the character according to the turn
        hexCells[gy][x].setCoordinate(gy,x,celltype::user1);
    else 
        hexCells[gy][x].setCoordinate(gy,x,celltype::user2);
}

void Hex::play(){

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    minstd_rand0 generator (seed);

    int x = generator()%size;										//these is make a coordinate to the computer
    int y = generator()%size;

    while(checkCoordinate(y,x)){
        x = generator()%size;
        y = generator()%size;
    }
    cout << "Computer move : " << static_cast<char>(x+65) << "," << y+1 << endl;
    raiseStatic();
    hexCells[y][x].setCoordinate(y,x,celltype::user2); 
}

void Hex::compare(){
    GameList();														//Print game list name to choose one of them
    string other;
    int index = 0;
    bool result;
    
    cout << "Write 'game name' you want to compare : ";
    cin >> other;
    index = ReturnGameIndex(other);									//We take the index of game
    if(index == -1){
        cout << "There is no game like " << other << endl;
        return;
    }
    cout  << "Game : " << GAMES.at(index).getName() << endl;
    GAMES.at(index).disp();    
    if(compareGame(GAMES.at(index)))								//It is comparing in this function
        cout << "Comparision is TRUE" << endl;
    else
        cout << "Comparision is FALSE" << endl;
    cout << "--------------------------" << endl;
    getline(cin, other);
}

bool Hex::compareGame(const Hex &other) const{
    int first = 0 ,second = 0;
    first = filledCell();

    for(vector<Cell> row: other.hexCells){							//It is returning filled cell in a game
        for(Cell cell : row){
            if(cell.getCell() == celltype::user1 || cell.getCell() == celltype::user2 || 
               cell.getCell() == celltype::win1 || cell.getCell() == celltype::win2){    
            	second++;
        	}
        }
    }
    return first > second;
}

void Hex::saveGame(string &fname){

    ofstream file(fname); 										//It is saving the game in a file

    file << "Size: " << size << endl;
    file << "Type: " << type << endl;
    file << "Turn: " << turn << endl; 

    for(int i=0; i<size;++i){									//ex: 5 6 x
        for(int j=0; j<size; ++j){
            if(hexCells[i][j].getCell() != celltype::empty)
                file << i << " " << j << " " << hexCells[i][j].getCell() << endl;
        }
    }

    cout << "Game Saved to " << fname << endl
         << "------------------------------\n";
    file.close();
}

void Hex::loadGame(string &fname){

    int x,y;
    char user;
    string fSize,fType,fTurn;

    ifstream file (fname);
    if(!file.is_open()){
        cerr << "File there is not exist" << endl
             << "Game continue" << endl;
        return;
    }

    int n1 = filledCell();
    hexCells.clear();										//Clear the ex game board

    file >> fSize >> size; 
    file >> fType >> type;
    file >> fTurn >> turn;
    fillCells();											//Filling with . according to the getting size

    int counter = 0;
    while(file >> x >> y >> user){							//Set the coordinate one bu one
        if(user == 'x')
            hexCells[x][y].setCoordinate(x,y,celltype::user1);
        else if(user == 'o')
            hexCells[x][y].setCoordinate(x,y,celltype::user2);
        counter++;
    }
    cellcount += counter - n1;							//Arrange the static varible according to loading game and deleting game
}

void Hex::setCoordinate(int gx,int gy,celltype type){
    raiseStatic();											//add +1 to static varible
    hexCells[gx][gy].setCoordinate(gx,gy,type); 			//Set the coordinate according to the user
}

void Hex::Cell::setCoordinate(int gx,int gy,celltype type){
    x = gx;     y = gy;												//Set cell varible
    cell = type;    
}

void Hex::getCoordinate(celltype user,string &save,string &load,string &menu,string &cmpr,string &size){
    
    string line,fname,cmmd = "";
    int y = 0,x;
    
    cout << "Player "<< static_cast<char>(user) << endl 
         << "Enter coordinate :(ex: A 5) : ";
    getline(cin,line);
    
    if(line.length() > 3)
        cmmd = line.substr(0,4);										//split the getting string
    
    if(cmmd == "SAVE"){
        auto pos = line.find(" ");										//get file name
        fname = line.substr(pos+1,line.length());
        save = fname;
    }
    else if(cmmd == "LOAD"){
        auto pos = line.find(" ");
        fname = line.substr(pos+1,line.length());
        load = fname;
    }
    else if(cmmd == "CMPR")												//set command if the user enter
        cmpr = "CMPR";
    else if(cmmd == "SIZE")
    	size = "SIZE";
    else if(cmmd == "MENU")
        menu = "MENU";
    else{
        int sum = 0;
        for(char i : line){
            if (i >= '0' && i <= '9')
                sum = sum * 10 + i - '0';
            if(i == '-'){
                sum = 0;          					//It is for the negative numbers 
                break;
            }    
        }
        play(line.at(0),sum);
    }
}

bool Hex::checkCoordinate(const int &y,const int &x) const{
    return (x >= getSize() || y >= getSize() || x < 0 || y < 0 || hexCells[y][x].getCell() != celltype::empty);
}

int Hex::filledCell() const{							//this return the filled cell in a game
    int counter = 0;
    for(vector<Cell> row : hexCells){
        for(Cell cell : row){
            if(cell.getCell() != celltype::empty)
                counter++;
        }
    }
    return counter;
}

void Hex::setSize(){
    int s1,s2;
    char cross;
    cout << "Please enter the size (Ex:5x5) : ";					//Set the game size
    cin >> s1 >> cross >> s2;
    if(s1 > 4 && s2 == s1 && (cross == 'x' || cross == 'X')){
        setSize(s1); 
        fillCells(); 
    } 
    else{
        cout << "\nUnvalid size enter again ";
        setSize();
    }
}

void Hex::setType(){
    int gtype;
    cout<< "1-> Play with friend" << endl							//Set the game type
        << "2-> Play with computer" << endl    
        << "Please, Enter a game type : ";
    cin >> gtype;
    if(gtype == 1 || gtype == 2)
    	setType(gtype);
    else{
	    cout << "============================" << endl;
    	cout << "Unvalid type enter again " << endl;
    	setType();
    }
	cout << "============================" << endl;
}

void Hex::reSize(){
	string free;
    cellcount -= filledCell();					//Set the static varible first
    hexCells.clear();							//Then clear board
   	setSize();									//Get new size	
   	getline(cin,free);
}

void  Hex::fillCells(){

    Cell tmp;    
    vector<Hex::Cell> row;						//This is filling all cell with '.'
    for(int i=0; i < getSize(); ++i){
        for(int j=0; j < getSize(); ++j){
            tmp.setCoordinate(i,j);     
            row.push_back(tmp);    
        }
        hexCells.push_back(row);
        row.clear();
   }
}

void Hex::disp(){
    int i = 1;										//Printing board
    cout << "  ";
    for(char a = 'a',k = 0; k < getSize(); a++,++k )
        cout << a << " " ;
    cout <<endl;
    
    for(auto row : hexCells){
        cout << i;
        for(int j = 0; j<i; ++j)
            cout << " ";
        for(auto clm: row){
            
            cout << clm.getCell() << " ";
        }
        i++;
        cout << endl;
    }
    cout << "-----------------------------" << endl;
}

void Hex::checkUser2(){													//After that checking the winning status 
    vector< vector<int> > way;
    for(Cell tmp : hexCells[0]){
        if(tmp.getCell() == celltype::user2)
            findWay(tmp.getX(), tmp.getY(), way, celltype::user2);		//If it find the o in first row is send to check is there a way to winnig
    }
    for(vector<int> a : way)											//This is making bigger character winnig way
        hexCells[a[0]][a[1]].setCoordinate(a[0], a[1], celltype::win2);
}

void Hex::checkUser1(){
    
    vector< vector<int> > way;
    for(int i=0; i<getSize(); ++i){										//If it find the x in first column is send to check is there a way to winnig
        if(hexCells[i][0].getCell() == celltype::user1)
            findWay(i, 0, way, celltype::user1);
    }
    for(vector<int> a : way)											//This is making bigger character winnig way
        hexCells[a[0]][a[1]].setCoordinate(a[0], a[1], celltype::win1);
}

void Hex::findWay(int x,int y,vector< vector<int> > &way, celltype user){
    
    vector<int> tmp;
    tmp.push_back(x);   tmp.push_back(y);
    way.push_back(tmp);
    //cout << x << "," << y << endl;
    if(x == getSize()-1 && user == celltype::user2){    setEndGame(true);		//Set the class varible as finished the game
        return;
    }

    if(y == getSize()-1 && user == celltype::user1){    setEndGame(true);;
        return;
    }    
    
    if( boundary(x-1,y+1) && passed(way, x-1, y+1)  && hexCells[x-1][y+1].getCell() == user)
        findWay(x-1,y+1,way,user);
    if( boundary(x,y+1) && passed(way, x, y+1)  && hexCells[x][y+1].getCell() == user)
        findWay(x,y+1,way,user);
    if( boundary(x+1,y) && passed(way, x+1, y) && hexCells[x+1][y].getCell() == user)
        findWay(x+1,y,way,user);
    if( boundary(x+1,y-1) && passed(way, x+1, y-1)  && hexCells[x+1][y-1].getCell() == user)
        findWay(x+1,y-1,way,user);
    if( boundary(x,y-1) && passed(way, x, y-1)  && hexCells[x][y-1].getCell() == user)
        findWay(x,y-1,way,user);
    if( boundary(x-1,y) && passed(way, x-1, y)  && hexCells[x-1][y].getCell() == user)
        findWay(x-1,y,way,user);
    if(getEndGame())
        return;

    way.pop_back();    
}

bool Hex::passed(vector< vector<int> > &way, int x,int y){			//Checking the passed coordinate
    bool check = true;
    for(vector<int> coordinate : way){
        if(coordinate[0] == x && coordinate[1] == y){
            check = false;
            break;
        }
    }
    return check;
}

bool Hex::boundary(const int &x,const int &y){						//Determine the boundary
    return x>=0 && x<size && y>=0 && y<size;
}
