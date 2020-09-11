#include <stdio.h>
#include <stdlib.h>

void BubbleSort(int *nums, int numsSize);
void SelectionSort(int *nums, int numsSize);
void InsertionSort(int *nums, int numsSize);
int* MergeSort(int *nums, int numsSize);
void QuickSort(int *nums, int numsSize);
void CountingSort(int *nums, int numsSize);

int main()
{
	int i;
	int nums[] = { 7, 4, 1, 2, 5, 8, 9, 6, 3 };
	int numsSize = sizeof(nums) / sizeof(nums[0]);

	//	BubbleSort(nums, numsSize);
	//	SelectionSort(nums, numsSize);
	//	InsertionSort(nums, numsSize);
	int* result = MergeSort(nums, numsSize);
	//	QuickSort(nums, numsSize);
	//	CountingSort(nums, numsSize);

	for (i = 0;i < numsSize;i++)
		printf("%d ", result[i]);
	printf("\n");
	return 0;
}

void swap(int *a, int *b)
{
	if (a == b) return;
	//	printf("%d <-> %d\n", *a, *b);
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void BubbleSort(int *nums, int numsSize)
{
	if (numsSize < 2) return;
	int i, j;
	for (i = 0;i < numsSize - 1;i++)
		for (j = 1;j < numsSize - i;j++)
			if (nums[j - 1] > nums[j])
				swap(&nums[j], &nums[j - 1]);
}

void SelectionSort(int *nums, int numsSize)
{
	if (numsSize < 2) return;
	int i;
	for (i = 0;i < numsSize;i++)
	{
		int j, MinIndex = i;
		for (j = i + 1;j < numsSize;j++)
			if (nums[j] < nums[MinIndex])
				MinIndex = j;
		if (i != j)
			swap(&nums[i], &nums[MinIndex]);
	}
}

void InsertionSort(int *nums, int numsSize)
{
	if (numsSize < 2) return;
	int i, j, num;
	for (i = 1;i < numsSize;i++)
	{
		num = nums[i];
		for (j = i - 1;j >= 0; j--)
		{
			if (nums[j] > num)
				nums[j + 1] = nums[j];
			else
				break;
		}
		nums[j + 1] = num;
	}
}

int* merge(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
	int i = 0, j = 0, idx = 0;
	int *nums = (int *)malloc(sizeof(int) * (nums1Size + nums2Size));
	while (idx < (nums1Size + nums2Size))
		if (i == nums1Size)
			nums[idx++] = nums2[j++];
		else if (j == nums2Size)
			nums[idx++] = nums1[i++];
		else if (nums1[i] < nums2[j])
			nums[idx++] = nums1[i++];
		else
			nums[idx++] = nums2[j++];
	return nums;
}

int* MergeSort(int *nums, int numsSize)
{
	int i;
	if (numsSize < 2) return nums;
	int middle = numsSize / 2;
	int *left = (int *)malloc(sizeof(int) * middle);
	int *right = (int *)malloc(sizeof(int) * (numsSize - middle));
	for (i = 0;i < middle;i++)
		left[i] = nums[i];
	for (i = 0;i < numsSize - middle;i++)
		right[i] = nums[middle + i];
	return merge(MergeSort(left, middle), middle, MergeSort(right, numsSize - middle), numsSize - middle);
}

void quick(int *nums, int begin, int end)
{
	if (end - begin < 2) return;
	int pivot = nums[begin];
	int i, boundary = begin + 1;
	for (i = begin + 1;i < end;i++)
		if (nums[i] < pivot)
		{
			swap(&nums[i], &nums[boundary]);
			boundary++;
		}
	boundary--;
	swap(&nums[begin], &nums[boundary]);
	quick(nums, begin, boundary);
	quick(nums, boundary + 1, end);
}

void QuickSort(int *nums, int numsSize)
{
	if (numsSize < 2) return;
	quick(nums, 0, numsSize);
}

void CountingSort(int *nums, int numsSize)
{
	if (numsSize < 2) return;
	int i, min = nums[0], max = nums[0];
	for (i = 0;i < numsSize;i++)
		if (nums[i] < min)
			min = nums[i];
		else if (nums[i] > max)
			max = nums[i];
	int range = max - min + 1;

	int* count = (int *)malloc(sizeof(int) * range);
	for (i = 0;i < range;i++)
		count[i] = 0;
	for (i = 0;i < numsSize;i++)
		count[nums[i] - min]++;

	int j, k = 0;
	for (i = 0;i < range;i++)
		for (j = 0;j < count[i];j++)
			nums[k++] = i + min;
	free(count);
}

