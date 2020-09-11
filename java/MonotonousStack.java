package myAlgorithms;

import java.util.LinkedList;
import java.util.Stack;

public class MonotonousStack {

	public static class Node{
		LinkedList<Integer> index;
		int value;
		public Node(int index, int value){
			this.value = value;
			this.index = new LinkedList<>();
			this.index.add(index);
		}
		public void addIndex(int index) {
			this.index.add(index);
		}
	}
	
	public static int[][] getArray(int[]arr) {
		Stack<Node> stack = new Stack<>();
		int[]left = new int[arr.length];
		int[]right = new int[arr.length];
		int cur = 0;
		while (cur < arr.length || !stack.isEmpty()) {
			if (cur < arr.length && (stack.isEmpty() || stack.peek().value > arr[cur])) {
				stack.add(new Node(cur, arr[cur]));
				cur++;
			} else if (cur < arr.length && stack.peek().value == arr[cur]) {
				stack.peek().index.add(cur);
				cur++;
			} else {
				Node pop = stack.pop();
				for (int j : pop.index) {
					if (cur == arr.length) {
						right[j] = Integer.MIN_VALUE;
					} else {
						right[j] = arr[cur];
					}
					if (stack.isEmpty()) {
						left[j] = Integer.MIN_VALUE;
					} else {
						left[j] = stack.peek().value;
					}
				}
			}
		}
		return new int[][] {left, right};
	}
	
	public static void printArray(int[]arr, int[][]res) {
		System.out.println("arr\tleft\tright");
		for (int i = 0;i < arr.length;i++) {
			System.out.print(arr[i] + "\t");
			if (res[0][i] == Integer.MIN_VALUE) {
				System.out.print("null\t");
			} else {
				System.out.print(res[0][i] + "\t");
			}
			if (res[1][i] == Integer.MIN_VALUE) {
				System.out.print("null");
			} else {
				System.out.print(res[1][i]);
			}
			System.out.println();
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[]arr = new int[] {5, 4, 5, 6, 3};
		int[][]res = getArray(arr);
		printArray(arr, res);
	}
}
