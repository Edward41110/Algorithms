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
	if (!loop1 && !loop2)		// �޻�  �����ཻ�ڵ�
		return isIntersection(head1, head2, NULL); 
	else if (loop1 && loop2)
	{
		if (loop1 == loop2)
			return isIntersection(head1, head2, loop1);		// �뻷�ڵ���ͬ  �����뻷ǰ�ཻ�Ľڵ� 
		List* cur;
		for (cur = loop1->next;cur != loop1;cur = cur->next)	// �뻷�ڵ㲻ͬ  �鿴�Ƿ�Ϊͬһ���� 
			if(cur == loop2)	// ��ͬһ����  ��������1�뻷�ڵ� 
				return loop1;
		return NULL;			// ����ͬһ����  ���ཻ 
	}
	else return NULL; 			// һ���л�һ���޻�  ���ཻ 
}
