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

List* ReverseList(List* node)
{
	if (node->next == NULL)
		return node;
	List* pre = NULL;
	List* cur = node;
	List* next = node->next;
	while (next != NULL)
	{
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	return pre;
}

bool isPalindrome(List* head)
{
	List* quick = head;
	List* slow = head;
	while (quick->next && quick->next->next)
	{
		quick = quick->next->next;
		slow = slow->next;
	}
	
	List* left = head;
	List* right = ReverseList(slow);
	List* backup = right;
	bool is = true;
	List* p;
	while (left != NULL)
	{
		if (left->data != right ->data)
		{
			is = false;
			break;
		}
		left = left->next;
		right = right->next;
	}
	ReverseList(backup);
	return is;
}

int main()
{
	List* head = (List*)malloc(sizeof(List));
	head->data = 3;
	head->next = NULL;
	NodeConstructor(3, NodeConstructor(2, NodeConstructor(3, NodeConstructor(2, head))));
	
	printf("%d\n", isPalindrome(head));
	List* p;
	for (p = head;p != NULL;p = p->next)
	{
		printf("%d\t", p->data);
	}
	
	printf("\n");
	return 0;
}

