import java.util.ArrayList;

public interface GameFunctions {
	
	public void start();
	public void setProperties(String id,int size ,int turn ,int type ,boolean finish);
	public void fillBoard() ;
	
	//setting Functions
	public void setFinish(boolean finish2) ;
	public void setType(int type2) ;
	public void setTurn(int turn2) ;
	public void setSize(int size) ;
	public void setId(String id2) ;
	
	//getting Functions
	public int getBoardSize() ;
	public int getGameType() ;
	public int getTurn() ;
	public String getId() ;
	public boolean getFinish() ;
	
	//reseting board
	public void cleanBoard() ;
	
	//undo last move
	public void undo() ;
	
	//file properties
	public void saveGame(String fname) ;
	public void loadGame(String fname) ;
	
	//calculate score of user
	public void scoreOfUsers() ;
	
	//computer move
	public void play();
	
	//user move
	public void play(Cell cell) ;
	
	//isFinished moves
	public void checkUser2();
	public void checkUser1() ;
	public void findWay(int x, int y, ArrayList<Coordinate> way, char user) ;
	public boolean boundary(int x,int y);
	public boolean passed(ArrayList<Coordinate> way,int x, int y);
	
}
