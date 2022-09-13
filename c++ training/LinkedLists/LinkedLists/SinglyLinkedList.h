#pragma once

template<typename T>
class TSLList
{
private:
	FNode* Head = nullptr;
	FNode* Tail = nullptr;
	int Size = 0;

	struct FNode
	{
	public:
		T Value;
		FNode* Next;

		FNode(const T& NewValue, const FNode* NewNext = nullptr) : Value(NewValue), Next(NewNext) {}
	};

public:
	TSLList() {}
	TSLList(const T& Value) : Size(1)
	{
		Head = new FNode(Value);
		Tail = Head;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	T& operator[](const int Index)
	{
		FNode CurrentNode = *Head;
		for (int i = 0; i < Index - 1; i++)
		{
			CurrentNode = *(CurrentNode.Next);
		}

		return CurrentNode;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	const T& operator[](const int Index) const
	{
		FNode* CurrentNode = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			CurrentNode = CurrentNode->Next;
		}

		return CurrentNode->Value;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	T& Head()
	{
		return Head->Value;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	const T& Head() const
	{
		return Head->Value;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	T& Tail()
	{
		return Tail->Value;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	const T& Tail() const
	{
		return Tail->Value;
	}
};