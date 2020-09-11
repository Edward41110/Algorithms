#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char ElemType;
typedef struct BinTree
{
	ElemType data;
	bool Ltag;
	bool Rtag;
	struct BinTree* LeftChild;
	struct BinTree* RightChild;
}BTree;

void Init(BTree** root)
{
	*root = (BTree*)malloc(sizeof(BTree));
	(*root)->Ltag = 1;
	(*root)->Rtag = 1;
	(*root)->LeftChild = NULL;
	(*root)->RightChild = NULL;
}

void NodeConstructor(BTree** node, BTree* root, int Left, ElemType data)
{
	*node = (BTree*)malloc(sizeof(BTree));
	(*node)->data = data;
	if (Left)
	{
		root->LeftChild = *node;
		root->Ltag = 0;
	}
	else
	{
		root->RightChild = *node;
		root->Rtag = 0;
	}
	(*node)->Ltag = 1;
	(*node)->Rtag = 1;
	(*node)->LeftChild = NULL;
	(*node)->RightChild = NULL;
}

void InThreading(BTree* root)
{
	static BTree* pre = NULL;
	if (!root) return;
	InThreading(root->LeftChild);
	if (root->Ltag)
		root->LeftChild = pre;
	if (pre && pre->Rtag)
		pre->RightChild = root;
	pre = root;
	InThreading(root->RightChild);
}

void InOrderTraverse_Thr(BTree* root)
{
	BTree* p = root;
	while (p)
	{
		while (!p->Ltag)
			p = p->LeftChild;
		printf("%c ", p->data);
		while (p->Rtag && p->RightChild != root)
		{
			p = p->RightChild;
			if (!p) break;
			printf("%c ", p->data);
		}
		if (!p) break;
		p = p->RightChild;
		if (p == root)
		{
			printf("%c ", p->data);
			p = p->RightChild;
		}
	}
}

void PrintNodeInfo(BTree* root)
{
	printf("data: %c Ltag: %d Rtag: %d\n", root->data, root->Ltag, root->Rtag);
	if (root->LeftChild) printf("LeftChildInfo: %c\t", root->LeftChild->data);
	if (root->RightChild) printf("RightChildInfo: %c", root->RightChild->data);
	printf("\n");
}

int main()
{
	BTree* root;
	Init(&root);
	root->data = 'E';
	BTree *l, *ll, *lr, *lrl, *r, *rr, *rrl, *rrr, *rrrr, *rrrrl;
	NodeConstructor(&l, root, 1, 'B');
	NodeConstructor(&ll, l, 1, 'A');
	NodeConstructor(&lr, l, 0, 'D');
	NodeConstructor(&lrl, lr, 1, 'C');
	NodeConstructor(&r, root, 0, 'F');
	NodeConstructor(&rr, r, 0, 'H');
	NodeConstructor(&rrl, rr, 1, 'G');
	NodeConstructor(&rrr, rr, 0, 'I');
	NodeConstructor(&rrrr, rrr, 0, 'K');
	NodeConstructor(&rrrrl, rrrr, 1, 'J');

	InThreading(root);
	InOrderTraverse_Thr(root);
	printf("\n");
	return 0;
}

