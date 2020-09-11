#include <stdio.h>
#include <stdlib.h>
#define NUMERATION 8
#define EMPTY 0
#define OK 1
typedef int ElemType;
typedef struct _Stack
{
	ElemType data;
	struct _Stack* next;
} Stack;

int Init(Stack **head)
{
	*head = (Stack*)malloc(sizeof(Stack));
	(*head)->next = NULL;
	return OK;
}

int IsEmpty(Stack *head)
{
	if (!head->next) return 1;
	else return 0;
}

int Push(Stack** head, ElemType data)
{
	Stack *pNew = (Stack *)malloc(sizeof(Stack));
	pNew->data = data;
	pNew->next = (*head)->next;
	(*head)->next = pNew;
	return OK;
}

int Pop(Stack** head, ElemType* ret)
{
	if (IsEmpty(*head))
		return EMPTY;
	else
	{
		Stack *pTop = (*head)->next;
		*ret = pTop->data;
		(*head)->next = pTop->next;
		free(pTop);
		return OK;
	}
}

void FreeStack(Stack *head)
{
	ElemType data;
	while (!IsEmpty(head))
		Pop(&head, &data);
	free(head);
}

void conversion(int num)
{
	Stack* head = NULL;
	Init(&head);
	while (num)
	{
		Push(&head, num % NUMERATION);
		num /= NUMERATION;
	}
	while (!IsEmpty(head))
	{
		ElemType res;
		Pop(&head, &res);
		printf("%d ", res);
	}
	FreeStack(head); 
}

