package myAlgorithms;

public class HeapSort {

	public static void swap(int[]arr, int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
	public static void heapInsert(int[]arr, int i) {
		while (arr[i] > arr[(i - 1) / 2]) {
			swap(arr, i, (i - 1) / 2);
			i = (i - 1) / 2;
		}
	}
	
	public static void heapify(int[]arr, int index, int heapSize) {
		int left = index * 2 + 1;
		while (left < heapSize) {
			int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;
			largest = arr[largest] > arr[index] ? largest : index;
			if (largest == index) {
				break;
			}
			swap(arr, largest, index);
			index = largest;
			left = index * 2 + 1;
		}
	}
	
	public static void heapSort(int[]arr) {
		if (arr == null || arr.length < 2) {
			return;
		}
		for (int i = 0;i < arr.length;i++) {
			heapInsert(arr, i);
		}
		int heapSize = arr.length;
		swap(arr, 0, --heapSize);
		while (heapSize > 0) {
			heapify(arr, 0, heapSize);
			swap(arr, 0, --heapSize);
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[]arr = {2, 1, 3, 6, 0, 4};
		heapSort(arr);
		for(int k : arr) {
			System.out.print(k + " ");
		}
	}

}
