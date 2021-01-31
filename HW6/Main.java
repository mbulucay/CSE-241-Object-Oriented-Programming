
public class Main {
		
	public static <E> void main(String[] args) throws Exception {
		
		System.out.println("ARRAY LIST");
		System.out.println("For Interger");
		ArrayList<Integer> arListInteger = new ArrayList<Integer>();
		Iterator<Integer> itArInt = arListInteger.iterator();
		
		arListInteger.add(1);
		arListInteger.add(2);
		arListInteger.add(3);
		arListInteger.add(4);
		arListInteger.add(5);
		
		System.out.println("Add 5 element add(1) to 5 = " + arListInteger);
		arListInteger.add(3,13);
		System.out.println("call add(3,13) = " + arListInteger);
	
		arListInteger.add(2,58);
		System.out.println("call add(2,58) " + arListInteger);
		arListInteger.remove(58);
		System.out.println("call remove(58) " + arListInteger);
		
		System.out.println("call contains(28) = " + arListInteger.contains(28)  );
		System.out.println("call contains(4) = " + arListInteger.contains(4) );
		System.out.println("call size() = " + arListInteger.size() );
		
		ArrayList<Integer> arListInteger2 = new ArrayList<Integer>();
		arListInteger2.add(6);
		arListInteger2.add(7);
		arListInteger2.add(8);
		arListInteger2.add(9);
		System.out.println("arListInteger2 = " + arListInteger2);
		arListInteger.addAll(arListInteger2);
		System.out.println("call addAll(arListInter2) = " + arListInteger);
		
		ArrayList<Integer> arListInteger3 = new ArrayList<Integer>();
		arListInteger3.add(1);
		arListInteger3.add(3);
		arListInteger3.add(5);
		arListInteger3.add(7);
		arListInteger3.add(9);
		System.out.println("arListInteger3 = " + arListInteger3);
		arListInteger.removeAll(arListInteger3);
		System.out.println("call removeAll(arListInter3) = " + arListInteger);
		
		ArrayList<Integer> arListInteger4 = new ArrayList<Integer>();
		arListInteger4.add(2);
		arListInteger4.add(4);
		arListInteger4.add(6);
		arListInteger4.add(8);
		System.out.println("arListInteger4 = " + arListInteger4);
		System.out.println("call containsAll(arListInter4) = " + arListInteger.containsAll(arListInteger4));
		
		ArrayList<Integer> arListInteger5 = new ArrayList<Integer>();
		arListInteger5.add(2);
		arListInteger5.add(4);
		arListInteger5.add(13);
		System.out.println("arListInteger5 = " + arListInteger5);
		arListInteger.retainAll(arListInteger5);
		System.out.println("call retainAll(arListInter5) = " + arListInteger);
		
		arListInteger.add(5);
		arListInteger.add(89);
		arListInteger.add(72);
		arListInteger.add(42);
		System.out.println("add(5),add(89),add(72),add(42) = " + arListInteger);
		
		System.out.println("call get(4) = " + arListInteger.get(4));
		System.out.println("call indexOf(89) = " + arListInteger.indexOf(89));
		arListInteger.set(5,36);
		System.out.println("call set(5,36) = " + arListInteger);
		
		System.out.println("iterator and remove 13 using iterator>");
		int i= 0;
		while(itArInt.hasNext()) {
			if(i == 1)
				itArInt.remove();
			System.out.print(itArInt.next() + " ");
			i++;
		}System.out.println();
		System.out.println("call isEmpty() = " + arListInteger.isEmpty());
		arListInteger.clear();
		System.out.println("call clear() "+ arListInteger);
		System.out.println("call isEmpty() = " + arListInteger.isEmpty());
		

		
		System.out.println("=============================");
		System.out.println("For String");
		
		ArrayList<String> arListString = new ArrayList<String>();
		Iterator<String> itArStr = arListString.iterator();
		
		arListString.add("first");
		arListString.add("second");
		arListString.add("third");
		arListString.add("fourth");
		arListString.add("fifth");
		
		System.out.println("add 5 element = " + arListString);
		arListString.add(3, "word");
		System.out.println("call add(3,\"word\")" + arListString);
		
		arListString.add(2,"remove");
		System.out.println("call add(2,\"remove\") " + arListString);
		arListString.remove("remove");
		System.out.println("call remove(\"remove\") " + arListString);
		
		System.out.println("call contains(\"first\") = " + arListString.contains("first") );
		System.out.println("call contains(\"not in\") = " + arListString.contains("not in") );
		System.out.println("call size() = " + arListString.size() );
		
		System.out.println("ArListString = " + arListString);
		ArrayList<String> arListString2 = new ArrayList<String>();
		arListString2.add("apple");
		arListString2.add("orange");
		arListString2.add("banana");
		arListString2.add("melon");
		System.out.println("arListString2 = " + arListString2);
		arListString.addAll(arListString2);
		System.out.println("call addAll(arListInter2) = " + arListString);
		
		System.out.println("ArListString = " + arListString);
		ArrayList<String> arListString3 = new ArrayList<String>();
		arListString3.add("first");
		arListString3.add("melon");
		arListString3.add("word");
		arListString3.add("apple");
		System.out.println("arListString3 = " + arListString3);
		arListString.removeAll(arListString3);
		System.out.println("call removeAll(arListInter3) = " + arListString);
		
		System.out.println("ArListString = " + arListString);
		ArrayList<String> arListString4 = new ArrayList<String>();
		arListString4.add("banana");
		arListString4.add("second");
		arListString4.add("orange");
		arListString4.add("fifth");
		System.out.println("arListString4 = " + arListString4);
		System.out.println("call containsAll(arListInter4) = " + arListString.containsAll(arListString4));
		
		System.out.println("ArListString = " + arListString);
		ArrayList<String> arListString5 = new ArrayList<String>();
		arListString5.add("second");
		arListString5.add("orange");
		System.out.println("arListInteger5 = " + arListString5);
		arListString.retainAll(arListString5);
		System.out.println("call retainAll(arListInter5) = " + arListString);

		System.out.println("ArListString = " + arListString);
		System.out.println("add some word > ");
		arListString.add("screen");
		arListString.add("keyboard");
		arListString.add("mouse");
		arListString.add("try");
		System.out.println("ArListString = " + arListString);
		
		System.out.println("call get(3) = " + arListString.get(3));
		System.out.println("call indexOf(\"screen\") = " + arListString.indexOf("screen"));
		arListString.set(1,"resetted");
		System.out.println("call set(1,\"resetted\") = " + arListString);

		System.out.println("iterator and remove keyboard using iterator>");
		int j= 0;
		while(itArStr.hasNext()) {
			if(j == 3)
				itArStr.remove();
			System.out.print(itArStr.next() + " ");
			j++;
		}System.out.println();
		
		System.out.println("call isEmpty() = " + arListString.isEmpty());
		arListString.clear();
		System.out.println("call clear() "+ arListString);
		System.out.println("call isEmpty() = " + arListString.isEmpty());

		

		System.out.println("===================================");
		System.out.println("===================================");
		System.out.println("===================================");
		
		
		System.out.println("LINKED LIST");
		System.out.println("For Integers");
		LinkedList<Integer> lListInteger = new LinkedList<Integer>();
		Iterator<Integer> itLinkInt = lListInteger.iterator();
		
		lListInteger.add(1);
		lListInteger.add(2);
		lListInteger.add(3);
		lListInteger.add(4);
		lListInteger.add(5);
		
		System.out.println("add 1 to 5 = " + lListInteger);
		
		lListInteger.add(2,13);
		System.out.println("call add(2,13) = " + lListInteger);
		lListInteger.remove(13);
		System.out.println("call remove(13) = " + lListInteger);
		System.out.println("call size() = " + lListInteger.size());
		lListInteger.add(2);
		lListInteger.add(7);
		System.out.println("call add(2) add(7) = " + lListInteger);
		System.out.println("call indexOf(2) = " + lListInteger.indexOf(2));
		System.out.println("call lastIndexOf(2) = " + lListInteger.lastIndexOf(2));
		lListInteger.set(5,6);
		System.out.println("call set(5,6) = " + lListInteger);
		System.out.println("call contains(3) = " + lListInteger.contains(3));
		
		System.out.println("call peek() = " + lListInteger.peek());
		System.out.println(lListInteger);
		System.out.println("call poll() = " + lListInteger.poll());
		System.out.println(lListInteger);
		lListInteger.offer(8);
		System.out.println("call offer(8) = " + lListInteger);
		System.out.println("call element() = " + lListInteger.element());
		
		LinkedList<Integer> lListInteger2 = new LinkedList<Integer>();
		lListInteger2.add(9);
		lListInteger2.add(10);
		lListInteger2.add(11);
		System.out.println("lListInteger2 = " + lListInteger2);
		lListInteger.addAll(lListInteger2);
		System.out.println("call addAll(lListInteger2) = " + lListInteger);
		
		LinkedList<Integer> lListInteger3 = new LinkedList<Integer>();
		lListInteger3.add(3);
		lListInteger3.add(6);
		lListInteger3.add(9);
		System.out.println("lListInteger3 = " + lListInteger3);
		lListInteger.removeAll(lListInteger3);
		System.out.println("call removeAll(lListInteger3) = " + lListInteger);

		LinkedList<Integer> lListInteger4 = new LinkedList<Integer>();
		lListInteger4.add(2);
		lListInteger4.add(4);
		lListInteger4.add(8);
		System.out.println("lListInteger4 = " + lListInteger4);
		System.out.println("call containsAll(lListInteger4) = " + lListInteger.containsAll(lListInteger4));

		LinkedList<Integer> lListInteger5 = new LinkedList<Integer>();
		lListInteger5.add(2);
		lListInteger5.add(5);
		lListInteger5.add(10);
		System.out.println("lListInteger5 = " + lListInteger5);
		lListInteger.retainAll(lListInteger5);
		System.out.println("call retainAll(lListInteger5) = " + lListInteger);
		
		lListInteger.add(2,13);
		lListInteger.add(2,45);
		lListInteger.add(2,48);
		System.out.println("call add some number = " + lListInteger);
		
		System.out.println("iterator and remove 45 using iterator>");
		int k = 0;
		while(itLinkInt.hasNext()) {
			if(k == 3)
				itLinkInt.remove();
			System.out.print(itLinkInt.next() + " ");
			k++;
		}System.out.println();
		
		System.out.println(lListInteger);
		System.out.println("call isEmpty = " + lListInteger.isEmpty());
		lListInteger.clear();
		System.out.println("call clear = " + lListInteger);
		System.out.println("call isEmpty = " + lListInteger.isEmpty());
	
		
		
		System.out.println("=============================");
		
		
		System.out.println("For String");
		LinkedList<String> lListString = new LinkedList<String>();
		Iterator<String> itListStr = lListString.iterator(); 
		
		lListString.add("first");
		lListString.add("second");
		lListString.add("third");
		lListString.add("fourth");
		lListString.add("fifth");
		
		lListString.add(2,"word");
		System.out.println("call add(2,\"word\") = " + lListString);
		lListString.remove("word");
		System.out.println("call remove(\"word\") = " + lListString);
		System.out.println("call size() = " + lListString.size());
		lListString.add("second");
		lListString.add("seventh");
		System.out.println("call add(\"orange\") add(\"apple\") = " + lListString);
		System.out.println("call indexOf(\"second\") = " + lListString.indexOf("second"));
		System.out.println("call lastIndexOf(\"second\") = " + lListString.lastIndexOf("second"));
		lListString.set(5,"sixth");
		System.out.println("call set(5,\"sixth\") = " + lListString);
		System.out.println("call contains(\"third\") = " + lListString.contains("third"));
		
		System.out.println("call peek() = " + lListString.peek());
		System.out.println(lListString);
		System.out.println("call poll() = " + lListString.poll());
		System.out.println(lListString);
		lListString.offer("eighth");
		System.out.println("call offer(8) = " + lListString);
		System.out.println("call element() = " + lListString.element());

		LinkedList<String> lListString2 = new LinkedList<String>();
		lListString2.add("nineth");
		lListString2.add("tenth");
		lListString2.add("eleventh");
		System.out.println("lListString2 = " + lListString2);
		lListString.addAll(lListString2);
		System.out.println("call addAll(lListString2) = " + lListString);

		LinkedList<String> lListString3 = new LinkedList<String>();
		lListString3.add("third");
		lListString3.add("sixth");
		lListString3.add("nineth");
		System.out.println("lListString3 = " + lListString3);
		lListString.removeAll(lListString3);
		System.out.println("call removeAll(lListString3) = " + lListString);

		LinkedList<String> lListString4 = new LinkedList<String>();
		lListString4.add("second");
		lListString4.add("fourth");
		lListString4.add("eighth");
		System.out.println("lListString4 = " + lListString4);
		System.out.println("call containsAll(lListString4) = " + lListString.containsAll(lListString4));

		LinkedList<String> lListString5 = new LinkedList<String>();
		lListString5.add("second");
		lListString5.add("fifth");
		lListString5.add("tenth");
		System.out.println("lListString5 = " + lListString5);
		lListString.retainAll(lListString5);
		System.out.println("call retainAll(lListString5) = " + lListString);

		
		lListString.add(2,"apple");
		lListString.add(2,"orange");
		lListString.add(2,"banana");
		System.out.println("call add some string = " + lListString);
		
		System.out.println("iterator and remove orange using iterator>");
		int l = 0;
		while(itListStr.hasNext()) {
			if(l == 3)
				itListStr.remove();
			System.out.print(itListStr.next() + " ");
			l++;
		}System.out.println();
		
		System.out.println("after removing = " + lListString);
		System.out.println("call isEmpty = " + lListString.isEmpty());
		lListString.clear();
		System.out.println("call clear = " + lListString);
		System.out.println("call isEmpty = " + lListString.isEmpty());

		
		
		System.out.println("===================================");
		System.out.println("===================================");
		System.out.println("===================================");
		
		
		
		System.out.println("HASH SET");
		System.out.println("For Integer");
		HashSet<Integer> hSetInteger = new HashSet<Integer>();
		Iterator<Integer> ithSetInt;
		
		hSetInteger.add(28);
		hSetInteger.add(51);
		hSetInteger.add(13);
		hSetInteger.add(62);
		hSetInteger.add(42);
		
		System.out.println("add some number = " + hSetInteger);
		hSetInteger.remove(62);
		System.out.println("call remove(62) = " + hSetInteger);		
		System.out.println("call size() = " + hSetInteger.size());
		System.out.println("call contains(13) = " + hSetInteger.contains(13));
		
		System.out.println("call to toArray assaigment : Object[] arr print:");
		Object[] arr = new Integer[100];
		arr = hSetInteger.toArray();
		for(int c=0; c<hSetInteger.size(); ++c)
			System.out.print(arr[c] + " ");
		System.out.println();
		
		System.out.println("hashSet = " + hSetInteger );
		HashSet<Integer> hSetInteger2 = new HashSet<Integer>();
		hSetInteger2.add(21);
		hSetInteger2.add(7);
		hSetInteger2.add(35);
		hSetInteger2.add(58);
		System.out.println("hSetInteger2 = " + hSetInteger2);
		hSetInteger.addAll(hSetInteger2);
		System.out.println("call addAll(hSetInteger2) = " + hSetInteger );
		
		System.out.println("hashSet = " + hSetInteger );
		HashSet<Integer> hSetInteger3 = new HashSet<Integer>();
		hSetInteger3.add(51);
		hSetInteger3.add(42);
		hSetInteger3.add(35);
		System.out.println("hSetInteger3 = " + hSetInteger3);
		hSetInteger.removeAll(hSetInteger3);
		System.out.println("call removeAll(hSetInteger3) = " + hSetInteger );

		System.out.println("hashSet = " + hSetInteger );
		HashSet<Integer> hSetInteger4 = new HashSet<Integer>();
		hSetInteger4.add(28);
		hSetInteger4.add(21);
		hSetInteger4.add(58);
		System.out.println("hSetInteger4 = " + hSetInteger4);
		System.out.println("call containsAll(hSetInteger4) = " + hSetInteger.containsAll(hSetInteger4));
		
		System.out.println("hashSet = " + hSetInteger );
		HashSet<Integer> hSetInteger5 = new HashSet<Integer>();
		hSetInteger5.add(28);
		hSetInteger5.add(58);
		System.out.println("hSetInteger5 = " + hSetInteger5);
		hSetInteger.retainAll(hSetInteger5);
		System.out.println("call retainAll(hSetInteger5) = " + hSetInteger);
		
		ithSetInt = hSetInteger.iterator();
		
		hSetInteger.add(36);
		hSetInteger.add(40);
		hSetInteger.add(63);
		System.out.println("add some value(36,40,63) to hasSet = " + hSetInteger );
		
		System.out.println("iterator and remove 36 using iterator>");
		int m = 0;
		while(ithSetInt.hasNext()) {
			if(m == 3)
				ithSetInt.remove();
			System.out.print(ithSetInt.next() + " ");
			m++;
		}System.out.println();
		
		System.out.println("after removing = " + hSetInteger);
		System.out.println("call isEmpty = " + hSetInteger.isEmpty());
		hSetInteger.clear();
		System.out.println("call clear = " + hSetInteger);
		System.out.println("call isEmpty = " + hSetInteger.isEmpty());
		
		
		
		
		System.out.println("=============================");
		
		System.out.println("For String");
		HashSet<String> hSetString = new HashSet<String>();
		Iterator<String> itSetStr;
		
		hSetString.add("apple");
		hSetString.add("orange");
		hSetString.add("banana");
		hSetString.add("melon");
		hSetString.add("grape");
		
		System.out.println("add some string = " + hSetString);
		hSetString.remove("melon");
		System.out.println("call remove(\"melon\") = " + hSetString);		
		System.out.println("call size() = " + hSetString.size());
		System.out.println("call contains(\"grape\") = " + hSetString.contains("grape"));

		System.out.println("call to toArray assaigment : Object[] arr print:");
		Object[] arrs = new Integer[100];
		arrs = hSetString.toArray();
		for(int c=0; c<hSetString.size(); ++c)
			System.out.print(arrs[c] + " ");
		System.out.println();	

		System.out.println("hashSet = " + hSetString );
		HashSet<String> hSetString2 = new HashSet<String>();
		hSetString2.add("keyboard");
		hSetString2.add("mouse");
		hSetString2.add("screen");
		System.out.println("hSetString2 = " + hSetString2);
		hSetString.addAll(hSetString2);
		System.out.println("call addAll(hSetInteger2) = " + hSetString );

		System.out.println("hashSet = " + hSetString );
		HashSet<String> hSetString3 = new HashSet<String>();
		hSetString3.add("orange");
		hSetString3.add("mouse");
		hSetString3.add("grape");
		System.out.println("hSetInteger3 = " + hSetString3);
		hSetString.removeAll(hSetString3);
		System.out.println("call removeAll(hSetInteger3) = " + hSetString );

		System.out.println("hashSet = " + hSetString );
		HashSet<String> hSetString4 = new HashSet<String>();
		hSetString4.add("apple");
		hSetString4.add("screen");
		hSetString4.add("keyboard");
		System.out.println("hSetString4 = " + hSetString4);
		System.out.println("call containsAll(hSetInteger4) = " + hSetString.containsAll(hSetString4));

		System.out.println("hashSet = " + hSetString );
		HashSet<String> hSetString5 = new HashSet<String>();
		hSetString5.add("apple");
		hSetString5.add("keyboard");
		System.out.println("hSetString5 = " + hSetString5);
		hSetString.retainAll(hSetString5);
		System.out.println("call retainAll(hSetString5) = " + hSetString);

		itSetStr = hSetString.iterator();
		
		hSetString.add("car");
		hSetString.add("ship");
		hSetString.add("plane");
		System.out.println("add some value(car,ship,plane) to hSetString = " + hSetString );
		
		System.out.println("iterator and remove ship using iterator>");
		int n = 0;
		while(itSetStr.hasNext()) {
			if(n == 3)
				itSetStr.remove();
			System.out.print(itSetStr.next() + " ");
			n++;
		}System.out.println();

		System.out.println("after removing = " + hSetString);
		System.out.println("call isEmpty = " + hSetString.isEmpty());
		hSetString.clear();
		System.out.println("call clear = " + hSetString);
		System.out.println("call isEmpty = " + hSetString.isEmpty());

	}
}







