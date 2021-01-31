import java.util.NoSuchElementException;

public class LinkedList<E> implements List<E>,Queue<E>{

	private static final Exception IllegalArgumentException = null;
	private static final Exception ClassCastException = null;
	private static final Exception UnsupportedOperationException = null;
	private static final Exception IndexOutOfBoundsException = null;
	private static final Exception NullPointerException = null;
	private static final Exception IllegalStateException = null;
	private static final Exception NoSuchElementException = null;
	private Node<E> head;
	private Node<E> tail;
	private Node<E> iter;
	
	private int size;
	
	LinkedList(){
		head = null;
		tail = head;
		iter = head;
	}
		
	@Override
	public boolean hasNext() {		//tell us is linked list finish on iterator	
		return iter != null;
	}

	@Override
	public E next() {			//returning current iterator data
		E tmp = iter.data;
		iter = iter.next;
		return tmp;
	}

	@Override
	public Iterator<E> iterator() {		//returning iterator for current linked list
		iter = head;
		return this;
	}

	@Override
	public boolean add(E e) throws Exception {
		
		try {
			//adding last element of linked list
			Node <E> element = new Node<E>(e);		
		
			if(head == null) {
				head = element;
				tail = head;
			}else{
				tail.next = element;
				tail = tail.next;
			}
			size++;
			iter = head;
			return true;
		}catch(IllegalStateException ise) {
			throw IllegalStateException;
		}catch(ClassCastException cce) {
			throw ClassCastException;
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}catch(IllegalArgumentException iae) {
			throw IllegalArgumentException;
		}
	}

	@Override
	public boolean addAll(Collection<E> c) throws Exception {
		
		try {
			//adding all element in collection to the linked list
			while(c.hasNext()) 					
				add(c.next());
			return true;
		} catch (UnsupportedOperationException e) {
			throw UnsupportedOperationException; 
		}catch(ClassCastException cce) {
			throw ClassCastException;
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}catch(IllegalArgumentException iae) {
			throw IllegalArgumentException;
		}catch(IllegalStateException ise) {
			throw IllegalStateException;
		}
	}

	@Override
	public void clear() throws Exception {
		try {
			//not pointing any more to the head
			head = null;			
			tail = head;
			iter = head;
		}catch(UnsupportedOperationException e) {
			throw UnsupportedOperationException;
		}
	}

	@Override
	public boolean contains(E e) throws Exception {
		try {
			//checking value in list or not
			Node<E> element = new Node<E>(e);		
			Node<E> tmpiter = head;
			while(tmpiter != null) {
				if(tmpiter.data.equals(element.getData()))
					return true;
				tmpiter = tmpiter.next;
			}
		}catch(ClassCastException cce) {
			throw ClassCastException;
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}
		return false;
	}

	@Override
	public boolean containsAll(Collection<E> c) throws Exception {
		//checking all element in collection one by one is they in list or not
		try {
			while(c.hasNext())					
				if(!contains(c.next()))
					return false;
			return true;
		}catch(ClassCastException cce) {
			throw ClassCastException;
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}
		
	}

	@Override
	public boolean isEmpty() {
		return head == null;		//if linked is pointing null that means list is empty
	}

	@Override
	public boolean remove(E e) throws Exception{

		try {
			//removing first same found same object in list
			Node<E> tmpiter = head;		
			if(tmpiter == null)
				return true;
			
			if(tmpiter.getData().equals(e)){
				head = head.next;
				size--;
				return true;
			}
				
			while(tmpiter != null) {
				
				if(tmpiter.next.data.equals(e)) {
					tmpiter.next = tmpiter.next.next;
					size--;
					return true;
				}
				tmpiter = tmpiter.next;
			}
		}catch(ClassCastException e1) {
			throw ClassCastException;
		}catch(NullPointerException e2) {
			throw NullPointerException;
		}
		return false;
	}

	@Override
	public boolean removeAll(Collection<E> c) throws Exception {
		//removing all element in collection one by one
		try {
			while(c.hasNext())			
			remove(c.next());
		
			return true;
		}catch(ClassCastException e1) {
			throw ClassCastException;
		}catch(NullPointerException e2) {
			throw NullPointerException;
		}
	}

	@Override
	public boolean retainAll(Collection<E> c) throws Exception {
		
		try {
			Node<E> tmpiter = head;
			//keeping data which exist in collection at the same time exist in linked list 
			while(tmpiter != null) {		//other wise removing object
				if(!c.contains(tmpiter.getData()))
					remove(tmpiter.getData());
				tmpiter = tmpiter.next;
			}
			
			return true;
		}catch(ClassCastException e1) {
			throw ClassCastException;
		}catch(NullPointerException e2) {
			throw NullPointerException;
		}
	}

	@Override
	public int size() {
		return size;		//returning number of object in list
	}
	
	@Override
	public E element() throws Exception {
		try {
			//returning head value of linked list
			E tmp = head.data;		
			return tmp;
		}catch(NoSuchElementException  nsee) {
			throw NoSuchElementException;
		}
		
	}

	@Override
	public boolean offer(E e) throws Exception {
		return add(e);		
		/*
		 * add element in linked list if is can not  return false
			and if exception occurs throw it
		*/				
	}

	@Override
	public E poll() {	
		//returning head value and remove it
		if(head == null)
			return null;
		E tmp = head.getData();
		head = head.next;
		return tmp;
	}

	@Override
	public void remove() throws Exception {
		try {
		remove(iter.data);			//removing current iterator data
		}catch(ClassCastException e1) {
			throw ClassCastException;
		}catch(NullPointerException e2) {
			throw NullPointerException;
		}
	}
	
	public String toString() {
		String tmp = "";				//Printing linked list as we want
		Node<E> tmpiter = head;
		
		while(tmpiter != null) {
			tmp = tmp + tmpiter.data.toString() + "->";
			tmpiter = tmpiter.next;
		}
		tmp = tmp + "NULL";
		return tmp;
	}

	@Override
	public E peek() {		//returning first data of linked list
		
		if(head == null)	//if head is null return null value
			return null;
		
		return head.getData();
	}

	@Override
	public void add(int index, E e) throws Exception {
		
		try {
			Node<E> iter = head;		//inserting element wanted place
			Node<E> newNode = new Node<E>(e);
			for(int i=0; i<index-1; i++) 
				iter = iter.next;
			newNode.next = iter.next;
			iter.next = newNode;
		}catch(UnsupportedOperationException uoe) {
			throw UnsupportedOperationException;
		}catch(ClassCastException cce) {
			throw ClassCastException;
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}catch(IllegalArgumentException iae) {
			throw IllegalArgumentException;
		}catch(IndexOutOfBoundsException iobe) {
			throw IndexOutOfBoundsException;
		}
	}

	@Override
	public boolean addAll(int index, Collection<E> c) throws Exception {
		try {
			while(c.hasNext()) {		//adding all element in collection where wanted place in list
				add(index,c.next());
				index++;
			}
			return true;
		}catch(UnsupportedOperationException uoe) {
			throw UnsupportedOperationException;
		}catch(ClassCastException cce) {
			throw ClassCastException;
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}catch(IllegalArgumentException iae) {
			throw IllegalArgumentException;
		}catch(IndexOutOfBoundsException iobe) {
			throw IndexOutOfBoundsException;
		}
	}

	@Override
	public E get(int index) throws Exception {
		Node<E> tmpiter = head;
		try {						//returning index value of linked list 
			for(int i=0; i<index; ++i)
				tmpiter = tmpiter.next;
				
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}catch(IndexOutOfBoundsException iobe) {
			throw IndexOutOfBoundsException;
		}
		
		return tmpiter.getData();
	}

	@Override
	public int indexOf(E e) {		
		//finding index of wanted element in linked list
		int i = 0;
		Node<E> tmpiter = head;
		Node<E> cmp = new Node<E>(e);
		while(tmpiter != null) {
			if(tmpiter.equals(cmp)) 
				return i;
			tmpiter = tmpiter.next;
			i++;
		}	
		return -1;
	}

	@Override
	public E set(int index, E e) throws Exception {
					
		try {
			//replacing index value with getting element
			Node<E> tmpiter = head;
			
			for(int i=0; i<index; ++i)
				tmpiter = tmpiter.next;

			tmpiter.setData(e);
			
		}catch(UnsupportedOperationException uoe) {
			throw UnsupportedOperationException;
		}catch(ClassCastException cce) {
			throw ClassCastException;
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}catch(IllegalArgumentException iae) {
			throw IllegalArgumentException;
		}catch(IndexOutOfBoundsException iobe) {
			throw IndexOutOfBoundsException;
		}
		return null;
	}


	@Override
	public int lastIndexOf(E e) {
		//finding last index of same object that getting parameter
		int index = 0, i = 0;
		Node<E> tmpiter = head;			
		
		while(tmpiter != null) {
			
			if(tmpiter.getData().equals(e))
				index = i;
			i++;
			tmpiter = tmpiter.next;
		}
		

		return index;
	}

	@Override
	public List<E> subList(int fromIndex, int toIndex) {
		
		//returning sub list of linked list
		
		
		return null;
	}
}




