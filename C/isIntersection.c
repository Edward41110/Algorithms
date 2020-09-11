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

List* isIntersection(List* head1, List* head2)
{
	int length1 = 1;
	int length2 = 1;
	List* end1;
	List* end2;
	for (end1 = head1;end1->next;end1 = end1->next)
		length1++;
	for (end2 = head2;end2->next;end2 = end2->next)
		length2++;
	if (end1 != end2)
		return NULL;
	int i;
	if (length1 > length2)
		for(i = 0;i < length1 - length2;i++)
			head1 = head1->next;
	if (length1 < length2)
		for(i = 0;i < length2 - length1;i++)
			head2 = head2->next;
	while (1)
	{
		if (head1 == head2)
			return head1;
		head1 = head1->next;
		head2 = head2->next;
	}
}

int main()
{
	List *head1 = (List*)malloc(sizeof(List));
	head1->data = 1;
	List *head2 = (List*)malloc(sizeof(List));
	head2->data = 11;
	int i;
	List *p = head1;
	List *intersection;
	for(i = 2;i < 10;i++)
	{
		p = NodeConstructor(i, p);
		if (i == 5)
			intersection = p;
	}
	p = head2;
	for (i = 12;i < 15;i++)
	{
		p = NodeConstructor(i, p);
	}
	p->next = intersection;
	
	p = isIntersection(head1, head2);
	printf("%d\n", p->data);
	
	return 0;
}
