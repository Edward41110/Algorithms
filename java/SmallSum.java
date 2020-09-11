package myAlgorithms;

public class SmallSum {

	public static int mergeSort(int[]arr) {
		if (arr == null || arr.length < 2) {
			return 0;
		}
		return sortProcess(arr, 0, arr.length - 1);
	}
	
	public static int sortProcess(int[]arr, int L, int R) {
		if (L == R) {
			return 0;
		}
		int mid = L + ((R - L) >> 1);
		return sortProcess(arr, L, mid) + sortProcess(arr, mid + 1, R) + merge(arr, L, mid, R);
	}
	
	public static int merge(int[]arr, int L, int mid, int R) {
		int i = 0;
		int p1 = L, p2 = mid + 1;
		int res = 0;
		int [] help = new int[R - L + 1];
		while(p1 <= mid && p2 <= R) {
			res += arr[p1] < arr[p2] ? (R - p2 + 1) * arr[p1] : 0;
			help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
		}
		while(p1 <= mid) {
			help[i++] = arr[p1++];
		}
		while(p2 <= R) {
			help[i++] = arr[p2++];
		}
		for(i = 0;i < help.length;i++) {
			arr[L + i] = help[i];
		}
		return res;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int []arr = {1, 3, 4, 2, 5};
		int res = mergeSort(arr);
		System.out.println(res);
	}
}
