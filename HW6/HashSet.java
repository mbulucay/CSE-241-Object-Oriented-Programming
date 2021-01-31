
public class HashSet <E> implements Set<E>,Iterator<E>{

	private static final Integer CAPACITY = 100;
	private static final Exception ClassCastException = null;
	private static final Exception NullPointerException = null;
	private static final Exception UnsupportedOperationException = null;
	private Node<E>[] hashSet;
	private int iter;
	private int size;
	private int used = 0;
	
	@SuppressWarnings("unchecked")
	public HashSet() {
		hashSet = new Node[CAPACITY];
		size = CAPACITY;
	}
	
	@SuppressWarnings("unchecked")
	public HashSet(final int cap) {
		size = cap;
		hashSet = new Node[size];
	}
	
	@SuppressWarnings("unchecked")
	public boolean add(E e) throws Exception{
		
		if(contains(e))									//If something already exist not adding two times
			return true;
		
		if(used == size) {								//if array fill we increase its size
			Node<E>[] newHashSet = new Node[size*2];
			
			for(int i=0; i<size; ++i)
				newHashSet[i] = hashSet[i];
			
			hashSet = newHashSet;				
			size*=2;
		}
		
		Node<E> newNode = new Node<E>(e);
		
		hashSet[used] = newNode;			//adding new node
		if(used > 0) 
			hashSet[used-1].next = hashSet[used];		//Making connection between each nodes
		
		used++;
		return true;
	}
	
	public boolean addAll(Collection<E> c) throws Exception {

		while(c.hasNext())		//adding each node in taking collection
			add(c.next());	
		return true;
	}
	
	public void clear() throws Exception {
		try {
			//clearing each node one by one
			for(int i =0; i<used; ++i)			
				hashSet[i].clear();
		
			used = iter = 0;
		}catch(UnsupportedOperationException e) {
			throw UnsupportedOperationException;
		}
		
	}

	public boolean contains(E e) throws Exception {
		try {
			//checking a node is in the set or not
			Node<E> compare = new Node<E>(e);		
			for(Node<E> e2 :hashSet) {
				if(compare.equals(e2))
					return true;
			}
		}catch(ClassCastException e1) {
			throw ClassCastException ;
		}catch(NullPointerException e2) {
			throw NullPointerException;
		}
		return false;
	}
	
	public boolean containsAll(Collection<E> c) throws Exception {
		try {
			while(c.hasNext())					//If we found something don't exist return false other wise true
				if(!contains(c.next()))
					return false;
			
			return true;
		}catch(ClassCastException e1) {
			throw ClassCastException ;
		}catch(NullPointerException e2) {
			throw NullPointerException;
		}
	}
	
	public boolean isEmpty() {
		if(used == 0)				//return the status of Set is empty or not
			return true;
		return false;
	}
	
	public boolean remove(E e) throws Exception {
		Node<E> comp = new Node<E>(e);
		try {
			//Removing first equal element in set
			for(int i=0; i<used; ++i) {				
				
				if(hashSet[i].equals(comp)) {
					while(i<used) {
						hashSet[i] = hashSet[++i];
					}
				}
			}
			used--;
			return true;
			
		}catch(ClassCastException e1) {
			throw ClassCastException;
		}catch(NullPointerException e2) {
			throw NullPointerException;
		}
	}
	
	public boolean removeAll(Collection<E> c) throws Exception {
		try {
			while(c.hasNext()) 		//removing each element in collection (if it is exist in set)
				remove(c.next());
			
			return true;
		}catch(ClassCastException e1) {
			throw ClassCastException;
		}catch(NullPointerException e2) {
			throw NullPointerException;
		}
	}
	
	public boolean retainAll(Collection<E> c) throws Exception {
		try {
			//Just stand same object in getting collection
			for(int i=0; i<used; ++i) {
				if(!c.contains(hashSet[i].getData())) {			
					remove(hashSet[i].getData());
					i--;
				}
			}
			
			return true;
		}catch(ClassCastException e1) {
			throw ClassCastException;
		}catch(NullPointerException e2) {
			throw NullPointerException;
		}
	}
	
	@Override
	public Iterator<E> iterator() {
		iter = 0;
		return this;		//Returning iterator for the object
	}
	
	public int size() {		
		//return the size of object not used
		return used;
	}

	@Override
	public boolean hasNext() {		
		//if iterator is less than used that means there is still object to call with .next()
		return iter<used;
	}
	
	@Override
	public E next() {			
		//Calling next object in set
		E value = null;
		try {
			value = hashSet[iter++].getData();
		}catch(NullPointerException e) {
			System.out.println("NullPointerException");
		}
		return value;
	}
	
	public void remove() throws Exception {
		try {										
			//removing last element which returning from .next()
			remove(hashSet[iter-1].getData());
		}catch(ArrayIndexOutOfBoundsException e) {
			System.out.println("ArrayIndexOutOfBoundsException");
		}
	}
	
	public String toString(){			
		//Print the set as we want
		String result = "( ";
		
		for(int i=0; i<used; ++i) {
			result = result + hashSet[i].getData().toString();
			if(i!=used-1)
				result += ", ";
		}
		result += " )";
		return result;
	}

	@Override
	public Object[] toArray() {				
		//Return set as an array
		@SuppressWarnings("unchecked")
		E[] array = (E[])new Object[used];
		
		for(int i=0; i<used;++i)
			array[i] = hashSet[i].getData();

		return array;
	}

}
