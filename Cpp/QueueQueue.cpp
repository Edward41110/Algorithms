#include <iostream>
#include <queue>
using namespace std;

class QueueStack
{
public:
	void push(int pushInt);
	int pop();
	int peek();
	int size();
	bool isEmpty();
private:
	void swap();
	queue<int> data;
	queue<int> help;
};

class QueueQueue
{
public:
	void add(int addInt);
	int remove();
	int peek();
	int size();
	bool isEmpty();
private:
	void pour();
	QueueStack push;
	QueueStack pop;
};

void QueueStack::push(int pushInt) {
	data.push(pushInt);
}

int QueueStack::pop() {
	while (data.size() > 1) {
		help.push(data.front());
		data.pop();
	}
	int ret = data.front();
	data.pop();
	swap();
	return ret;
}

int QueueStack::peek()
{
	return data.back();
}

void QueueStack::swap()
{
	queue<int> temp = data;
	data = help;
	help = temp;
}

int QueueStack::size()
{
	return data.size();
}

bool QueueStack::isEmpty()
{
	return data.empty();
}

void QueueQueue::add(int addInt)
{
	push.push(addInt);
	pour();
}

int QueueQueue::remove()
{
	pour();
	return pop.pop();
}

int QueueQueue::peek()
{
	pour();
	return pop.peek();
}

void QueueQueue::pour()
{
	if (!pop.isEmpty())
		return;
	while (!push.isEmpty())
	{
		pop.push(push.pop());
	}
}

int QueueQueue::size()
{
	return push.size() + pop.size();
}

bool QueueQueue::isEmpty()
{
	return push.isEmpty() && pop.isEmpty();
}

