#include "List.h"

IntList::~IntList()
{
	while (head != nullptr)
	{
		Node* prevHead = head;
		head = head->next;
		delete prevHead;
	}
}

void IntList::PushBack(int v)
{
	Node* newValue = new Node(v);

	if (tail != nullptr)
	{
		tail->next = newValue;
	}

	newValue->prev = tail;
	tail = newValue;

	if (head == nullptr)
	{
		head = newValue;
	}
}

void IntList::PopBack()
{
	Node* prevTail = tail;
	if (prevTail != nullptr)
	{
		tail = prevTail->prev;
		if (tail != nullptr)
		{
			tail->next = nullptr;
		}
		delete prevTail;
	}
}

Node* IntList::GetHead()
{
	return head;
}

bool IntList::IsEmpty() const
{
	return head == nullptr && tail == nullptr;
}
