
public class CellType {
	//Valid cell type
	public enum users{
		
		user1('x'),user2('o'),
		win1('X'),win2('O'),
		empty('.');
		
		private final char type;
	
		users(char c) {
			this.type = c;
		}
		public char getType() {
			return type;
		}
		
	}
}
