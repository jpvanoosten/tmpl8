#include "pch.h"
#include "List.h"

TEST(IntList, Ctor)
{
	IntList list;

	ASSERT_TRUE(list.IsEmpty());
}

TEST(IntList, PushBack)
{
	IntList list;
	list.PushBack(9);

	Node* head = list.GetHead();

	ASSERT_FALSE(list.IsEmpty());
	ASSERT_EQ(head->value, 9);
	ASSERT_EQ(head->next, nullptr);
	ASSERT_EQ(head->prev, nullptr);
}

TEST(IntList, PushMany)
{
	IntList list;

	list.PushBack(0);
	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);

	Node* n = list.GetHead();
	for(int i = 0; i < 4; ++i)
	{
		ASSERT_NE(n, nullptr);
		ASSERT_EQ(n->value, i);
		n = n->next;
	}
}

TEST(IntList, PopBack)
{
	IntList list;

	list.PushBack(9);
	list.PopBack();

	ASSERT_TRUE(list.IsEmpty());
}

TEST(IntList, PopMany)
{
	IntList list;

	list.PushBack(0);
	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	
	list.PopBack(); // 3
	list.PopBack(); // 2
	list.PopBack(); // 1
	list.PopBack(); // 0

	ASSERT_TRUE(list.IsEmpty());
}

TEST(IntList, Count)
{
	IntList list;

	list.PushBack(0);
	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);

	ASSERT_EQ(list.Count(), 4);
}