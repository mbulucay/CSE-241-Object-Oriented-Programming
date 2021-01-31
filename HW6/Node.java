import java.util.Objects;

public class Node<E>{

	public E data;
	public Node<E> next;
	
	Node(){
		this.next = null;
	}
	
	Node(E data){
		this.data = data;
		this.next = null;
	}

	
	public void setData(E e) {
		data = e;
	}
	
	public E getData() {
		return data;
	}
	
	public void setNext(Node<E> next) {
		this.next = next;
	}
	
	public void clear() {
		data = null;
		next = null;
	}
	
	public int hashCode(Node<E> e) {
		
		return Objects.hash(data);
	}
	
	public boolean equals(Object o) {
		
		if(this == o)
			return true;
		
		if(o == null)
			return false;
		
		if(getClass() != o.getClass())
			return false;
		
		@SuppressWarnings("unchecked")
		Node<E> e = (Node<E>) o;
		
		return Objects.equals(data,e.data);
	}


}
