
public interface Queue <E> extends Collection<E>,Iterator<E> {

	public boolean add(E e)throws Exception;
	public E element() throws Exception;
	public boolean offer(E e) throws Exception;
	public E peek();
	public E poll();
	public void remove() throws Exception;
}
