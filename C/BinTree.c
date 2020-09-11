#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct BinTree
{
	ElemType data;
	struct BinTree* LeftChild;
	struct BinTree* RightChild;
}BTree;

void Init(BTree** root)
{
	*root = (BTree*)malloc(sizeof(BTree));
	(*root)->LeftChild = NULL;
	(*root)->RightChild = NULL;
}

void NodeConstructor(BTree** node, BTree* root, int Left, ElemType data)
{
	*node = (BTree*)malloc(sizeof(BTree));
	(*node)->data = data;
	if(Left) root->LeftChild = *node;
	else root->RightChild = *node;
	(*node)->LeftChild = NULL;
	(*node)->RightChild = NULL;
}

void PreOrderTraverse(BTree* root)
{
	if (!root) return;
	printf("%c ", root->data);
	PreOrderTraverse(root->LeftChild);
	PreOrderTraverse(root->RightChild);
}

void InOrderTraverse(BTree* root)
{
	if (!root) return;
	InOrderTraverse(root->LeftChild);
	printf("%c ", root->data);
	InOrderTraverse(root->RightChild);
}

void PostOrderTraverse(BTree* root)
{
	if (!root) return;
	PostOrderTraverse(root->LeftChild);
	PostOrderTraverse(root->RightChild);
	printf("%c ", root->data);
}

int CountLeaves(BTree* root)
{
	if(!root) return 0;
	if (!root->LeftChild && !root->RightChild) return 1;
	return CountLeaves(root->LeftChild) + CountLeaves(root->RightChild);
}

void SwapLeftAndRight(BTree* root)
{
	if (!root->LeftChild && !root->RightChild) return;
	SwapLeftAndRight(root->LeftChild);
	SwapLeftAndRight(root->RightChild);
	BTree* temp = root->LeftChild;
	root->LeftChild = root->RightChild;
	root->RightChild = temp;
}

void FreeTree(BTree* root)
{
	if (!root) return;
	FreeTree(root->LeftChild);
	FreeTree(root->RightChild);
	free(root);
}

void DeleteNode(BTree** root, ElemType key)
{
	if (!(*root)) return;
	if ((*root)->data == key)
	{
		FreeTree(*root);
		*root = NULL;
		return;
	}
	if ((*root)->LeftChild->data == key)
	{
		FreeTree((*root)->LeftChild);
		(*root)->LeftChild = NULL;
	}
	if ((*root)->RightChild->data == key)
	{
		FreeTree((*root)->RightChild);
		(*root)->RightChild = NULL;
	}
	DeleteNode(&(*root)->LeftChild, key);
	DeleteNode(&(*root)->RightChild, key);
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
	
	PreOrderTraverse(root);
	printf("\n");
	SwapLeftAndRight(root);
	PreOrderTraverse(root);
	
	return 0;
}
