
public class ArrayList<E> implements List<E>,Iterator<E> {

	private static final Integer CAPACITY = 100;
	private static final Exception IndexOutOfBoundsException = null;
	private static final Exception NullPointerException = null;
	private static final Exception ClassCastException = null;
	private static final Exception ArrayIndexOutOfBoundsException = null;
	private static final Exception UnsupportedOperationException = null;
	private static final Exception IllegalArgumentException = null;
	private Node<E>[] arrayList;
	private int iter;
	private int size;
	private int used = 0;
	
	@SuppressWarnings("unchecked")
	ArrayList(){
		arrayList = new Node[CAPACITY];
		size = CAPACITY;
	}
	
	@SuppressWarnings("unchecked")
	ArrayList(int cap) {
		size = cap;						
		arrayList = new Node[size];
	}
	
	public boolean hasNext() {
		return iter < used;			//checking for iterator is there any element to get
	}

	public E next() throws Exception {
		E value = null;
		try {					
			//returning current iterator value of ArrayList 
			value = arrayList[iter++].getData();
		}catch(NullPointerException e) {
			throw NullPointerException;
		}
		return value;
	}

	public void remove() throws Exception {
		try {			//removing value which iterator pointing value
			remove(arrayList[iter-1].getData());
		}catch(ArrayIndexOutOfBoundsException e) {
			throw ArrayIndexOutOfBoundsException;
		}
	}

	public Iterator<E> iterator() {		//returning iterator for the object
		iter = 0;
		return this;
	}

	public boolean add(E e) {

		//adding element end of Array List
		
		if(used == size) {			
			@SuppressWarnings("unchecked")
			Node<E>[] newArrayList = new Node[size*2];
			
			for(int i=0; i<size; ++i)
				newArrayList[i] = arrayList[i];
			arrayList = newArrayList;
			size *= 2;
		}
		
		Node<E> newNode = new Node<E>(e);
		arrayList[used] = newNode;
		
		if(used > 0) 
			arrayList[used-1].next = arrayList[used];
		
		used++;
		
		return true;
	}

	public void add(int index,E e) throws Exception {
				//inserting element where wanted index
		try {
			
			if(index < 0 || index > used)
				throw IndexOutOfBoundsException;

			@SuppressWarnings("unchecked")
			Node<E>[] newArrayList = new Node[size+2];
			
			for(int i=0; i<index; ++i)
				newArrayList[i] = arrayList[i];

			Node<E> tmp = new Node<E>(e);
			newArrayList[index] = tmp;
			
			for(int i = index; i< used; ++i)
				newArrayList[i+1] = arrayList[i];

			used++;
			arrayList = newArrayList;
			
		}catch(IndexOutOfBoundsException e1) {
			throw IndexOutOfBoundsException;
		}
	}
	
	public void clear() throws Exception {
		try {		//clear all data in array list
			for(int i =0; i<used; ++i) 
				arrayList[i].clear();
			
			used = iter = 0;
		}catch(UnsupportedOperationException e) {
			throw UnsupportedOperationException;
		}
	}

	public boolean contains(E e) throws Exception {
		try {			//check the element is there or not in the list
			Node<E> compare = new Node<E>(e);
			
			for(Node<E> e2 :arrayList) {
				if(compare.equals(e2))
					return true;
			}
		}catch(ClassCastException cce) {
			throw ClassCastException;
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}
		return false;
	}

	public boolean isEmpty() {
		if (used == 0)		//return array list is empty or not 
			return true;	//is empty return true
		return false;		//other wise false
	}

	public boolean remove(E e) throws Exception {
		
		Node<E> comp = new Node<E>(e);
		
		try {			//removing first found same object which get as parameter in list
			
			for(int i=0; i<used; ++i) {
				if(arrayList[i].equals(comp)) {
					while(i<used) {
						arrayList[i] = arrayList[++i];
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

	public int size() {			//returning size of array list
		return used;
	}
	
	public boolean addAll(Collection<E> c) throws Exception {
		
		while(c.hasNext())			//adding all element in collection
			add(c.next());
		
		return true;
	}
	
	public boolean removeAll(Collection<E> c) throws Exception {
		try {
			while(c.hasNext())		//removing all element in collection if they are in list
				remove(c.next());
			return false;
		}catch(ClassCastException e1) {
			throw ClassCastException;
		}catch(NullPointerException e2) {
			throw NullPointerException;
		}
	}
	
	public boolean containsAll(Collection<E> c) throws Exception {
		try {
			while(c.hasNext())			//checking each element in collection
				if(!contains(c.next()))	//if all exist return true other wise return false
					return false;
			
			return true;
		}catch(ClassCastException cce) {
			throw ClassCastException;
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}	
	}
	
	public boolean retainAll(Collection<E> c) throws Exception {
		
		try {
			/*Keep data which exist in collection and array list other
			 * wise removing it*/
			for(int i=0; i<used; ++i) {			
				if(!c.contains(arrayList[i].getData())) {
					remove(arrayList[i].getData());
					i--;
				}
			}
			
			return true;
		}catch(ClassCastException cce) {
			throw ClassCastException;
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}
	}

	public String toString() {		//printing list as we want
		String tmp = "{ ";
		
		for(int i=0; i<used; ++i) {
			tmp += arrayList[i].getData();
			if(i != used-1)
				tmp += ", ";
		}
		tmp += " }";
		return tmp;
	}

	@Override
	public boolean addAll(int index, Collection<E> c) throws Exception {
		try {
			//insert all element in collection wanted place
			 
			while(c.hasNext()) {		
				add(index,c.next());
				index++;
			}
			return false;
		}catch(IndexOutOfBoundsException e1) {
			throw IndexOutOfBoundsException;
		}	
	}

	@Override
	public E get(int index) throws Exception {
		E data;
		try {		
			//getting index value of array list
			data = arrayList[index].getData();
		}catch(IndexOutOfBoundsException e) {
			throw IndexOutOfBoundsException;
		}
		return data;
	}

	@Override
	public int indexOf(E e) throws Exception{
		//finding index of element which getting parameter
		int index = 0;
		Node<E> tmp = new Node<E>(e);		
		try {
			for(int i=0; i<size; ++i) {
				if(arrayList[i].equals(tmp)) {
					index = i;
					break;
				}
			}	
		}catch(ClassCastException cce) {
			throw ClassCastException;
		}catch(NullPointerException npe) {
			throw NullPointerException;
		}
		return index;
	}

	
	@Override
	public E set(int index, E e) throws Exception {
		
		//replacing index value of list with getting value as parameter
		
		Node<E> tmp;
		try {
			Node<E> newNode = new Node<E>(e);
			tmp = arrayList[index];
			arrayList[index] = newNode;
			
		}catch(UnsupportedOperationException uop) {
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
		return tmp.getData();
	}

	@SuppressWarnings("null")
	@Override
	public List<E> subList(int fromIndex, int toIndex) {
		//returning of sublist which wanted piece of array list
		ArrayList<E> newArrayObject = null;
		for(int i=fromIndex; i<toIndex; ++i)
			newArrayObject.add(arrayList[i].getData());
		
		return newArrayObject;
	}

	@Override
	public int lastIndexOf(E e) {
		//finding last same object in array list return it of it index value
		int index = 0;
		Node<E> tmp = new Node<E>(e);
		try {
			for(int i = size-1; i>=0; i--) {
				if(arrayList[i].equals(tmp)) {
					index = i;
					break;
				}
			}
		}catch(ClassCastException cce) {
			throw cce;
		}catch(NullPointerException npe) {
			throw npe;
		}
		return index;
	}
}
