#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 80
#define OK 0
#define EMPTY 1
#define FULL 2

typedef int ElemType;
typedef struct _Queue 
{
	ElemType data[MAX_SIZE];
	int front;
	int rear;
} Queue;

int Init(Queue* q)
{
	q->front = 0;
	q->rear = 0;
	return OK;
}

int IsEmpty(Queue *q)
{
	return q->front == q->rear;
}

int IsFull(Queue *q)
{
	return (q->rear + 1) % MAX_SIZE == q->front; 
}

int QueueLength(Queue *q)
{
	return (q->rear - q->front + MAX_SIZE) % MAX_SIZE;
}

int EnQueue(Queue *q, ElemType data)
{
	if (IsFull(q)) return FULL;
	else
	{
		q->data[q->rear] = data;
		q->rear = (q->rear + 1) % MAX_SIZE;
	}
		
}

int DeQueue(Queue *q, ElemType* ret)
{
	if (IsEmpty(q)) return EMPTY;
	*ret = q->data[q->front];
	q->front = (q->front + 1) % MAX_SIZE;
}

int main()
{
	return 0;
}
