package myAlgorithms;

import java.util.LinkedList;

public class AllLessNumSubArray {

	public static void addNumMax(LinkedList<Integer> max, int[]arr, int index) {
		while(!max.isEmpty() && arr[max.peekLast()] <= arr[index]) {
			max.pollLast();
		}
		max.addLast(index);
	}
	
	public static void deleteNumMax(LinkedList<Integer> max, int index) {
		if (max.peekFirst() == index) {
			max.pollFirst();
		}
	}
	
	public static void addNumMin(LinkedList<Integer> min, int[]arr, int index) {
		while(!min.isEmpty() && arr[min.peekLast()] >= arr[index]) {
			min.pollLast();
		}
		min.addLast(index);
	}
	
	public static void deleteNumMin(LinkedList<Integer> min, int index) {
		if (min.peekFirst() == index) {
			min.pollFirst();
		}
	}
	
	public static void addNum(LinkedList<Integer> max, LinkedList<Integer> min, int[]arr, int index) {
		addNumMax(max, arr, index);
		addNumMin(min, arr, index);
	}
	
	public static void deleteNum(LinkedList<Integer> max, LinkedList<Integer> min, int index) {
		deleteNumMax(max, index);
		deleteNumMin(min, index);
	}
	
	public static int getNum(int[]arr, int num) {
		if (arr == null || arr.length == 0) {
			return 0;
		}
		LinkedList<Integer> max = new LinkedList<Integer>();
		LinkedList<Integer> min = new LinkedList<Integer>();
		int L = 0;
		int R = 0;
		int res = 0;
		while(L < arr.length) {
			while (R < arr.length) {
				addNum(max, min, arr, R);
				if (arr[max.peekFirst()] - arr[min.peekFirst()] <= num) {
					R++;
				} else {
					break;
				}
			}
			deleteNum(max, min, L);
			res += R - L;
			L++;
		}
		return res;
	}
	
	public static int getNum2(int[]arr, int num) {
		if (arr == null || arr.length == 0) {
			return 0;
		}
		LinkedList<Integer> max = new LinkedList<Integer>();
		LinkedList<Integer> min = new LinkedList<Integer>();
		int L = 0;
		int R = 0;
		int res = 0;
		while (L < arr.length) {
			while (R < arr.length) {
				while (!min.isEmpty() && arr[min.peekLast()] >= arr[R]) {
					min.pollLast();
				}
				min.addLast(R);
				while (!min.isEmpty() && arr[min.peekLast()] <= arr[R]) {
					max.pollLast();
				}
				max.addLast(R);
				if (arr[max.getFirst()] - arr[min.getFirst()] > num) {
					break;
				}
				R++;
			}
			if (min.peekFirst() == L) {
				min.pollFirst();
			}
			if (max.peekFirst() == L) {
				max.pollFirst();
			}
			res += R - L;
			L++;
		}
		return res;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[]arr = new int[]{1, 4, 7, 8, 5, 2, 3, 6, 9};
		System.out.println(getNum2(arr, 3));
	}

}
