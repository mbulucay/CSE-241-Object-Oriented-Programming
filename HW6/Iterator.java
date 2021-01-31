
public interface Iterator<E> {
	
	boolean hasNext();
	E next() throws Exception;
	void remove() throws Exception;

}
