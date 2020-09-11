package myAlgorithms;

import java.util.LinkedList;

public class QueueStack {

	private LinkedList<Integer> data = new LinkedList<Integer>();
	private LinkedList<Integer> help = new LinkedList<Integer>();

	public void push(int pushInt) {
		data.add(pushInt);
	}
	
	public int pop() {
		while (data.size() > 1) {
			help.add(data.poll());
		}
		int ret = data.poll();
		swap();
		return ret;
	}
	
	public int peek() {
		while (data.size() > 1) {
			help.add(data.poll());
		}
		int ret = data.peek();
		help.add(data.poll());
		swap();
		return ret;
	}
	
	private void swap() {
		LinkedList<Integer> temp = data;
		data = help;
		help = temp;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
	}
}
