
public interface Collection<E> extends Iterator<E>{

	Iterator<E> iterator();
	boolean add(E e) throws Exception;
	boolean addAll(Collection<E> c) throws Exception;
	void clear() throws Exception;
	boolean contains(E e) throws Exception;
	boolean containsAll(Collection<E> c) throws Exception;
	boolean isEmpty();
	boolean remove(E e) throws Exception;
	boolean removeAll(Collection<E> c) throws Exception;
	boolean retainAll(Collection<E> c) throws Exception;
	int size();
	
}
