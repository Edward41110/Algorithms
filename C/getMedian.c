#include<stdio.h>
#include<stdlib.h>

void swap(int*arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void maxHeapInsert(int*arr, int num, int heapSize)
{
	arr[heapSize] = num;
	int i = heapSize;
	while (arr[i] > arr[(i - 1) / 2]) {
		swap(arr, i, (i - 1) / 2);
		i = (i - 1) / 2;
	}
}

void minHeapInsert(int*arr, int num, int heapSize)
{
	arr[heapSize] = num;
	int i = heapSize;
	while (arr[i] < arr[(i - 1) / 2]) {
		swap(arr, i, (i - 1) / 2);
		i = (i - 1) / 2;
	}
}

void maxHeapify(int*arr, int index, int heapSize)
{
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

void minHeapify(int*arr, int index, int heapSize)
{
	int left = index * 2 + 1;
	while (left < heapSize) {
		int smallest = left + 1 < heapSize && arr[left + 1] < arr[left] ? left + 1 : left;
		smallest = arr[smallest] < arr[index] ? smallest : index;
		if (smallest == index) {
			break;
		}
		swap(arr, smallest, index);
		index = smallest;
		left = index * 2 + 1;
	}
}

void AdjustHeap(int*arr, int arrSize)
{
	int maxHeapSize = 0;
	int minHeapSize = 0;
	int*maxHeap = (int*)malloc(sizeof(int) * (arrSize / 2 + 2));
	int*minHeap = (int*)malloc(sizeof(int) * (arrSize / 2 + 2));
	for (int i = 0;i < arrSize;i++) {
		if (arr[i] < minHeap[0]) {
			maxHeapInsert(maxHeap, arr[i], maxHeapSize++);
		}
		else {
			minHeapInsert(minHeap, arr[i], minHeapSize++);
		}
		if (maxHeapSize - minHeapSize == 2) {
			minHeapInsert(minHeap, maxHeap[0], minHeapSize++);
			swap(maxHeap, 0, --maxHeapSize);
			maxHeapify(maxHeap, 0, maxHeapSize);
		}
		else if (minHeapSize - maxHeapSize == 2) {
			maxHeapInsert(maxHeap, minHeap[0], maxHeapSize++);
			swap(minHeap, 0, --minHeapSize);
			minHeapify(minHeap, 0, minHeapSize);
		}
		double median;
		if (maxHeapSize == minHeapSize) {
			median = (double)(maxHeap[0] + minHeap[0]) / 2;
		}
		else {
			median = maxHeapSize > minHeapSize ? maxHeap[0] : minHeap[0];
		}
		printf("%.2f\n", median);
	}
}

int main()
{
	int arr[] = { 1, 10, 100, 1000, 10000, 1000, 100, 10, 1 };
	AdjustHeap(arr, sizeof(arr)/sizeof(arr[0]));
	getchar();
}

