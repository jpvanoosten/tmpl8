#pragma once

struct Node
{
	Node(int value)
		: value(value)
	{}

	int value;
	Node* prev = nullptr;
	Node* next = nullptr;
};

class IntList
{
public:
	IntList() = default;
	~IntList();

	/// <summary>
	/// Push an element at the end of the list.
	/// </summary>
	/// <param name="v"></param>
	void PushBack(int v);

	/// <summary>
	/// Remove the element from the end of the list.
	/// </summary>
	void PopBack();

	/// <summary>
	/// Get the head node.
	/// </summary>
	/// <returns>The head node.</returns>
	Node* GetHead();

	/// <summary>
	/// Get the tail node.
	/// </summary>
	/// <returns>The tail node.</returns>
	Node* GetTail();

	/// <summary>
	/// Does the list contain any values?
	/// </summary>
	/// <returns>true if the list is empty.</returns>
	bool IsEmpty() const;

	/// <summary>
	/// Counts the number of elements in the list.
	/// </summary>
	/// <returns>The number of elements in the list.</returns>
	size_t Count() const;

private:
	Node* head = nullptr;
	Node* tail = nullptr;
};