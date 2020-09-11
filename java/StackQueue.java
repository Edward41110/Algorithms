package myAlgorithms;

import java.util.Stack;

public class StackQueue {

	private Stack<Integer> push = new Stack<Integer>();
	private Stack<Integer> pop = new Stack<Integer>();
	
	public void add(int addInt) {
		push.push(addInt);
		pour();
	}
	
	public int remove() {
		pour();
		return pop.pop();
	}
	
	public int peek() {
		pour();
		return pop.peek();
	}
	
	private void pour() {
		if (!pop.isEmpty()) {
			return;
		}
		while(!push.isEmpty()) {
			pop.push(push.pop());
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
	}

}
