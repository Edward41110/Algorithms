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
	while (quick != slow)
	{
		if (quick->next && quick->next->next)
			quick = quick->next->next;
		else
			return NULL;
		slow = slow->next;
	}
	for (quick = head;quick != slow;quick = quick->next, slow = slow->next);
	return quick;
}

List* isIntersection(List* head1, List* head2, List* end)
{
	int length1 = 1;
	int length2 = 1;
	List* end1;
	List* end2;
	for (end1 = head1;end1->next != end;end1 = end1->next)
		length1++;
	for (end2 = head2;end2->next != end;end2 = end2->next)
		length2++;
	if (end1->next && end2->next && end1->next == end2->next)
		return end1->next;
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

List* isIntersectionWithLoop(List* head1, List* head2)
{
	List* loop1 = hasLoop(head1);
	List* loop2 = hasLoop(head2);
	if (!loop1 && !loop2)		// 无环  返回相交节点
		return isIntersection(head1, head2, NULL); 
	else if (loop1 && loop2)
	{
		if (loop1 == loop2)
			return isIntersection(head1, head2, loop1);		// 入环节点相同  返回入环前相交的节点 
		List* cur;
		for (cur = loop1->next;cur != loop1;cur = cur->next)	// 入环节点不同  查看是否为同一个环 
			if(cur == loop2)	// 是同一个环  返回链表1入环节点 
				return loop1;
		return NULL;			// 不是同一个环  不相交 
	}
	else return NULL; 			// 一个有环一个无环  不相交 
}
