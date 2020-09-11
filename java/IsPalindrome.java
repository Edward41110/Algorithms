package myAlgorithms;

import java.util.LinkedList;
import java.util.Stack;

public class IsPalindrome {

	public static boolean isPalindrome(LinkedList<Integer> list) {
		boolean is = true;
		int mid = 0;
		for (int i = 0;i < list.size();i += 2) {
			mid += 1;
		}
		Stack<Integer> st = new Stack<Integer>();
		for (int i = mid;i < list.size();i++) {
			st.push(list.get(i));
		}
		for (int i = 0;!st.empty();i++) {
			if (!list.get(i).equals(st.pop())) {
				is = false;
				break;
			}
		}
		return is;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
	}
}
