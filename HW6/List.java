
public interface List<E> extends Collection<E>  {

	void add(int index,E e) throws Exception;
	boolean	addAll(int index, Collection<E> c) throws Exception;
	E get(int index) throws Exception;
	int indexOf(E e) throws Exception;
	E set(int index,E e) throws Exception;
	List<E> subList(int fromIndex, int toIndex);
	int lastIndexOf(E e);
	
	
}
