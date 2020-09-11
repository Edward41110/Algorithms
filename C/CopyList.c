#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _List{
	int data;
	struct _List* next;
	struct _List* rand; 
}List;

List* NodeConstructor(int data, List* last, List* rand)
{
	List* pNew = (List*)malloc(sizeof(List));
	pNew->data = data;
	last->next = pNew;
	pNew->next = NULL;
	pNew->rand = rand;
	return pNew;
}

List* PrintList(List* head)
{
	List* p;
	printf("data\tnext\trand\n");
	for (p = head;p != NULL;p = p->next)
	{
		printf("%d\t", p->data);
		if (p->next)
			printf("%d", p->next->data);
		if (p->rand)
			printf("\t%d", p->rand->data);
		printf("\n");
	}
}

List* CopyList(List* head)
{
	List*p, *q;
	for (p = head;p != NULL;p = p->next->next)
	{
		List* pNew = (List*)malloc(sizeof(List));
		pNew->data = p->data;
		pNew->next = p->next;
		pNew->rand = NULL;
		p->next = pNew;
	}
	for (p = head, q = head->next;q->next;p = p->next->next, q = q->next->next)
	{
		if(p->rand)
			q->rand = p->rand->next;
	}
	if(p->rand)
		q->rand = p->rand->next;
	
	p = head->next->next;
	List* src = head;
	List* dst = head->next;
	q = dst;
	while (p)
	{
		src->next = p;
		src = src->next;
		p = p->next;
		dst->next = p;
		dst = dst->next;
		p = p->next;
	}
	return q;
}

int main()
{
	List* head = (List*)malloc(sizeof(List));
	head->data = 1;
	head->rand = NULL;
	NodeConstructor(2, head, NULL);
	List* p = head->next;
	List* q = head;
	int i;
	for (i = 3;i < 6;i++)
	{
		List* pNew = NodeConstructor(i, p, q);
		p = p->next;
		q = q->next;
	}
	
	PrintList(CopyList(head));
	printf("\n\n");
	PrintList(head);
	return 0;
}

