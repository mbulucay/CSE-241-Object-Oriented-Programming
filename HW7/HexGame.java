import java.util.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.*; 
import java.io.*;

public class HexGame implements GameFunctions,Cloneable,MouseListener{

	private String id;
	private Cell hexCells[][],undo,save,load,reset,clone; 
	private ArrayList<Coordinate> savedCoordinate = new ArrayList<>();
	int boardSize, gameType, turn = 0,scoreO,scoreX;
	boolean finish = false;
	private JFrame frame;
	private JTextField fname,scoreXtext,scoreOtext;
	static int countOfCell;
	static int countOfGame;
	
	HexGame(){}
	HexGame(String id, int size,int turn,int type,boolean bool,boolean visiblty){
		//setting all properties 
		setProperties(id,size,turn,type,bool);
		//adding required properties buttons
		start();
		//filling board with buttons and hexCells
		fillBoard();
		frame.setVisible(visiblty);
	}
	
	public void start() {	
		
		//Filling frame with buttons
		frame = new JFrame("Hex Game Board");
		frame.setSize(getBoardSize()*150, getBoardSize()*75);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(null);

		//wanted properties
		undo = new Cell(-1,-1);
		undo.setText("UNDO");
		undo.setBounds((getBoardSize()+5)*50,50, 100, 30);
		undo.addMouseListener(this);
		save = new Cell(-2,-2);
		save.setText("SAVE");
		save.setBounds((getBoardSize()+5)*50,80,100,30);
		save.addMouseListener(this);
		load = new Cell(-3,-3);
		load.setText("LOAD");
		load.setBounds((getBoardSize()+5)*50,110,100,30);
		load.addMouseListener(this);
		reset = new Cell(-4,-4);
		reset.setText("RESET");
		reset.setBounds((getBoardSize()+5)*50,140,100,30);
		reset.addMouseListener(this);
		clone = new Cell(-5,-5);
		clone.setText("CLONE");
		clone.setBounds((getBoardSize()+5)*50, 170, 100, 30);
		clone.addMouseListener(this);
		fname = new JTextField(".txt");
		fname.setBounds((getBoardSize()+5)*50, 230, 100, 30);
		scoreXtext = new JTextField();
		scoreXtext.setBounds((getBoardSize()+10)*50, 50, 50, 30);
		scoreXtext.setEditable(false);
		scoreOtext = new JTextField();
		scoreOtext.setBounds((getBoardSize()+10)*50, 100, 50, 30);
		scoreOtext.setEditable(false);
		
		
		
		//adding text to frame
		JLabel label = new JLabel("Enter the file name :");
		label.setBounds((getBoardSize()+5)*50, 200, 250, 30);
		frame.add(label);
		label = new JLabel("Score X: ");
		label.setBounds((getBoardSize()+8)*50,50, 75, 30);
		frame.add(label);
		label = new JLabel("Score O: ");
		label.setBounds((getBoardSize()+8)*50,100, 75, 30);
		frame.add(label);
		label = new JLabel("Muhammed Bedir ULUCAY");
		label.setBounds((getBoardSize()+5)*63, (getBoardSize()+5)*33, 180, 30);
		frame.add(label);
	}
	
	public void setProperties(String id,int size ,int turn ,int type ,boolean finish) {
		setId(id);			//setting all properties one by one
		setSize(size);
		setTurn(turn);
		setType(type);
		setFinish(finish);
	}
	
	public void fillBoard() {
		Cell board[][] = new Cell[getBoardSize()][getBoardSize()];
		int x = 50,y = 50;
		//adding buttons to frame
		frame.add(undo);
		frame.add(save);
		frame.add(load);
		frame.add(reset);
		frame.add(fname);
		frame.add(clone);
		frame.add(scoreOtext);
		frame.add(scoreXtext);
		//filling game motor hexCells and jbuttons on frame
		for(int i=0; i<getBoardSize(); ++i) {
			x = 50 + i*25;
			for(int j=0; j<getBoardSize(); ++j) { 
				Cell tmp = new Cell(i,j);
				tmp.setBounds(x, y, 50, 50);
				frame.add(tmp);
				tmp.addMouseListener(this);
				board[i][j] = tmp;
				x += 50;
			}
			y +=50;
		}
		hexCells = board;
	}
	
	//setting Functions
	public void setFinish(boolean finish2) {
		finish = finish2;	
	}
	public void setType(int type2) {
		gameType = type2;
	}
	public void setTurn(int turn2) {
		turn = turn2;
	}
	public void setSize(int size) {
		boardSize = size;
	}
	public void setId(String id2) {
		id = id2;
	}
	
	//getting Functions
	public int getBoardSize() {
		return boardSize;
	}
	public int getGameType() {
		return gameType;
	}
	public int getTurn() {
		return turn;
	}
	public String getId() {
		return id;
	}
	public boolean getFinish() {
		return finish;
	}
	
	
	public void cleanBoard() {
		//reseting board
		for(int i=0; i<getBoardSize(); ++i) {
			for(int j=0; j<getBoardSize(); ++j) {
				hexCells[i][j].setCellType('.');
				hexCells[i][j].setText(".");
			}
		}
		turn = 0;
		savedCoordinate.clear();
	}

	public void undo() {
		//removing last element on board and buttons
		try {
			Coordinate tmp = savedCoordinate.get(getTurn()-1); 
			hexCells[tmp.getRow()][tmp.getColumn()].setCellType('0');
			hexCells[tmp.getRow()][tmp.getColumn()].setText(".");
			turn--;
			savedCoordinate.remove(turn);
			if(getGameType() == 2) {
				tmp = savedCoordinate.get(getTurn()-1); 
				hexCells[tmp.getRow()][tmp.getColumn()].setCellType('0');
				hexCells[tmp.getRow()][tmp.getColumn()].setText(".");
				turn--;
				savedCoordinate.remove(turn);
			}
		}catch(Exception e) {
			System.out.println("There is no back move");
		}
	}
	
	public void saveGame(String fname) {
		//saving game wanted style
		System.out.println(fname);
		try {
			
			File file = new File(fname);
			if(!file.exists()) 
				file.createNewFile();
			//properties
			FileWriter fwriter = new FileWriter(file,false);
			fwriter.write(getId() + "\n"+
						  String.valueOf(getBoardSize()) + "\n"+
						  String.valueOf(getGameType()) + "\n" +
						  String.valueOf(getTurn()) + "\n");
			
			int val = (getFinish()) ? 1 : 0;
			fwriter.write(String.valueOf(val) + "\n");
			
			//cells
			for(int i=0; i<savedCoordinate.size();++i) {
				fwriter.write(String.valueOf(savedCoordinate.get(i).getRow()) + " " + 
						String.valueOf(savedCoordinate.get(i).getColumn())+ "\n");
			}
			
			fwriter.close();
		
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void loadGame(String fname) {
		try {
			//getting properties
			System.out.println(fname);
			File file = new File(fname);
			Scanner sc = new Scanner(file);
			String str = sc.nextLine();
			int size = sc.nextInt();
			int type = sc.nextInt();
			int turn = sc.nextInt();
			boolean val = (sc.nextInt() != 0);

			HexGame loaded = new HexGame(str,size,type,turn,val,false);
			int i = 0;
			sc.nextLine();
			
			//getting coordinates queue
			while (sc.hasNextLine()) {
				
				String line = sc.nextLine();
				String[] arr = line.split(" ");
				int row = Integer.parseInt(arr[0]);
				int column = Integer.parseInt(arr[1]);
				
				if(i%2 == 0) {
					loaded.hexCells[row][column].setCellType('x');
					loaded.hexCells[row][column].setText("x");			
				}
				else {			
					loaded.hexCells[row][column].setCellType('o');
					loaded.hexCells[row][column].setText("o");
				}
				i++;
			} 
			
			System.out.println(loaded);
			loaded.frame.setVisible(true);
			sc.close();
		
		}catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	
	public void scoreOfUsers() {
		int score1 = 0,score2 = 0;
		for(int i=0; i<getBoardSize(); ++i){             //Calculate the score of users
	        for(int j=0; j<getBoardSize(); ++j){
	            ///User 1 score
	            if ((hexCells[i][j].getCellType() == 'x') &&
	                ((j < getBoardSize()-1 && hexCells[i][j].getCellType() == hexCells[i][j + 1].getCellType()) ||
	                 (j < getBoardSize()-1 && i> 0 && hexCells[i][j].getCellType() == hexCells[i - 1][j + 1].getCellType()) ||
	                 (i < getBoardSize()-1 && hexCells[i][j].getCellType() == hexCells[i + 1][j].getCellType())))
	            {    score1++;  }
	            //User 2 score
	            if ((hexCells[i][j].getCellType() == 'o' || hexCells[i][j].getCellType() == 'O') &&
	                ((j < getBoardSize()-1 && hexCells[i][j].getCellType() == hexCells[i][j + 1].getCellType()) ||
	                 (i < getBoardSize()-1 && hexCells[i][j].getCellType() == hexCells[i + 1][j].getCellType())  ||
	                 (i < getBoardSize()-1 && j > 0 && hexCells[i][j].getCellType() == hexCells[i + 1][j - 1].getCellType()) ||
	                 (j > 0 && hexCells[i][j].getCellType() == hexCells[i][j - 1].getCellType())))
	            {    score2++;  }
	            //if the game has done we give the player max score winning character
	            if (hexCells[i][j].getCellType() == 'X'){
	                score1 = getBoardSize()*getBoardSize();
	                break;
	            }
	            if (hexCells[i][j].getCellType() == 'O'){
	                score2 = getBoardSize()*getBoardSize();
	                break;
	            }
	        }
	    }  
		scoreX = score1;
		scoreO = score2;
	}
	
	public void play() {
		
		//Computer make move finding valid cell
		
		Random rand = new Random(); 
		int row = rand.nextInt(getBoardSize());
		int column = rand.nextInt(getBoardSize());
		
		while(hexCells[row][column].getCellType() != '.') {
			row =  rand.nextInt(getBoardSize());
			column = rand.nextInt(getBoardSize());
		}
		
		Cell cell = hexCells[row][column];
		cell.setCellType('o');
		cell.setText("o");
		//adding coordiantes
		savedCoordinate.add(new Coordinate(cell.getRow(),cell.getColumn()));
		turn++;
	}
	
	public void play(Cell cell) {
		//user move are sending buttons and hexCells
		if(turn %2 == 0) {
			cell.setCellType('x');
			cell.setText("x");
		}else{
			cell.setCellType('o');
			cell.setText("o");
		}
		//adding coordiantes
		savedCoordinate.add(new Coordinate(cell.getRow(),cell.getColumn()));
		turn++;
	}
	
	public void checkUser2() {
		
		//check game is finish for user2 (o)
		ArrayList<Coordinate> way = new ArrayList<>();
		for(int i=0; i<getBoardSize(); ++i)
			if(hexCells[0][i].getCellType() == 'o')
				findWay(0,i,way,'o');
		
		//if win make O finished way
		for(Coordinate coordiante : way) {
			hexCells[coordiante.getRow()][coordiante.getColumn()].setCellType('O');
			hexCells[coordiante.getRow()][coordiante.getColumn()].setText("O");
		}	
	}
	
	public void checkUser1() {
		
		//check game is finished for user1 (x)
		ArrayList<Coordinate> way = new ArrayList<>();
		for(int i=0; i<getBoardSize(); ++i)
			if(hexCells[i][0].getCellType() == 'x')
				findWay(i,0,way,'x');

		//if win make X finished way
		for(Coordinate coordiante : way) {
			hexCells[coordiante.getRow()][coordiante.getColumn()].setCellType('X');
			hexCells[coordiante.getRow()][coordiante.getColumn()].setText("X");
		}	
	}
	
	public void findWay(int x, int y, ArrayList<Coordinate> way, char user) {
		
		//Check game is finish using backtracking algorithm
		
		Coordinate tmp = new Coordinate();
		tmp.setRow(x);		tmp.setColumn(y);
		way.add(tmp);
		if(x == getBoardSize()-1 && user == 'o') {
			setFinish(true);
			return;
		}
		if(y == getBoardSize()-1 && user == 'x') {
			setFinish(true);
			return;
		}
		
		//Checking neighbor of current cell
		if (boundary(x - 1, y + 1) && passed(way, x - 1, y + 1) && hexCells[x - 1][y + 1].getCellType() == user)
		    findWay(x - 1, y + 1, way, user);
	    if (boundary(x, y + 1) && passed(way, x, y + 1) && hexCells[x][y + 1].getCellType() == user)
	        findWay(x, y + 1, way, user);
	    if (boundary(x + 1, y) && passed(way, x + 1, y) && hexCells[x + 1][y].getCellType() == user)
	        findWay(x + 1, y, way, user);
	    if (boundary(x + 1, y - 1) && passed(way, x + 1, y - 1) && hexCells[x + 1][y - 1].getCellType() == user)
	        findWay(x + 1, y - 1, way, user);
	    if (boundary(x, y - 1) && passed(way, x, y - 1) && hexCells[x][y - 1].getCellType() == user)
	        findWay(x, y - 1, way, user);
	    if (boundary(x - 1, y) && passed(way, x - 1, y) && hexCells[x - 1][y].getCellType() == user)
	        findWay(x - 1, y, way, user);
	    if (getFinish())
	        return;
		
		way.remove(way.size()-1);
	}
	
	public boolean boundary(int x,int y) {
		//is check x an y are boundary 
		return x>=0 && x<getBoardSize() && y>=0 && y<getBoardSize();
	}
	
	public boolean passed(ArrayList<Coordinate> way,int x, int y) {
		//If we passed a coordinate return false other wise return true
		for(Coordinate coordinate : way)
			if(coordinate.getRow() == x && coordinate.getColumn() == y)
				return false;
		return true;
	}
	
	public HexGame clone() {
		
		HexGame tmp = null;
		try {
			//cloning obj
			//this are primitive copying
			tmp = (HexGame)super.clone();
			tmp.id = new String(getId());
			
			//setting new instance variable
			Cell board[][] = new Cell[getBoardSize()][getBoardSize()];
			tmp.hexCells = board;
			
			tmp.start();
			tmp.fillBoard();
			
			ArrayList<Coordinate> tmpSavedCoordiante = new ArrayList<>();
			for(int i=0; i<savedCoordinate.size(); ++i)
				tmpSavedCoordiante.add(savedCoordinate.get(i));
			
			for(int i=0; i<savedCoordinate.size(); ++i) {
				int row = savedCoordinate.get(i).getRow();
				int column = savedCoordinate.get(i).getColumn();
				if(i%2 == 0) {
					tmp.hexCells[row][column].setCellType('x');
					tmp.hexCells[row][column].setText("x");
				}else {
					tmp.hexCells[row][column].setCellType('o');
					tmp.hexCells[row][column].setText("o");
				}
			}
			//adding all frame
			tmp.frame.add(tmp.undo);
			tmp.frame.add(tmp.save);
			tmp.frame.add(tmp.load);
			tmp.frame.add(tmp.reset);
			tmp.frame.add(tmp.fname);
			tmp.frame.add(tmp.scoreOtext);
			tmp.frame.add(tmp.scoreXtext);
			
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		
		return tmp;
	}
	
	public boolean equals(HexGame other) {
		//checking games are equal
		if(getTurn() == other.getTurn())
			return true;
		else 
			return false;
	}
	
	public int hashCode() {
		//returning hashCode of game
		return getTurn();
	}
	
	@Override
	public String toString() {
		
		//printing board wanted style
		StringBuilder str = new StringBuilder();
		int ch = 65;
		int free = 0;
		str.append("  ");
		for(int i=0; i<getBoardSize(); ++i)
			str.append((char)(ch+i) + " ");
		str.append("\n");	
		
		for(int i=0; i<getBoardSize(); ++i){                        //Print Board
            str.append(i+1);
            str.append(" ");
            
            for (int j = 0; j < free; ++j)
            	str.append(" ");
            for (int j= 0; j< getBoardSize(); ++j) {
                str.append(hexCells[i][j].getCellType());
                str.append(" ");
            }
    		str.append("\n");	
            free++;
        }
		
		return str.toString();
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
				
		scoreOfUsers();
		scoreXtext.setText(String.valueOf(scoreX));
		scoreOtext.setText(String.valueOf(scoreO));
		//checking cell which clicked
		if(getFinish()) {
			JOptionPane.showMessageDialog(frame, "The current game already done");
			return;
		}
		
		Cell currentCell = (Cell) e.getComponent();
		
		if(currentCell.getRow() == -1) {
			undo();
			return;
		}else if(currentCell.getRow() == -2) {
			saveGame(fname.getText());
			return;
		}else if(currentCell.getRow() == -3) {
			loadGame(fname.getText());
			return;
		}else if(currentCell.getRow() == -4) {
			cleanBoard();
			return;
		}else if(currentCell.getRow() == -5) {
			HexGame tmp = this.clone();
			tmp.frame.setVisible(true);
			return;
		}
		
		if(currentCell.getCellType() == '.' && e.getButton() == 1) 
			play(currentCell);
		checkUser1();
		if(getFinish()) {
			JOptionPane.showMessageDialog(frame, "PLAYER X HAS WON");
			return;
		}
		try {
			Thread.sleep(50);
		} catch (InterruptedException e1) {
			e1.printStackTrace();
		}
		if(getGameType() == 2) 
			play();

		checkUser2();
		if(getFinish()) { 
			JOptionPane.showMessageDialog(frame, "PLAYER O HAS WON");
			return;
		}
		try {
			Thread.sleep(50);
		} catch (InterruptedException e1) {
			e1.printStackTrace();
		}

		System.out.println(this);
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
	}
	@Override
	
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
	}
	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
	}
	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
	}
	
}
