#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define SizeOfList 80
typedef struct linear_list{
	int data[SizeOfList];
	int last;
} List;

int menu(void);
void InitList(List *pL);
void ClearList(List *pL);
void GetElem(List *pL);			//return the ith element of list
void LocateElem(List *pL);		//return the location of num which is first time appear
void InsertElem(List *pL);		//insert num to the ith of the list
void ModifyElem(List *pL);		//modify the element in the list
void DeleteElem(List *pL);		//delete the ith element in the list
void SortElem(List *pL);		//sort these elements in the list
void PrintAllElements(List *pL);//print all the elements in the list
void SaveData(List *pL);		//save data to a file
void LoadData(List *pL);		//load data from a file
void FreeList(List *pL);		//free the whole list

int main()
{
	List *pL = (List *)malloc(sizeof(List));
	pL->last = 0;
	printf("\n\t### the list has been created successfully ###\n");
	while(1)
	{
		printf("\n");
		system("pause");
		system("cls"); 
		int cmd = menu();
		switch (cmd)
		{
			case 1:		InitList(pL);			break;
			case 2:		ClearList(pL);			break;
			case 3:		GetElem(pL);			break;
			case 4:		LocateElem(pL);			break;
			case 5:		InsertElem(pL);			break;
			case 6:		ModifyElem(pL);			break;
			case 7:		DeleteElem(pL);			break;
			case 8:		SortElem(pL);			break;
			case 9:		PrintAllElements(pL);	break;
			case 10:	SaveData(pL);			break;
			case 11:	LoadData(pL);			break;
			case 12:	FreeList(pL);			return 0;
		}
	}
}

int menu()
{
	printf("\n#########################################################################################################");
	printf("\n#\t\t\t\t\t\t\t\t\t\t\t\t\t#");
	printf("\n#\t<Main Menu>\t\t\t\t\t\t\t\t\t\t\t#\n");
	printf("#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n");
	printf("#\t1 : InitList\t\t");
	printf("2 : ClearList\t\t");
	printf("3 : GetElement\t\t");
	printf("4 : LocateElement\t#\n");
	printf("#\t5 : InsertElement\t");
	printf("6 : ModifyElement\t");
	printf("7 : DeleteElement\t");
	printf("8 : SortElem\t\t#\n");
	printf("#\t9 : PrintAllElements\t");
	printf("10: SaveData\t\t");
	printf("11: LoadData\t\t");
	printf("12: FreeList\t\t#");
	printf("\n#\t\t\t\t\t\t\t\t\t\t\t\t\t#");
	printf("\n#########################################################################################################\n\n");
	printf("command:");
	int cmd;
	scanf("%d", &cmd);
	return cmd;
}

bool JudgeYN()
{
	char ch;
	scanf(" %c", &ch);
	if (ch == 'Y' || ch == 'y') return true;
	else return false;
}

void InitList(List *pL)
{
	printf("do you want to initialize this list? (Y/N):");
	if (JudgeYN())
	{
		pL->last = 0;
		printf("\n\t### the list has been initialized successfully ###\n");
	}
}

void ClearList(List *pL)
{
	printf("do you want to clear this list? (Y/N):");
	if (JudgeYN())
	{
		int i;
		for(i = 0 ; i < pL->last ; i++)
			pL->data[i] = 0;
		printf("\n\t### the list has been cleared successfully ###\n");
	}
}

void GetElem(List *pL)
{
	int i;
	printf("please input the index of element you want to get:");
	scanf("%d", &i);
	if(i > pL->last)
		printf("\tError: index out of range\n");
	else if(i <= 0)
		printf("\tError: input is illegal\n");
	else
		printf("\tlist %d : %d\n", i, pL->data[i-1]);
}

void LocateElem(List *pL)
{
	int num;
	printf("please input the element you want to locate:");
	scanf("%d", &num);
	int i;
	int cnt = 0;
	int times;
	int isFind = 0;
	printf("which times this element appear do you want to find (input 0 means find all):", num);
	scanf("%d", &times);
	for (i = 0 ; i < pL->last ; i++)
	{
		if(pL->data[i] == num)
		{
			printf("\tlist %d : %d\n", i+1, num);
			isFind = 1;
			cnt++;
			if (cnt == times)
				break;
		}
	}
	if (i == pL->last)
	{
		if(isFind)
			printf("\tfind all\n");
		else	
			printf("\t%d not found\n", num);
	}
}

void InsertElem(List *pL)
{
	int num;
	printf("please input the element you want to insert:");
	scanf("%d", &num);
	int x;
	printf("please input the location of %d:", num);
	scanf("%d", &x);
	if (x <= 0)
		printf("\tError: input is illegal\n");
	else
	{
		if (pL->last == SizeOfList)
			printf("\tError: the list is full\n");
		else
		{
			if(x > pL->last+1)
			{
				printf("\tWarning: ");
				printf("\tlength of the list is %d\n",pL->last);
				printf("\tdo you want to add this data directly to the end of list?\n\t(Y/N): \t");
				char ch;
				scanf(" %c", &ch);
				if (ch == 'Y' || ch == 'y')
				{
					pL->data[pL->last++] = num;
					printf("\tList %d : %d\n", pL->last, num);
				}
			}
			else
			{
				int i;
				for(i = pL->last ; i >= x ; i--)
					pL->data[i] = pL->data[i-1];
				pL->data[i] = num;
				printf("\tlist %d : %d\n", i+1, num);
				pL->last++;
			}
		}
	}
}

void ModifyElem(List *pL)
{
	int x;
	printf("please input the index of element which you want to modify:");
	scanf("%d", &x);
	if(x <= 0 || x > SizeOfList)
		printf("\tError: input is illegal\n");
	else if(x > pL->last)
		printf("\tError: index out of range\n");
	else
	{
		int num;
		printf("\tlist %d : %d\n", x, pL->data[x-1]);
		printf("%d -> ", pL->data[x-1]);
		scanf("%d", &num);
		pL->data[x-1] = num;
		printf("\tlist %d : %d\n", x, pL->data[x-1]);
	}
}

void DeleteElem(List *pL)
{
	int x;
	printf("please input the index of element you want to delete:");
	scanf("%d", &x);
	if (pL->last == 0)
		printf("\tError: the list is empty\n");
	else
	{
		if(x > pL->last)
			printf("\tError: index out of range\n");
		else if(x <= 0)
			printf("\tError: input is illegal\n");
		else
		{
			int i;
			printf("\tlist %d : %d\n", x, pL->data[x-1]);
			printf("are you sure to delete?(Y/N):");
			if (JudgeYN())
			{
				for(i = x ; i < pL->last ; i++)
					pL->data[i-1] = pL->data[i];
				printf("\n\t### Successfully deleted ###\n");
				pL->last--;
			}
		}
	}
}

void SortElem(List *pL)
{
	printf("do you want to sort this list? (Y/N):");
	if (JudgeYN())
	{
		int i,j,temp;
		for(i = 0;i < pL->last;i++)
			for(j = 1;j < pL->last-i;j++)
				if(pL->data[j-1] > pL->data[j])
				{
					temp = pL->data[j];
					pL->data[j] = pL->data[j-1];
					pL->data[j-1] = temp;
				}
		printf("\n\t### Successfully Sorted ###\n");
	}
}

void PrintAllElements(List *pL)
{
	int i;
	printf("\tlength of the list is %d\n",pL->last);
	if (pL->last == 0)
		printf("\tthis list is empty\n");
	else
	{
		printf("\tall of elements in this list:\n\t");
		for(i = 0 ; i < pL->last ; i++)
		{
			printf("%d", pL->data[i]);
			if( (i+1) % 5 == 0)
				printf("\n\t");
			else
				printf("\t");
		}
	printf("\n");
	}
}

void SaveData(List *pL)
{
	FILE *fp = fopen("linear_list", "w");
	if (fp)
	{
		fprintf(fp, "total : %d\n", pL->last);
		int i;
		for (i = 0 ; i < pL->last ; i++)
			fprintf(fp, "%d\n" ,pL->data[i]);
		fclose(fp);
		printf("\t### successfully save data ###\n");
	}
	else
		printf("\tError: Failed to create a file\n");
}

void LoadData(List *pL)
{
	FILE *fp = fopen("linear_list", "r");
	if (fp)
	{
		fscanf(fp, "total : %d ", &pL->last);
		int i;
		for (i = 0 ; i < pL->last ; i++)
			fscanf(fp, "%d ", &pL->data[i]);
		fclose(fp);
		printf("\t### successfully load data ###\n");
	}
	else
		printf("\tError: No such a file \"linear_list\"\n");
}

void FreeList(List *pL)
{
	printf("do you want to free this list? (Y/N):");
	if (JudgeYN())
	{
		free(pL);
		printf("\n\t### space has been released ###\n");
	}
}

