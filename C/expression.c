#include <stdio.h>
#include <stdlib.h>

typedef struct _Stack
{
	int data;
	struct _Stack *next;
}Stack;

void Push(Stack *pHead, int data);
int Pop(Stack *pHead);
int IsEmpty(Stack *pHead);
void FreeStack(Stack *pHead);
int Priority(char ch);
int CheckTopElement(Stack *pHead);
void In2Post(Stack *pHead, char *cInfix, char *cPostfix);
int Calculate(Stack *pHead, char *cPostfix);

int main()
{
	Stack *pHead = (Stack *)malloc(sizeof(Stack));
	pHead->next = NULL;
	char cInfix[80];
	char cPostfix[80];
	printf("expression:");
	scanf("%s", cInfix);
	In2Post(pHead, cInfix, cPostfix);
	int iResult = Calculate(pHead, cPostfix);
	printf("Result = %d\n", iResult);
	FreeStack(pHead);
	getchar();
	getchar();
	return 0;
}

void Push(Stack *pHead, int data)
{
	Stack *pNew = (Stack *)malloc(sizeof(Stack));
	pNew->data = data;
	pNew->next = pHead->next;
	pHead->next = pNew;
}

int Pop(Stack *pHead)
{
	if (IsEmpty(pHead))
		return 0;
	else
	{
		int data;
		Stack *pTop;
		pTop = pHead->next;
		data = pTop->data;
		pHead->next = pTop->next;
		free(pTop);
		return data;
	}
}

int IsEmpty(Stack *pHead)
{
	int bFlag;
	if (pHead->next == NULL)
		bFlag = 1;
	else
		bFlag = 0;
	return bFlag;
}

void FreeStack(Stack *pHead)
{
	while (!IsEmpty(pHead))
		Pop(pHead);
	free(pHead);
}

int Priority(char ch)
{
	int iPriority;
	if (ch == '+' || ch == '-')
		iPriority = 1;
	else if (ch == '*' || ch == '/')
		iPriority = 2;
	return iPriority;
}

int CheckTopElement(Stack *pHead)
{
	int data;
	if (IsEmpty(pHead))
		data = 0;
	else
		data = pHead->next->data;
	return data;
}

void In2Post(Stack *pHead, char *cInfix, char *cPostfix)
{
	int i = 0, j = 0;
	if (cInfix[0] == '-') cPostfix[j++] = '0';
	for (i = 0; cInfix[i] != '\0'; i++)
	{
		if (cInfix[i] >= '0' && cInfix[i] <= '9')
			cPostfix[j++] = cInfix[i];
		else if (cInfix[i] == '(')
			Push(pHead, ((int)cInfix[i]));
		else if (cInfix[i] == '+' || cInfix[i] == '-' || cInfix[i] == '*' || cInfix[i] == '/')
		{
			while (1)
			{
				if ((IsEmpty(pHead)) || ((char)CheckTopElement(pHead)) == '(' || (Priority(cInfix[i]) > Priority((char)CheckTopElement(pHead))))    //空栈、栈顶运算符为左括号、栈顶运算符优先级高于此运算符时入栈
				{
					Push(pHead, ((int)cInfix[i]));
					break;
				}
				else
					cPostfix[j++] = (char)(Pop(pHead));
			}
		}
		else if (cInfix[i] == ')')
		{
			while (((char)CheckTopElement(pHead)) != '(')
				cPostfix[j++] = (char)(Pop(pHead));
			Pop(pHead);
		}
		else
			printf("illegal symbol input\n");
	}
	while (!IsEmpty(pHead))
		cPostfix[j++] = (char)(Pop(pHead));
	cPostfix[j] = '\0';
}

int Calculate(Stack *pHead, char *cPostfix)
{
	int k;
	for (k = 0; cPostfix[k] != '\0'; k++)
	{
		if (cPostfix[k] >= '0' && cPostfix[k] <= '9')
			Push(pHead, (cPostfix[k] - '0'));
		else
		{
			int iResult;
			int iOperator1 = Pop(pHead);
			int iOperator2 = Pop(pHead);
			if (cPostfix[k] == '+')
			{
				iResult = iOperator1 + iOperator2;
				Push(pHead, iResult);
			}
			else if (cPostfix[k] == '-')
			{
				iResult = iOperator2 - iOperator1;
				Push(pHead, iResult);
			}
			else if (cPostfix[k] == '*')
			{
				iResult = iOperator1 * iOperator2;
				Push(pHead, iResult);
			}
			else if (cPostfix[k] == '/')
			{
				iResult = iOperator2 / iOperator1;
				Push(pHead, iResult);
			}
		}
	}
	int iResult = Pop(pHead);
	return iResult;
}

