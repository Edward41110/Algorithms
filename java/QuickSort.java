package myAlgorithms;

public class QuickSort {

	public static void swap(int[]arr, int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
	public static int[] Partition(int[]arr, int L, int R) {
		int less = L - 1, more = R;
		int cur = L;
		while (cur < more) {
			if (arr[cur] < arr[R]) {
				swap(arr, ++less, cur++);
			} else if (arr[cur] > arr[R]) {
				swap(arr, --more, cur);
			} else {
				cur++;
			}
		}
		swap(arr, more, R);
		return new int[] { less + 1, more};
	}
	
	public static void quickSort(int[]arr, int L, int R) {
		if ( L < R) {
			int[]p = Partition(arr, L, R);
			quickSort(arr, L, p[0] - 1);
			quickSort(arr, p[1] + 1, R);
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int []arr = {1, 4, 7, 8, 5, 2, 3, 6, 9};
		quickSort(arr, 0, arr.length - 1);
		for(int k : arr) {
			System.out.print(k+" ");
		}
	}

}
