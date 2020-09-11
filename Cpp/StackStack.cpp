#include <iostream>
#include <stack>
using namespace std;

class StackQueue
{
public:
	void add(int addInt);
	int remove();
	int size();
	bool isEmpty();
private:
	void pour();
	stack<int> push;
	stack<int> pop;
};

class StackStack
{
public:
	void push(int pushInt);
	int pop();
	int peek();
	int size();
	bool isEmpty();
private:
	void swap();
	int peek; 
	StackQueue data;
	StackQueue help;
};

void StackQueue::add(int addInt)
{
	push.push(addInt);
	pour();
}

int StackQueue::remove()
{
	pour();
	int ret = pop.top();
	pop.pop();
	return ret;
}

int StackQueue::size()
{
	return push.size() + pop.size();
}

bool StackQueue::isEmpty()
{
	return push.empty() && pop.empty();
}

void StackQueue::pour()
{
	if (!pop.empty())
		return;
	while (!push.empty()) {
		pop.push(push.top());
		push.pop();
	}
}

void StackStack::push(int pushInt)
{
	this->peek = pushInt;
	data.add(pushInt);
}

int StackStack::pop()
{
	while (data.size() > 1)
	{
		help.add(data.remove());
	}
	int ret = data.remove();
	swap();
	return ret;
}

int StackStack::peek()
{
	return this->peek;
}

int StackStack::size()
{
	return data.size();
}

bool StackStack::isEmpty()
{
	return data.isEmpty();
}

void StackStack::swap()
{
	StackQueue temp = data;
	data = help;
	help = temp;
}

