package myAlgorithms;

import java.util.LinkedList;
import java.util.Stack;

public class MaxRectangle {

	public static class Node{
		LinkedList<Integer> index;
		public Node(int index){
			this.index = new LinkedList<>();
			this.index.add(index);
		}
		public void addIndex(int index) {
			this.index.add(index);
		}
	}
	
	public static int maxRecFromBottom(int[]arr) {
		Stack<Node> stack = new Stack<>();
		int cur = 0;
		int max = Integer.MIN_VALUE;
		int[]left = new int[arr.length];
		int[]right = new int[arr.length];
		while (cur < arr.length || !stack.isEmpty()) {
			if (cur < arr.length && (stack.isEmpty() || arr[stack.peek().index.getFirst()] < arr[cur])) {
				stack.push(new Node(cur));
				cur++;
			} else if (cur < arr.length && arr[stack.peek().index.getFirst()] == arr[cur]) {
				stack.peek().addIndex(cur);
				cur++;
			} else {
				Node pop = stack.pop();
				for (int i : pop.index) {
					right[i] = cur;
					left[i] = stack.isEmpty() ? -1 : stack.peek().index.getFirst();
				}
			}
		}
		for (int i = 0;i < arr.length;i++) {
			max = Math.max((right[i] - left[i] - 1) * arr[i], max);
		}
		return max;
	}
	
	public static int maxRectangle(int[][]arr) {
		int max = Integer.MIN_VALUE;
		for (int i = 1;i < arr.length;i++) {
			for (int j = 0;j < arr[0].length;j++) {
				arr[i][j] = arr[i][j] == 0 ? 0 : arr[i - 1][j] + 1;
			}
		}
		for (int[] ints : arr) {
			max = Math.max(maxRecFromBottom(ints), max);
		}
		return max;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[][]arr = new int[3][4];
		arr[0] = new int[] {1, 0, 1, 1};
		arr[1] = new int[] {1, 1, 1, 1};
		arr[2] = new int[] {1, 1, 1, 0};
		System.out.println(maxRectangle(arr));
	}

}
