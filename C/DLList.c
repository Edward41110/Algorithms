#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NUM_OF_TEST 1000000
#define LIMIT_OF_NUMS 10000

int MemoryLeakDetector = 0;		// Once malloc, increase; Once free, decrease

typedef struct DLList {			// struct declaration 
	int data;
	struct DLList* prior;
	struct DLList* next;
}List;

List* CreateList()				// create a new list
{
	List* head = (List *)malloc(sizeof(List));
	MemoryLeakDetector++;
	head->data = -1;
	head->prior = head;
	head->next = head;
	return head;
}

void FreeList(List *head)		// destroy the list
{
	List *p, *q;
	p = head->next;
	while (p != head)
	{
		q = p->next;
		free(p);
		MemoryLeakDetector--;
		p = q;
	}
	free(head);
	MemoryLeakDetector--;
}

List* InsertData(List *head, List *p, int data)	// insert a data into list
{
	if (head->data == -1)
	{
		head->data = data;
		return head;
	}
	List* pNew = (List *)malloc(sizeof(List));
	MemoryLeakDetector++;
	pNew->data = data;
	p->next = pNew;
	pNew->prior = p;
	pNew->next = head;
	head->prior = pNew;
	p = p->next;
	return p;
}

void PrintData(List *head)		// print the whole list
{
	List *p;
	for (p = head;p->next != head;p = p->next)
		printf("%d\t", p->data);
	printf("%d\n", p->data);
}

void swap(List* p, List *q)		// swap two values in list 
{
	if (p == q) return;
	int temp = p->data;
	p->data = q->data;
	q->data = temp;
}

void QuickSort(List *begin, List *end)	// partition
{
	if (begin == end) return;
	int pivot = begin->data;
	List *i, *boundary = begin->next;
	for (i = begin->next;i != end->next;i = i->next)
		if (i->data < pivot)
		{
			swap(i, boundary);
			boundary = boundary->next;
		}
	boundary = boundary->prior;
	swap(begin, boundary);
	QuickSort(begin, boundary);
	QuickSort(boundary->next, end);
}

int main()
{
	List* head = CreateList();
	List* p = head;
	int num;
	scanf("%d", &num);
	while (num >= 0)
	{
		p = InsertData(head, p, num);
		scanf("%d", &num);
	}
	if (head->data == -1)
		printf("The list is empty\n");
	else
	{
		printf("All Elements below:\n");
		PrintData(head);
		QuickSort(head, p);
		printf("After Sorted:\n");
		PrintData(head);
	}
	FreeList(head);
	return 0;
}

//int main()
int test()				// rename to "main" to test
{
	int i, num;
	srand(time(NULL));
	FILE* fp = fopen("test.txt", "w");	// roll a group of test data and save it as a text file
	if(fp)
	{
		for(i = 0;i < NUM_OF_TEST;i++)
		{
			int num = rand() % LIMIT_OF_NUMS;
			fprintf(fp, "%d ", num);
		}
		fprintf(fp, "%d", -1);
		fclose(fp);
	}
	
	bool correct = true;
	List* head = CreateList();
	List* p = head;
	fp = fopen("test.txt", "r");
	fscanf(fp, "%d", &num);
	while (num >= 0)						// load data
	{
		p = InsertData(head, p, num);
		fscanf(fp, "%d", &num);
	}
	fclose(fp);
	
	QuickSort(head, p);						// quick sort
	
	for(p = head;p->next != head;p = p->next)	// check the function
		if (p->data > p->next->data)
		{
			correct = false;
			break;
		}
	
	if(correct)
	{
		fp = fopen("result.txt", "w");
		if (fp)
		{
			for(p = head;p->next != head;p = p->next)
				fprintf(fp, "%d ", p->data);
		}
	}
	fclose(fp);
	
	FreeList(head);
	printf("MemoryLeakDetector: %d\n", MemoryLeakDetector);
	printf("result = ");
	if (correct) printf("PASS\n");
	else printf("FAILED\n");
	return 0;
}

