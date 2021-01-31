import javax.swing.JButton;

@SuppressWarnings("serial")
public class Cell extends JButton{
	
	
	private Coordinate coordiante;
	private CellType.users type;
	
	//cell constructor1
	Cell(int row, int column){
		super(".");
		coordiante = new Coordinate(row,column);
		type = CellType.users.empty;
	}
	//cell constructor2
	Cell(int row, int column , char c){
		super();
		coordiante = new Coordinate(row,column);
		if(c == 'x')
			type = CellType.users.user1;
		else if(c == 'o')
			type = CellType.users.user2;
		else if(c == 'X')
			type = CellType.users.win1;
		else if(c == 'O')
			type = CellType.users.win2;
		else 
			type = CellType.users.empty;
	}
	
	//get and cell properties of cell object
	char getCellType() {
		return type.getType();
	}
	
	void setCellType(char c) {		
		if(c == 'x')
			type = CellType.users.user1;
		else if(c == 'o')
			type = CellType.users.user2;
		else if(c == 'X')
			type = CellType.users.win1;
		else if(c == 'O')
			type = CellType.users.win2;
		else 
			type = CellType.users.empty;
	}
	
	void setRow(int row) {
		coordiante.setRow(row);
	}
	
	void setColumn(int column) {
		coordiante.setColumn(column);
	}
	
	int getColumn() {
		return coordiante.getColumn();
	}
	int getRow() {
		return coordiante.getRow();
	}
	
}
