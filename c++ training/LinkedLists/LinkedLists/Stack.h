#pragma once
#include "SinglyLinkedList.h"

template<typename T>
class TStack
{
private:
	TSLList<T> List;

public:
	const T& Top() const
	{
		return List.GetHead();
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	T& Top()
	{
		return List.GetHead();
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void Push(const T& Item)
	{
		List.AddHead(Item);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void Pop()
	{
		List.Remove(0);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool IsEmpty() const
	{
		return List.IsEmpty();
	}
};