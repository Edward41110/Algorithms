#include<stdio.h>
#include<stdlib.h>

typedef struct linked_list{
	int data;
	struct linked_list *next;
	
} List;


int MainMenu(void);
void InitList(List *head);
void GetElem(List *head);		//return the ith element of list
void LocateElem(List *head);		//return the location of num which is first time appear
void InsertElem(List *head);		//insert num to the ith of the list
void ModifyElem(List *head);		//modify the element in the list
void DeleteElem(List *head);		//delete the ith element in the list
int ListLength(List *head);		//return the length of list
void PrintAllElements(List *head);	//print all the elements in the list
void FreeList(List *head);		//free the whole list

int main()
{
	List *head = (List *)malloc(sizeof(List));
	head->data = 0;
	head->next = head;
	printf("\n\t### the list has been created successfully ###\n");
	while(1)
	{
		int cmd = MainMenu();
		switch (cmd)
		{
			case 1:
			{
				InitList(head);
				break;
			}
			case 2:
			{
				GetElem(head);
				break;
			}
			case 3:
			{
				LocateElem(head);
				break;
			}
			case 4:
			{
				InsertElem(head);
				break;
			}
			case 5:
			{
				ModifyElem(head);
				break;
			}
			case 6:
			{
				DeleteElem(head);
				break;
			}
			case 7:
			{
				ListLength(head);
				break;
			}
			case 8:
			{
				PrintAllElements(head);
				break;
			}
			case 9:
			{
				FreeList(head);
				goto end;
			}
		}
	}
end:
	return 0;
}

int MainMenu()
{
	printf("\n#################################################################################");
	printf("\n#\t\t\t\t\t\t\t\t\t\t#");
	printf("\n#\t<Main Menu>\t\t\t\t\t\t\t\t#\n");
	printf("#\t\t\t\t\t\t\t\t\t\t#\n");
	printf("#\t1: InitList\t\t");
	printf("2: GetElement\t\t");
	printf("3: LocateElement\t#\n");
	printf("#\t4: InsertElement\t");
	printf("5: ModifyElement\t");
	printf("6: DeleteElement\t#\n");
	printf("#\t7: ListLength\t\t");
	printf("8: PrintAllElements\t");
	printf("9: FreeList\t\t#");
	printf("\n#\t\t\t\t\t\t\t\t\t\t#");
	printf("\n#################################################################################\n");
	printf("command:");
	int cmd;
	scanf("%d",&cmd);
	return cmd;
}

void InitList(List *head)
{
	List *p;
	for(p = head->next;p != head;p = p->next)
		p->data = 0;
	printf("\n\t### the list has been initialized successfully ###\n");
}

void GetElem(List *head)
{
	int i;
	List *p;
//	int num;
	printf("请输入需要查找元素的位次:");
	scanf("%d",&i);
	int cnt = 1;
	if (i <= 0)
		printf("\tError: input is illegal\n");
	else
	{
		for (p = head->next;p != head;cnt++,p = p->next)
		{
			if (cnt == i)
			{
				printf("\tlist %d : %d\n",cnt,p->data);
//				num = p->data;
				break;
			}
		}
		if (p == head)
			printf("\tError: index out of range\n");
	}
}

void LocateElem(List *head)
{
	int num;
	printf("请输入需要查找的元素:");
	scanf("%d",&num);
	int i=1;
	int cnt = 0;
	int times;
	int isFind = 0;
	List *p;
	printf("请输入需要查找%d第几次出现的次数(input 0 means find all):",num);
	scanf("%d",&times);
	for (p = head->next;p != head;i++,p = p->next)
	{
		if (p->data == num)
		{
			printf("\tlist %d : %d\n",i,p->data);
			isFind = 1;
			cnt++;
			if (cnt == times)
				break;
		}
	}
	if (p == head)
	{
		if (isFind)
			printf("\tfind all\n");
		else
			printf("\t%d not found\n",num);
	}
}

void InsertElem(List *head)
{
	int num;
	printf("请输入待插入的数字:");
	scanf("%d",&num);
	if (head->next == head)
	{
		List *new = (List *)malloc(sizeof(List));
		new->data = num;
		head->next = new;
		new->next = head;
		printf("\tlist 1 : %d\n",num);
	}
	else
	{
		int x;
		printf("请输入%d将要插入的位次:",num);
		scanf("%d",&x);
		int cnt = 1;
		int isInsert = 0;
		List *p;
		if (x <= 0)
			printf("\tError: input is illegal\n");
		else
		{
			for(p = head->next;p != head;cnt++,p = p->next)
			{
				if(cnt == x-1)
				{
					List *new = (List *)malloc(sizeof(List));
					new->data = num;
					new->next = p->next;
					p->next = new;
					isInsert = 1;
					printf("\tlist %d : %d\n",cnt+1,num);
					break;
				}
			}
			if (!isInsert)
			{
				printf("\tWarning: ");
				ListLength(head);
				printf("\tdo you want to add this data directly to the end of list?\n\t(Y/N): \t");
				char ch;
				scanf(" %c",&ch);
				if (ch == 'Y' || ch == 'y')
				{
					List *last;
					List *new = (List *)malloc(sizeof(List));
					new->data = num;
					for(last = head->next;last->next != head;last = last->next);
					new->next = head;
					last ->next = new;
					printf("\tlist %d : %d\n", cnt, num);
				}
			}
		}
	}
}

void ModifyElem(List *head)
{

}

void DeleteElem(List *head)
{
	int i;
	printf("请输入需要删除元素的位次:");
	scanf("%d", &i);
	int cnt = 0;
	List *p;
	List *last;
	if (i <= 0)
		printf("\tError: input is illegal\n");
	else
	{
		for (p = head->next ; p != head ; cnt++, last = p, p = p->next)
		{
			if (cnt == i)
			{
				printf("\tlist %d : %d\n", cnt, p->data);
				printf("确认删除?(Y/N):");
				char ch;
				scanf(" %c", &ch);
				if (ch == 'Y' || ch == 'y')
				{
					last->next = p->next;
					free(p);
					printf("\n\t### successfully deleted ###\n");
				}
			}
		}
	}
}

int ListLength(List *head)
{
	int len = 0;
	List *p;
	for (p = head->next;p != head;len++,p = p->next);
	printf("\tlength of the list is %d\n",len);
	return len;
}

void PrintAllElements(List *head)
{
	int cnt = 0;
	ListLength(head);
	List *p;
	if (head->next == head)
		printf("\tthis list is empty\n");
	else
	{
		printf("\tall of elements in this list:\n\t");
		for (p = head->next;p != head;cnt++,p = p->next)
		{
			printf("%d",p->data);
			if((cnt+1) % 5 == 0)
				printf("\n\t");
			else
				printf("\t");	
		}
	printf("\n");
	}
}

void FreeList(List *head)
{
	printf("\n\t### space has been released ###\n\n");
}

