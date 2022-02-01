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
	/// Get the root node.
	/// </summary>
	/// <returns></returns>
	Node* GetHead();

	/// <summary>
	/// Does the list contain any values?
	/// </summary>
	/// <returns>true if the list is empty.</returns>
	bool IsEmpty() const;

private:
	Node* head = nullptr;
	Node* tail = nullptr;
};