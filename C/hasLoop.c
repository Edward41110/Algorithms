#include <stdio.h>
#include <stdlib.h>

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

List* hasLoop(List* head)
{
	List* quick = head;
	List* slow = head;
	while (1)
	{
		if (quick->next && quick->next->next)
			quick = quick->next->next;
		else
			return NULL;
		slow = slow->next;
		if (quick == slow)
			break;
	}
	for (quick = head;;quick = quick->next, slow = slow->next)
		if (quick == slow)
			return quick;
}

int main()
{
	List* head = (List*)malloc(sizeof(List));
	head->data = 1;
	List* p = head;
	List* loop;
	int i;
	for(i = 2;i < 6;i++)
	{
		p = NodeConstructor(i, p);
		if (i == 3)
			loop = p;
	}
	p->next = loop;
	
	p = hasLoop(head);
	printf("%d\n", p->data);
	return 0;
}
