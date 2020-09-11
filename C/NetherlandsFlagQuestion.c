#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _List{
	int data;
	struct _List* next;
}List;

List* NodeConstructor(int data, List* last)
{
	List* pNew = (List*)malloc(sizeof(List));
	pNew->data = data;
	last->next = pNew;
	pNew->next = NULL;
	return pNew;
}

List* Partition(List* head, int pivot)
{
	List* lessHead = NULL;
	List* lessEnd = NULL;
	List* equHead = NULL;
	List* equEnd = NULL;
	List* moreHead = NULL;
	List* moreEnd = NULL;
	
	while (head != NULL)
	{
		if (head->data < pivot)
		{
			if (!lessHead)
			{
				lessHead = head;
				lessEnd = head;
			}
			else
			{
				lessEnd->next = head;
				lessEnd = lessEnd->next;
			}
		}
		else if (head->data == pivot)
		{
			if (!equHead)
			{
				equHead = head;
				equEnd = head;
			}
			else
			{
				equEnd->next = head;
				equEnd = equEnd->next;
			}
		}
		else
		{
			if (!moreHead)
			{
				moreHead = head;
				moreEnd = head;
			}
			else
			{
				moreEnd->next = head;
				moreEnd = moreEnd->next;
			}
		}
		head = head->next;
	}
	if (!lessHead)
		lessHead = equHead ? equHead : moreHead;
	if (lessEnd)
		lessEnd->next = equHead ? equHead : moreHead;
	if (equEnd)
		equEnd->next = moreHead;
	if (moreEnd)
		moreEnd->next = NULL;
	return lessHead;
}

int main()
{
	List* head = (List*)malloc(sizeof(List));
	head->data = 4;
	head->next = NULL;
	NodeConstructor(1, NodeConstructor(2, NodeConstructor(3, head)));
	List* p = Partition(head, 5);
	while (p != NULL)
	{
		printf("%d\t", p->data);
		p = p->next;
	}
	
	printf("\n");
	return 0;
}

