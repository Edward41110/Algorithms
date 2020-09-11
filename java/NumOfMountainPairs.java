package myAlgorithms;

import java.util.Stack;
import java.util.LinkedList;
import java.util.HashMap;
import java.util.HashSet;

public class NumOfMountainPairs {
	
	static class Node{
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
		int[]help = new int[3 * arr.length];
		for (int i = 0;i < help.length;i++) {
			help[i] = arr[i % arr.length];
		}
		int[]helpLeft = new int[help.length];
		int[]helpRight = new int[help.length];
		int cur = 0;
		while (cur < help.length || !stack.isEmpty()) {
			if (cur < help.length && (stack.isEmpty() || stack.peek().value > help[cur])) {
				stack.add(new Node(cur, help[cur]));
				cur++;
			} else if (cur < help.length && stack.peek().value == help[cur]) {
				stack.peek().index.add(cur);
				cur++;
			} else {
				Node pop = stack.pop();
				for (int j : pop.index) {
					if (cur == help.length) {
						helpRight[j] = Integer.MIN_VALUE;
					} else {
						helpRight[j] = help[cur];
					}
					if (stack.isEmpty()) {
						helpLeft[j] = Integer.MIN_VALUE;
					} else {
						helpLeft[j] = stack.peek().value;
					}
				}
			}
		}
		int[]left = new int[arr.length];
		int[]right = new int[arr.length];
		for (int i = arr.length;i < 2 * arr.length;i++) {
			left[i - arr.length] = helpLeft[i];
			right[i - arr.length] = helpRight[i];
		}
		return new int[][] {left, right};
	}
	
	public static void printResult(int[]arr, HashMap<Integer, HashSet<Integer>> map) {
		int cnt = 0;
		for (int i : arr) {
			HashSet<Integer> set = map.get(i);
			for (int j : set) {
				System.out.println("<" + i + ", " + j + ">");
				cnt++;
			}
		}
		System.out.println(cnt);
	}
	
	public static void getNumOfPairs(int[]arr) {
		HashMap<Integer, HashSet<Integer>> map = new HashMap<>();
		int[][]ret = getArray(arr);
		int[]left = ret[0];
		int[]right = ret[1];
		for (int i = 0;i < arr.length;i++) {
			map.put(arr[i], new HashSet<Integer>());
			HashSet<Integer> set = map.get(arr[i]);
			int i1 = (i + arr.length - 1) % arr.length;
			if (arr[i] < arr[i1]) {
				set.add(arr[i1]);
			}
			if (arr[i] < arr[(i + 1) % arr.length]) {
				set.add(arr[(i + 1) % arr.length]);
			}
			if (arr[i] < left[i]) {
				set.add(left[i]);
			}
			if (arr[i] < right[i]) {
				set.add(right[i]);
			}
		}
		printResult(arr, map);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[]arr = new int[] {1, 2, 4, 4, 3};
		getNumOfPairs(arr);
	}

}
