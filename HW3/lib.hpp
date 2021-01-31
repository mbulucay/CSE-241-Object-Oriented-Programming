#ifndef LIB_H_
#define LIB_H_ 

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>
using namespace std;

    enum celltype : char{
        empty = '.', user1 = 'x', user2 = 'o' ,win1 = 'X' ,win2 = 'O'
    };

    class Hex{

        public:
                Hex();                  //These are construct to create a game 
                Hex(string gname);
                Hex(int gsize);
                Hex(int gsize,int gtype);

                void play();                    //These are playing function       
                void play(char gx,int gy);     
                void playGame();                
                void playWithFriend();
                void playWithComp();
                void getCoordinate(celltype user,string &save,string &load,string &menu,string &cmpr,string &size);
                void setCoordinate(int gx,int gy,celltype type);
                bool checkCoordinate(const int &x,const int &y) const;

                void checkUser1();                  //Checking that game is over or not
                void checkUser2();
                void findWay(int x,int y,vector< vector<int> > &way,celltype user);
                bool boundary(const int &x,const int &y);
                bool passed(vector< vector<int> > &way, int x,int y);

                void saveGame(string &fname);       //This are make command taken from user
                void loadGame(string &fname);
                void compare();
                bool compareGame(const Hex &other)const;

                int filledCell()const;      //This is return filled cell in board      

                inline int getSize() const{return size;};       //These are to get private data
                inline int getType() const{return type;};
                inline bool getEndGame()const{return endGame;};
                inline int getTurn()const{return turn;};
                inline string getName()const{return gameName;}; 

                void fillCells();
                void reSize();
                void setSize();
                void setSize(int gsize){size = gsize;};
                void setType();
                void setType(int gtype) {type = gtype;};
                void setEndGame(bool gendGame){endGame = gendGame;};
                void disp() ;

                static void raiseStatic();
                static int getStatic();            
        private:
                class Cell{
                    private :
                        int x,y;
                        celltype cell;
                    public :
                        Cell(){
                            x = -1;         y = -1;
                            cell = celltype::empty;
                        }
      
                        Cell(int gx,int gy,celltype gcell = celltype::empty){
                            x = gx;         y = gy;
                            cell = gcell;
                        }
     
                        void setCoordinate(int gx,int gy,celltype type = celltype::empty);
                        inline char getCell() const{return cell;};
                        inline int getX() const{return x;};
                        inline int getY() const{return y;};
                };
               
                vector< vector<Cell> > hexCells;
                int size = 0, type = 0, turn = 0;
                static int cellcount;
                string gameName;
                char Winner;
                bool endGame = false;
    };

    int ReturnGameIndex(string name);
    void GameList();
    bool CheckName(string name);

    extern vector<Hex> GAMES;

#endif
