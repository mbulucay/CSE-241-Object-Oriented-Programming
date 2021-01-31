#ifndef LIB_
#define LIB_

#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>

enum celltype : char {
    empty = '.',    user1 = 'x',    user2 = 'o',    win1 = 'X',     win2 = 'O'
};

struct coorinate{
    int row,clm;
};

class Hex
{
    public:
        //CONSTRUCTORS & DECONSTRUCTOR
        Hex();
        Hex(std::string& id);
        explicit Hex(std::string& id, int size);
        explicit Hex(std::string& id, int size, int type,int turn,celltype winner,bool finish);
        Hex(const Hex &rightSide);
        ~Hex();
        
        //BASE GETTERS
        inline std::string getId() const { return id; };
        inline int getSize() const { return boardSize; };
        inline int getType() const { return gameType; };
        inline celltype getCell(int row, int clm) const { return hexCells[row][clm].getCell(); };
        inline int getTurn() const { return turn; };
        inline celltype getWinner() const { return winner; };
        inline bool getFinish() const { return finish; };
        
        //BASE SETTERS
        void fillCells();
        void setId(std::string gid) {id = gid;};
        void setSize();
        void setSize(int gsize) { boardSize = gsize; }; 
        void setType();
        void setType(int gtype) { gameType = gtype; };
        void setTurn(int gturn) { turn = gturn;};
        void setWinner(celltype gwinner) { winner = gwinner;} ;
        void setFinish(bool gfinish) { finish = gfinish;};

        //BOARD FUNCTION
        void removeBoard();         //deleting board
        void cleanBoard();          //all cell setting with '.'
        void resizeBoard();     
        
        //SAVE & LOAD FUNCTIONS
        void saveGame(const std::string &fname)const;
        void loadGame(const std::string &fname);

        //GAME FUNCTIONS
        void playGame();
        void playWithFriend();
        void playWithComp();
        void play();
        void play(int row, char clm);
        std::string scoreOfUsers() const;
        void popCell();

        //COORDINATE FUNCTIONS
        void getCoordinate(celltype player,int& row, char& clm,std::string& command);
        bool checkCoordinate(const int &y, const int &x) const;
        void setCoordinate(int gx, int gy, celltype type);
        void setEndGame(bool gendGame) { finish = gendGame; };

        //OPERATOR OVERLOADINGS
        friend std::ostream& operator<<(std::ostream &sout,const Hex &game);
        friend std::ifstream &operator>>(std::ifstream &sin, Hex &game);
        Hex& operator=(const Hex& rightSide);
        Hex& operator--();
        Hex operator--(int);
        friend bool operator==(const Hex &leftSide, const Hex &rightSide);

        //STATIC VARIABLE
        static void increaseStatic();
        static void decreaseStatic();
        static int getStatic();

        //FINDING WAY
        void checkUser1();
        void checkUser2();
        void findWay(int x, int y, std::vector<std::vector<int> > &way, celltype user);
        bool boundary(const int &x, const int &y);
        bool passed(std::vector<std::vector<int> > &way, int x, int y);
        
        //CELL CLASS
        class Cell{
            public:
                Cell();
                inline celltype getCell() { return cell;};
                void setCoordinate(int gx, int gy, celltype type);
                inline int getRow() const { return row; };
                inline int getClm() const { return clm; };

            private:
                int clm, row;
                celltype cell;
        };

    private:
        
        Cell **hexCells;
        coorinate* savedCoordinates;
        std::string id;
        int boardSize, gameType, turn;
        celltype winner = celltype::empty;
        bool finish = false;
        static int count;
};

void CompareTwoGames(const std::vector<Hex*> &GAMES, int &game1, int &game2);    //game1 and 2 index of choosen games
void GameList(const std::vector<Hex*> &GAMES);
int ReturnGameIndex(const std::vector<Hex*> &GAMES, std::string name);
bool CheckName(const std::vector<Hex*> &GAMES, std::string name);       //checking the game is exsit or not return index

int GetOperation();
void PlayAnExistingGame(std::vector<Hex*> &GAMES);
void CompareTwoGames(const std::vector<Hex*> &GAMES);
void PushGAME(std::vector<Hex*> &GAMES);        //add new game to GAMES
void CloseProgram();

#endif