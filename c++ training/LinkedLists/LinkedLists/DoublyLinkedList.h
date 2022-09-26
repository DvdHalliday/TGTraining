#pragma once

template<typename T>
class TDLList
{
private:
	struct FNode
	{
	public:
		T Data;

		FNode* Next;
		FNode* Previous;

		FNode(const T& NewData, FNode* NewPrevious = nullptr, FNode* NewNext = nullptr) : Data(NewData), Next(NewNext), Previous(NewPrevious) {}
	};

	FNode* Head = nullptr;
	FNode* Tail = nullptr;
	int Size = 0;

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	FNode& GetNodeAt(const int Index) const
	{
		FNode* CurrentNode;

		if (Index < Size / 2)
		{
			CurrentNode = Head;
			for (int i = 0; i < Index; i++)
			{
				CurrentNode = CurrentNode->Next;
			}

			return *CurrentNode;
		}

		CurrentNode = Tail;
		for (int i = Size - 1; i > Index; i--)
		{
			CurrentNode = CurrentNode->Previous;
		}

		return *CurrentNode;
	}

public:
	TDLList() {}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	TDLList(const TDLList<T>& Other)
	{
		for (T Item : Other)
		{
			AddTail(Item);
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	~TDLList()
	{
		Clear();
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	TDLList& operator=(const TDLList<T>& Other)
	{
		Clear();

		for (T Item : Other)
		{
			AddTail(Item);
		}

		return *this;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	T& operator[](const int Index)
	{
		return GetNodeAt(Index).Data;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	const T& operator[](const int Index) const
	{
		return GetNodeAt(Index).Data;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	T& GetHead()
	{
		return Head->Data;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	const T& GetHead() const
	{
		return Head->Data;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	T& GetTail()
	{
		return Tail->Data;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	const T& GetTail() const
	{
		return Tail->Data;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool IsEmpty() const
	{
		return Size == 0;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	int GetSize() const
	{
		return Size;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void AddHead(const T& Data)
	{
		if (IsEmpty())
		{
			Head = new FNode(Data);
			Tail = Head;

			Size = 1;
			return;
		}

		Head->Previous = new FNode(Data, nullptr, Head);
		Head = Head->Previous;

		Size++;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void AddTail(const T& Data)
	{
		if (IsEmpty())
		{
			AddHead(Data);
			return;
		}

		Tail->Next = new FNode(Data, Tail);
		Tail = Tail->Next;

		Size++;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void Insert(const T& Data, const int Index)
	{
		if (Index < 0 || Index > Size)
		{
			return;
		}

		if (Index == 0)
		{
			AddHead(Data);
			return;
		}
		else
		{
			FNode& PreviousNode = GetNodeAt(Index - 1);
			FNode* CurrentPtr = PreviousNode.Next;
			PreviousNode.Next = new FNode(Data, &PreviousNode, CurrentPtr);

			if (Index == Size)
			{
				Tail = Tail->Next;
			}
			else
			{
				CurrentPtr->Previous = PreviousNode.Next;
			}

			Size++;
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void Remove(const int Index)
	{
		if (Index < 0 || Index >= Size)
		{
			return;
		}

		if (Index == 0)
		{
			FNode* NodeToDeletePtr = Head;
			Head = NodeToDeletePtr->Next;

			if (Head)
			{
				Head->Previous = nullptr;
			}

			delete NodeToDeletePtr;
			NodeToDeletePtr = nullptr;

			if (Size == 1)
			{
				Tail = nullptr;
			}
		}
		else
		{
			FNode& PreviousNode = GetNodeAt(Index - 1);
			FNode* NodeToDeletePtr = PreviousNode.Next;
			FNode* NewNextPtr = NodeToDeletePtr->Next;

			PreviousNode.Next = NewNextPtr;
			
			if (NewNextPtr)
			{
				NewNextPtr->Previous = &PreviousNode;
			}
			else
			{
				Tail = &PreviousNode;
			}

			delete NodeToDeletePtr;
			NodeToDeletePtr = nullptr;

		}

		Size--;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void Clear()
	{
		while (Head)
		{
			Remove(0);
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	class FIterator
	{
	private:
		FNode* Current;

	public:
		FIterator(FNode* NewCurrent) : Current(NewCurrent) {}

		FIterator& operator++()
		{
			Current = Current->Next;
			return *this;
		}

		T& operator*()
		{
			return Current->Data;
		}

		bool operator!=(const FIterator& Other)
		{
			return Current != Other.Current;
		}
	};
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	FIterator begin() const
	{
		return FIterator(Head);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	FIterator end() const
	{
		return FIterator(nullptr);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<typename Pred>
	void ForEach(const Pred& Predicate)
	{
		for (T& Item : *this)
		{
			Predicate(Item);
		}
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<typename Pred>
	T* FindByPredicate(const Pred& Predicate) const
	{
		for (T& Item : *this)
		{
			if (Predicate(Item))
			{
				return &Item;
			}
		}

		return nullptr;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<typename Pred>
	TSLList<T> FilterByPredicate(const Pred& Predicate) const
	{
		TSLList<T> NewList;

		for (T& Item : *this)
		{
			if (Predicate(Item))
			{
				NewList.AddTail(Item);
			}
		}

		return NewList;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<typename Pred>
	void RemoveAllByPredicate(const Pred& Predicate)
	{
		FNode* CurrentNode = Head;
		for (int i = 0; i < Size; i++)
		{
			if (Predicate(CurrentNode->Value))
			{
				CurrentNode = CurrentNode->Next;
				Remove(i--);
			}
			else
			{
				CurrentNode = CurrentNode->Next;
			}
		}
	}
};